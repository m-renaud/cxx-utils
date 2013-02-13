#ifndef MRR_STATE_HXX_
#define MRR_STATE_HXX_

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <typename... TS>
class state
{
public:
  using state_type = std::tuple<TS...>;


  state() = default;
  state(state const& ) = default;
  state(state&& ) = default;
  state& operator =(state const& ) = default;
  state& operator =(state&& ) = default;
  ~state() = default;

  // Create a state from a list of arguments.
  state(TS&&... vars)
    : s_(std::move(vars)...)
  {
  }

  // Create a state from an appropriate tuple.
  state(state_type const& tup)
    : s_(tup)
  {
  }

  // Restore the context
  state_type const& restore_state() const
  {
    return s_;
  }

private:
  state_type s_;
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

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // MRR_STATE_HXX_
