# MRR C++ Utils #
This directory contains my personal C++ utility headers and libraries.


## `utility.hxx` ##
Contains common utility functions that are useful for everday
coding.

### Contents ###

#### `template <typename T> std::istream& discard(std::istream&);` ####
This function discards the next occurence of type `T` from an istream.
For brevity here, `discard` takes a `std::istream` but in the
implementation it is templated over `Char` and `Traits` and uses
`std::basic_istream<Char,Traits>`.


#### `template <typename T> std::string to_string(T const& t);` ####
This functions returns the value of type T as a string using
`std::stringstream` although, this function in now available in the
standard since C++11.

#### `template <typename ClockType> class stopwatch` ####
This class can be used to time running times of algorithms using the
new C++11 `<chrono>` header.


## `concurrent/algorithm.hxx` ##

Concurrent version of the standard `<algorithm>` header with
implementation of *embarrassingly parallel* algorithms.

### Contents ###

* `template <typename Iterator, typename T>`
  `T accumulate(Iterator first, Iterator last, T init);`

* `template <typename Iterator, typename T>`
  `auto count(Iterator first, Iterator last, T const& value)`
  `-> typename std::iterator_traits<Iterator>::difference_type;`

* `template <typename Iterator, typename Pred>`
  `auto count_if(Iterator first, Iterator last, Pred const& pred)`
  `-> typename std::iterator_traits<Iterator>::difference_type;`

* `template <typename Iterator, typename T>`
  `void fill(Iterator first, Iterator last, T const& value);`

* `template <typename Iterator, typename Func>`
  `void for_each(Iterator first, Iterator last, Func const& func);`

* `template <typename Iterator>`
  `Iterator max_element(Iterator first, Iterator last);`

* `template <typename Iterator>`
  `Iterator min_element(Iterator first, Iterator last);`

* `template <typename Iterator, typename T>`
  `void replace(Iterator first, Iterator last, T const& old_val, T const& new_val);`

* `template <typename Iterator, typename Pred, typename T>`
  `void replace_if(Iterator first, Iterator last, Pred const& pred, T const& new_val);`

## `scope_guard` ##

An implementation of Andrei Alexandrescu's `scope_guard` leveraging
RAII to handle resource cleanup even when exceptions can be thrown.


## `state` ##

Lightweight class to easily save and restore state of a set of variables.
