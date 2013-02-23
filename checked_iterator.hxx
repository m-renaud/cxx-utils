#ifndef MRR_CXX_UTILS_CHECKED_ITERATOR_HXX_
#define MRR_CXX_UTILS_CHECKED_ITERATOR_HXX_

#include <iterator>
#include <stdexcept>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


template <
  typename Cont,
  typename Iter = typename Cont::iterator
>
class checked_iterator : public std::iterator_traits<Iter>
{
  using traits_type = std::iterator_traits<Iter>;

public:
  using difference_type = typename traits_type::difference_type;
  using value_type = typename traits_type::value_type;
  using pointer = typename traits_type::pointer;
  using reference = typename traits_type::reference;
  using iterator_categor = typename traits_type::iterator_category;

  checked_iterator() = delete;
  checked_iterator(checked_iterator const& ) = default;
  checked_iterator(checked_iterator&& ) = default;
  checked_iterator& operator =(checked_iterator const& ) = default;
  checked_iterator& operator =(checked_iterator&& ) = default;
  ~checked_iterator() = default;

  checked_iterator(Cont& c, Iter p)
    : cont_(&c), current_(std::move(p))
  {
    valid(current_);
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Dereference and access operators.
  reference operator *()
  {
    using std::end;

    if (current_ == end(*cont_))
      throw std::out_of_range("Attempt to dereference end detected");
    return *current_;
  }

  pointer operator ->()
  {
    return &*current_;
  }

  reference operator [](difference_type d)
  {
    using std::end;

    if (end(*cont_) - current_ <= d)
      throw std::out_of_range(
        "Attempt to access element [" + std::to_string(d) + "] detected"
      );

    return cont_[d];
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Increment and decrement operators.
  checked_iterator& operator ++()
  {
    using std::end;

    if (current_ == end(*cont_))
      throw std::out_of_range("Attempt to incement past end detected");

    ++current_;
    return *this;
  }

  checked_iterator operator ++(int)
  {
    checked_iterator tmp = *this;
    ++*this;
    return tmp;
  }

  checked_iterator& operator --()
  {
    using std::begin;

    if (current_ == begin(*cont_))
      throw std::out_of_range("Attempt to decrement before begin detected");

    --current_;
    return *this;
  }

  checked_iterator operator --(int)
  {
    checked_iterator tmp = *this;
    --*this;
    return tmp;
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Addition and subtraction operators.
  checked_iterator& operator +=(difference_type d)
  {
    using std::end;

    if (end(*cont_) - current_ <= d)
      throw std::out_of_range(
        "Attempt to move past end with += " + std::to_string(d) + " detected"
      );

    current_ += d;
    return *this;
  }

  checked_iterator& operator -=(difference_type d)
  {
    current_ -= d;
    return *this;
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Comparison operators.
  bool operator ==(checked_iterator const& rhs)
  {
    return cont_ == rhs.cont_ && current_ == rhs.current_;
  }

  bool operator !=(checked_iterator const& rhs)
  {
    return !(*this == rhs);
  }

  bool operator <(checked_iterator const& rhs)
  {
    return cont_ == rhs.cont_ && current_ < rhs.current_;
  }

  bool operator >(checked_iterator const& rhs)
  {
    return rhs < *this;
  }

  bool operator <=(checked_iterator const& rhs)
  {
    return *this < rhs || *this == rhs;
  }

  bool operator >=(checked_iterator const& rhs)
  {
    return rhs <= *this;
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  difference_type index() const
  {
    using std::begin;

    return current_ - begin(*cont_);
  }

  Iter unchecked() const
  {
    return current_;
  }


private:
  Cont* cont_;
  Iter current_;

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // Check the validity of the iterator passed in w.r.t. the container.
  void valid(Iter p)
  {
    using std::end;

    if (p == end(*cont_))
      return;

    if (valid_helper(p, typename traits_type::iterator_category()))
      return;

    throw std::out_of_range("Invalid iterator provided to constructor");
  }

  bool valid_helper(Iter p, std::input_iterator_tag)
  {
    using std::begin;
    using std::end;

    for (Iter i = begin(*cont_); i != end(*cont_); ++i)
      if(i == p)
        return true;

    return false;
  }

  bool valid_helper(Iter p, std::random_access_iterator_tag)
  {
    using std::begin;
    using std::end;

    return begin(*cont_) <= p && p <= end(*cont_);
  }

};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Addition and subtraction operators.
template <typename Cont, typename Iter>
inline checked_iterator<Cont,Iter> operator +(
  checked_iterator<Cont,Iter> iter,
  typename checked_iterator<Cont,Iter>::different_type d
)
{
  iter += d;
  return iter;
}

template <typename Cont, typename Iter>
inline checked_iterator<Cont,Iter> operator +(
  typename checked_iterator<Cont,Iter>::different_type d,
  checked_iterator<Cont,Iter> iter
)
{
  iter += d;
  return iter;
}

template <typename Cont, typename Iter>
inline checked_iterator<Cont,Iter> operator -(
  checked_iterator<Cont,Iter> iter,
  typename checked_iterator<Cont,Iter>::different_type d
)
{
  iter -= d;
  return iter;
}

template <typename Cont, typename Iter>
inline checked_iterator<Cont,Iter> operator -(
  typename checked_iterator<Cont,Iter>::different_type d,
  checked_iterator<Cont,Iter> iter
)
{
  iter -= d;
  return iter;
}



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Convenient creator functions.

template <typename Cont, typename Iter>
checked_iterator<Cont, Iter> make_checked(Cont& c, Iter i)
{
  return checked_iterator<Cont,Iter>(c, i);
}


template <typename Cont>
checked_iterator<Cont, typename Cont::iterator> make_checked(Cont& c)
{
  using std::begin;

  return checked_iterator<Cont,typename Cont::iterator>(c, begin(c));
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // MRR_CXX_UTILS_CHECKED_ITERATOR_HXX_
