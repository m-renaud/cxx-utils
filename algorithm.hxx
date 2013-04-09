//===========================================================================
// Copyright (c) 2012 Matt Renaud. All Rights Reserved.
//
//===========================================================================

#ifndef MRR_CONCURRENT_ALGORITHM_HXX_
#define MRR_CONCURRENT_ALGORITHM_HXX_

#include <algorithm>
#include <future>
#include <iostream>
#include <thread>
#include <type_traits>
#include <vector>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {
namespace concurrent {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Prototypes
template <typename Iterator, typename T>
T accumulate(Iterator first, Iterator last, T init);

template <typename Iterator, typename T>
auto count(Iterator first, Iterator last, T const& value)
  -> typename std::iterator_traits<Iterator>::difference_type;

template <typename Iterator, typename Pred>
auto count_if(Iterator first, Iterator last, Pred const& pred)
  -> typename std::iterator_traits<Iterator>::difference_type;

template <typename Iterator, typename T>
void fill(Iterator first, Iterator last, T const& value);

template <typename Iterator, typename Func>
void for_each(Iterator first, Iterator last, Func const& func);

template <typename Iterator>
Iterator max_element(Iterator first, Iterator last);

template <typename Iterator>
Iterator min_element(Iterator first, Iterator last);

template <typename Iterator, typename T>
void replace(Iterator first, Iterator last, T const& old_val, T const& new_val);

template <typename Iterator, typename Pred, typename T>
void replace_if(Iterator first, Iterator last, Pred const& pred, T const& new_val);



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Implementations
template <typename Iterator, typename T>
struct parallel_accumulate_impl
{
  static T apply(Iterator first, Iterator last, T const& init)
  {
    return std::accumulate(first,last,init);
  }

  template <typename ResultIter>
  static T result(ResultIter first, ResultIter last, T const& init)
  {
    return std::accumulate(first,last,init);
  }
};


template <typename Iterator, typename T>
struct parallel_count_impl
{
  using return_type = typename std::iterator_traits<Iterator>::difference_type;

  static return_type apply(Iterator first, Iterator last, T const& t)
  {
    return std::count(first,last,t);
  }

  template <typename ResultIter>
  static return_type result(ResultIter first, ResultIter last, T const&)
  {
    return mrr::concurrent::accumulate(first,last,0);
  }
};


template <typename Iterator, typename Pred>
struct parallel_count_if_impl
{
  using return_type = typename std::iterator_traits<Iterator>::difference_type;

  static return_type apply(Iterator first, Iterator last, Pred const& pred)
  {
    return std::count_if(first,last,pred);
  }

  template <typename ResultIter>
  static return_type result(ResultIter first, ResultIter last, Pred const&)
  {
    return mrr::concurrent::accumulate(first,last,0);
  }
};


template <typename Iterator, typename T>
struct parallel_fill_impl
{
  static void apply(Iterator first, Iterator last, T const& value)
  {
    return std::fill(first,last,value);
  }
};



template <typename Iterator, typename Func>
struct parallel_for_each_impl
{
  static void apply(Iterator first, Iterator last, Func const& f)
  {
    std::for_each(first,last,f);
  }
};



template <typename Iterator>
struct parallel_max_element_impl
{
  static Iterator apply(Iterator first, Iterator last)
  {
    return std::max_element(first,last);
  }

  template <typename ResultIter>
  static Iterator result(ResultIter first, ResultIter last)
  {
    return std::max_element(first,last);
  }
};



template <typename Iterator>
struct parallel_min_element_impl
{
  static Iterator apply(Iterator first, Iterator last)
  {
    return std::min_element(first,last);
  }

