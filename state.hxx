#ifndef MRR_CXX_UTILS_STATE_HXX_
#define MRR_CXX_UTILS_STATE_HXX_

#include <chrono>
#include <tuple>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <typename... TS>
class state
{
public:
  using state_type = std::tuple<TS...>;
  using clock_type = std::chrono::high_resolution_clock;
  using time_point = clock_type::time_point;

  state() = default;
  state(state const& ) = default;
  state(state&& ) = default;
  state& operator =(state const& ) = default;
  state& operator =(state&& ) = default;
  ~state() = default;

  // Create a state from a list of arguments.
  state(TS&&... vars)
    : s_(std::move(vars)...), save_point_(clock_type::now())
  {
  }

  // Create a state from an appropriate tuple.
  state(state_type const& tup)
    : s_(tup), save_point_(clock_type::now())
  {
  }

  state(state_type&& tup)
    : s_(std::move(tup)), save_point_(clock_type::now())
  {
  }

  // Get the time that the state was saved at.
  time_point const& save_point()
  {
    return save_point_;
  }

  // Restore the state held in the current object.
  state_type const& restore_state() const
  {
    return s_;
  }

  // Swap current state with another state.
  void swap(state& other)
  {
    using std::swap;
    swap(s_, other.s_);
    swap(save_point_, other.save_point_);
  }

private:
  state_type s_;
  time_point save_point_;
};


template <typename... TS>
std::tuple<TS...> restore_state(state<TS...> const& st)
{
  return st.restore_state();
}

template <typename... TS>
state<TS...> save_state(TS... ts)
{
  return state<TS...>(std::move(ts)...);
}


template <typename... TS>
state<TS...> save_state(std::tuple<TS...> const& tup)
{
  return state<TS...>(tup);
}

template <typename... TS>
state<TS...> save_state(std::tuple<TS...>&& tup)
{
  return state<TS...>(std::move(tup));
}

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // MRR_STATE_HXX_
