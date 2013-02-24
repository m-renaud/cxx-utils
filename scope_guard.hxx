//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Implementation of Andrei Alexandrescu's scope guard.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#ifndef MRR_UTILITY_SCOPE_GUARD_
#define MRR_UTILITY_SCOPE_GUARD_

#include <utility>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <typename Func>
class scope_guard
{
private:
  bool active_;
  Func function_;

public:
  scope_guard()                         = delete;
  scope_guard(scope_guard&)             = delete;
  scope_guard& operator=(scope_guard&)  = delete;
  scope_guard& operator=(scope_guard&&) = delete;

  scope_guard(scope_guard&& sg)
    : active_(sg.active_), function_(std::move(sg.function_))
  {
    sg.active_ = false;
  }

  scope_guard(Func const& func)
    : active_(true), function_(func)
  {
  }

  scope_guard(Func&& func)
    : active_(true), function_(std::move(func))
  {
  }

  ~scope_guard()
  {
    if(active_)
      function_();
  }

  void dismiss() noexcept
  {
    active_ = false;
  }
};


template <typename Func>
scope_guard<Func> make_scope_guard(Func&& f)
{
  return scope_guard<Func>(std::forward<Func>(f));
}

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // #ifndef MRR_UTILITY_SCOPE_GUARD_
