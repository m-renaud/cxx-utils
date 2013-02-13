#ifndef MRR_CXX_UTILS_STOPWATCH_HXX_
#define MRR_CXX_UTILS_STOPWATCH_HXX_

#include <chrono>
#include <numeric>
#include <ratio>


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


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


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // MRR_CXX_UTILS_STOPWATCH_HXX_
