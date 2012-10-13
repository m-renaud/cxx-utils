#ifndef MRR_MODULO_HXX_
#define MRR_MODULO_HXX_

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

template <int N, typename IntType = unsigned long long>
struct modulo
{
  using value_type = IntType;

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo(int v)
    : val(v%N)
  {
  }

  modulo(modulo<N> const& mv)
    : val(mv)
  {
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo<N>& operator +=(modulo<N> const& rhs)
  {
    val = (val + rhs.val) % N;
    return *this;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo<N>& operator -=(modulo<N> const& rhs)
  {
    if(val < rhs.val)
      val+=N;
    val -= rhs.val;
    return *this;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo<N>& operator *=(modulo<N> const& rhs)
  {
    val = (val * rhs.val) % N;
    return *this;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  const modulo<N> operator +(int const& rhs)
  {
    return (modulo<N>(*this) += rhs);
  }

  const modulo<N> operator +(modulo<N> const& rhs)
  {
    return (modulo<N>(*this) += rhs);
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  const modulo<N> operator -(int const& rhs)
  {
    return (modulo<N>(*this) -= rhs);
  }

  const modulo<N> operator -(modulo<N> const& rhs)
  {
    return (modulo<N>(*this) -= rhs);
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  const modulo<N> operator *(int const& rhs)
  {
    return (modulo<N>(*this) *= rhs);
  }

  const modulo<N> operator *(modulo<N> const& rhs)
  {
    return (modulo<N>(*this) *= rhs);
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  modulo<N>& operator =(modulo<N> const& rhs)
  {
    val = rhs.val;
    return *this;
  }


  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  bool operator ==(int const& rhs)
  {
    return val == modulo<N>(rhs);
  }

  bool operator ==(modulo<N> const& rhs)
  {
    return val == rhs.val;
  }

  //m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  bool operator !=(int const& rhs)
  {
    return !(*this == modulo<N>(rhs));
  }

  bool operator !=(modulo<N> const& rhs)
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
