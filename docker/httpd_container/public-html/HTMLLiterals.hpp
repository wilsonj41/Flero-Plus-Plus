#ifndef HTML_LITERALS_HPP
#define HTML_LITERALS_HPP

//#if __cpp_lib_format
//#include <format>
//namespace fmt = std;
//#else
#define FMT_HEADER_ONLY
#include <fmt/format.h>
//#endif

#include <iostream>

namespace fleropp_literals {
  class FormatProxy {
    public:
      FormatProxy(std::string data) : m_data{std::move(data)} {};

      template<typename... Args>
      void operator()(Args&& ...args) {
        std::cout << fmt::format(fmt::runtime(m_data), std::forward<Args>(args)...) << '\n';
      } 
    private:
      std::string m_data;
  };

  FormatProxy operator"" _f(const char* data, std::size_t len) {
    return {data};
  }

  void operator"" _h(const char* data, std::size_t len) {
    std::cout << data << '\n';
  }
}

#endif /* HTML_LITERALS_HPP */