#ifndef MRR_CXX_UTILS_UTILITLY_HXX_
#define MRR_CXX_UTILS_UTILITLY_HXX_

#include <chrono>
#include <ios>
#include <iostream>
#include <numeric>
#include <ratio>
#include <sstream>

namespace mrr {

template <typename T, typename Char, typename Traits>
auto discard(std::basic_istream<Char,Traits>& is)
  -> std::basic_istream<Char,Traits>&
{
  T t;
  is >> t;
  return is;
}

template <typename T>
std::string to_string(T const& t)
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

template <typename ClockType = std::chrono::high_resolution_clock>
class stopwatch
{
  using time_point = typename ClockType::time_point;

public:
  stopwatch()
  {
    start_time = ClockType::now();
  }

  double lap()
  {
    using std::chrono::duration;
    using std::chrono::duration_cast;

    time_point end_time = ClockType::now();
    time_span = duration_cast<duration<double> >(end_time - start_time).count();
    start_time = ClockType::now();
    return time_span;
  }

  void reset()
  {
    start_time = ClockType::now();
  }

private:
  time_point start_time;
  double time_span;
};


} // namespace mrr

#endif // #ifndef MRR_CXX_UTILS_UTILITLY_HXX_
