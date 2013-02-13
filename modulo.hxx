#ifndef MRR_MODULO_HXX_
#define MRR_MODULO_HXX_

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <std::size_t N, typename IntType = unsigned long long>
struct modulo
{
  using value_type = IntType;

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo() = default;

  modulo(modulo const&) = default;
  modulo& operator =(modulo const&) = default;

  modulo(modulo&&) = default;
  modulo& operator =(modulo&&) = default;

  ~modulo() = default;


  modulo(value_type const& v)
    : val(v % N)
  {
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  void swap(modulo& other)
  {
    using std::swap;
    swap(val, other.val);
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo& operator +=(modulo const& rhs)
  {
    val = (val + rhs.val) % N;
    return *this;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo& operator -=(modulo const& rhs)
  {
    while(val < rhs.val)
      val += N;

    val -= rhs.val;
    return *this;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo& operator *=(modulo const& rhs)
  {
    val = (val * rhs.val) % N;
    return *this;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  const modulo operator +(value_type const& rhs)
  {
    return (modulo(*this) += rhs);
  }

  const modulo operator +(modulo const& rhs)
  {
    return (modulo(*this) += rhs);
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  const modulo operator -(value_type const& rhs)
  {
    return (modulo(*this) -= rhs);
  }

  const modulo operator -(modulo const& rhs)
  {
    return (modulo(*this) -= rhs);
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  const modulo operator *(value_type const& rhs)
  {
    return (modulo(*this) *= rhs);
  }

  const modulo operator *(modulo const& rhs)
  {
    return (modulo(*this) *= rhs);
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  bool operator ==(int const& rhs)
  {
    return val == modulo(rhs);
  }

  bool operator ==(modulo const& rhs)
  {
    return val == rhs.val;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  bool operator !=(int const& rhs)
  {
    return !(*this == modulo(rhs));
  }

  bool operator !=(modulo const& rhs)
  {
    return !(*this == rhs);
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  operator value_type const& () const
  {
    return val;
  }


private:
  unsigned long long val;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#endif // #ifndef MRR_MODULO_HXX_
