#ifndef MRR_CXX_UTILS_MONITOR_HXX_
#define MRR_CXX_UTILS_MONITOR_HXX_

#include <mutex>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


template <typename T>
class monitor
{
private:
  mutable T t_;
  mutable std::mutex m_;

public:
  monitor()
    : t_{}
  {
  }

  monitor(T& t)
    : t_{t}
  {
  }

  monitor(T const& t)
    : t_{t}
  {
  }

  monitor(T&& t)
    : t_{std::move(t)}
  {
  }

  monitor(monitor const& m)
    : t_{std::move(m.object())}
  {
  }

  monitor(monitor&&) = delete;
  monitor& operator =(monitor const&) = delete;
  monitor& operator =(monitor&&) = delete;

  T object() const
  {
    std::lock_guard<std::mutex> guard{m_};
    return t_;
  }

  template <typename F>
  auto operator ()(F&& f) const
    -> decltype(std::forward<F>(f)(t_))
  {
    std::lock_guard<std::mutex> guard{m_};
    return std::forward<F>(f)(t_);
  }

};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // MRR_CXX_UTILS_MONITOR_HXX_
