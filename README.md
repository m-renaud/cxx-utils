# MRR C++ Utils #
This directory contains my personal C++ utility headers and libraries.

## Utility.hxx ##
Contains common utility functions that are useful for everday
coding.

### Contents ###

* `template <typename T> std::istream& discard(std::istream&);`
This function discards the next occurence of type `T` from an istream

* `template <typename T> std::string to_string(T const& t);`
This functions returns the value of type T as a string using
`std::stringstream`

* `template <typename ClockType> class stopwatch`
This class can be used to time running times of algorithms using the
new C++11 `<chrono>` header.
