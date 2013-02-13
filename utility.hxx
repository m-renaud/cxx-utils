#ifndef MRR_CXX_UTILS_UTILITLY_HXX_
#define MRR_CXX_UTILS_UTILITLY_HXX_

#include <ios>
#include <sstream>


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

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

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


#endif // MRR_CXX_UTILS_UTILITLY_HXX_