  template <typename ResultIter>
  static Iterator result(ResultIter first, ResultIter last)
  {
    return std::min_element(first,last);
  }
};



template <typename Iterator, typename T>
struct parallel_replace_impl
{
  static void apply(Iterator first, Iterator last, T const& old_val, T const& new_val)
  {
    std::replace(first,last,old_val,new_val);
  }
};



template <typename Iterator, typename Pred, typename T>
struct parallel_replace_if_impl
{
  static void apply(Iterator first, Iterator last, Pred const& pred, T const& new_val)
  {
    std::replace(first,last,pred,new_val);
  }
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// The core algorithm - non-void return version
template <typename Algorithm, typename Iterator, typename... Args>
auto in_parallel(Iterator first, Iterator last, Args&&... args)
  -> typename std::enable_if<
       !std::is_void<decltype(
                       Algorithm::apply(first,last,std::forward<Args>(args)...)
       )>::value,
       decltype(Algorithm::apply(first,last,std::forward<Args>(args)...))
     >::type
{
  using difference_type = typename std::iterator_traits<Iterator>::difference_type;
  using iterator = Iterator;
  using return_type = decltype(
    Algorithm::apply(first,last,std::forward<Args>(args)...)
  );

  const difference_type length = std::distance(first,last);

  if(length == 0)
    return 0;

  const unsigned num_threads = std::max(1u, std::thread::hardware_concurrency());
  const difference_type block_size = length/num_threads;

  std::vector<std::future<return_type> > threads(num_threads - 1);
  std::vector<return_type> results(num_threads);

  iterator block_first = first;
  for(unsigned i = 0; i < (num_threads - 1); ++i)
  {
    iterator block_last = block_first;
    std::advance(block_last, block_size);

    threads[i] = std::async(
      std::launch::async,
      Algorithm::apply,
      block_first, block_last,
      std::forward<Args>(args)...
    );
    block_first = block_last;
  }

  results[num_threads-1] = Algorithm::apply(
    block_first,last,
    std::forward<Args>(args)...
  );

  for(unsigned i = 0; i < (num_threads - 1); ++i)
    results[i] = threads[i].get();

  return Algorithm::result(begin(results), end(results), std::forward<Args>(args)...);
}



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// The core algorithm - void return version
template <typename Algorithm, typename Iterator, typename... Args>
auto in_parallel(Iterator first, Iterator last, Args&&... args)
  -> typename std::enable_if<
       std::is_void<decltype(
                      Algorithm::apply(first,last,std::forward<Args>(args)...)
       )>::value,
       void
     >::type
{
  using difference_type = typename std::iterator_traits<Iterator>::difference_type;
  using iterator = Iterator;

  const difference_type length = std::distance(first,last);

  if(length == 0)
    return;

  const unsigned num_threads = std::max(1u, std::thread::hardware_concurrency());
  const difference_type block_size = length/num_threads;

  std::vector<std::thread> threads(num_threads - 1);

  iterator block_first = first;
  for(unsigned i = 0; i < (num_threads - 1); ++i)
  {
    iterator block_last = block_first;
    std::advance(block_last, block_size);

    threads[i] = std::thread(
      Algorithm::apply,
      block_first, block_last,
      std::forward<Args>(args)...
    );
    block_first = block_last;
  }

  Algorithm::apply(
    block_first,last,
    std::forward<Args>(args)...
  );

  for(std::thread& t : threads)
    t.join();
}



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Calling functions
template <typename Iterator, typename T>
T accumulate(Iterator first, Iterator last, T init)
{
  return in_parallel<parallel_accumulate_impl<Iterator,T> >(first,last,init);
}

template <typename Iterator, typename T>
auto count(Iterator first, Iterator last, T const& value)
  -> typename std::iterator_traits<Iterator>::difference_type
{
  return in_parallel<parallel_count_impl<Iterator,T> >(first,last,value);
}

template <typename Iterator, typename Pred>
auto count_if(Iterator first, Iterator last, Pred const& pred)
  -> typename std::iterator_traits<Iterator>::difference_type
{
  return in_parallel<parallel_count_if_impl<Iterator,Pred> >(first,last,pred);
}

template <typename Iterator, typename T>
void fill(Iterator first, Iterator last, T const& value)
{
  return in_parallel<parallel_fill_impl<Iterator,T> >(first, last, value);
}

template <typename Iterator, typename Func>
void for_each(Iterator first, Iterator last, Func const& func)
{
  in_parallel<parallel_for_each_impl<Iterator,Func> >(first,last,func);
}

template <typename Iterator>
Iterator max_element(Iterator first, Iterator last)
{
  in_parallel<parallel_max_element_impl<Iterator> >(first,last);
}

template <typename Iterator>
Iterator min_element(Iterator first, Iterator last)
{
  in_parallel<parallel_min_element_impl<Iterator> >(first,last);
}

template <typename Iterator, typename T>
void replace(Iterator first, Iterator last, T const& old_val, T const& new_val)
{
  in_parallel<parallel_replace_impl<Iterator,T> >(first,last,old_val,new_val);
}

template <typename Iterator, typename Pred, typename T>
void replace_if(Iterator first, Iterator last, Pred const& pred, T const& new_val)
{
  in_parallel<parallel_replace_if_impl<Iterator,Pred,T> >(first,last,pred,new_val);
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace concurrent
} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // #ifndef MRR_CONCURRENT_ALGORITHM_HXX_
