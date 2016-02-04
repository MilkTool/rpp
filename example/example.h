#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <stdexcept>
#include <functional>
#include <map>

namespace reflection {
  template<class T>
  struct Enum {};
}

// ---------------------------
// mytest_xmacro::Color : unsigned int ( red blue green ) @ ...../checkouts/clang_reflection_generator/example/enum_testfile.h:31:1
// ---------------------------
namespace reflection {
  template<>
  struct Enum<mytest_xmacro::Color> {
    //using int_type  = unsigned int;
    using enum_type = mytest_xmacro::Color;
    static void for_each_possible_value(std::function<void(mytest_xmacro::Color)> f) {
      f(mytest_xmacro::Color::red);
      f(mytest_xmacro::Color::blue);
      f(mytest_xmacro::Color::green);
    }

    static const char* str(mytest_xmacro::Color v) {
      auto r = get_value_name_map().find(v);
      if (r!=get_value_name_map().end()) {
        return r->second.c_str();
      }
      else {
        throw std::invalid_argument("unexpected enum value");
      }
    }
    static mytest_xmacro::Color parse(const char* txt) {
      auto r = get_name_value_map().find(txt);
      if (r!=get_name_value_map().end()) {
        return r->second;
      }
      else {
        throw std::invalid_argument("text did not match any enum value representation");
      }
    }

  private:
    static const std::map<mytest_xmacro::Color, std::string>& get_value_name_map() {
      static std::map<mytest_xmacro::Color, std::string> m({
        {mytest_xmacro::Color::red, "red"},
        {mytest_xmacro::Color::blue, "blue"},
        {mytest_xmacro::Color::green, "green"},
      });
      return m;
    }
    static const std::map<std::string, mytest_xmacro::Color>& get_name_value_map() {
      static std::map<std::string, mytest_xmacro::Color> m({
        {"red",mytest_xmacro::Color::red},
        {"blue",mytest_xmacro::Color::blue},
        {"green",mytest_xmacro::Color::green},
      });
      return m;
    }

  };
}
std::ostream& operator<< (std::ostream& mystream, const mytest_xmacro::Color& myvalue) {
  mystream << reflection::Enum<mytest_xmacro::Color>::str(myvalue);
  return mystream;
}



// ---------------------------
// mytest::oknotok : _Bool ( ok not_ok ) @ ..../checkouts/clang_reflection_generator/example/enum_testfile.h:38:3
// ---------------------------
namespace reflection {
  template<>
  struct Enum<mytest::oknotok> {
    //using int_type  = _Bool;
    using enum_type = mytest::oknotok;
    static void for_each_possible_value(std::function<void(mytest::oknotok)> f) {
      f(mytest::oknotok::ok);
      f(mytest::oknotok::not_ok);
    }

    static const char* str(mytest::oknotok v) {
      auto r = get_value_name_map().find(v);
      if (r!=get_value_name_map().end()) {
        return r->second.c_str();
      }
      else {
        throw std::invalid_argument("unexpected enum value");
      }
    }
    static mytest::oknotok parse(const char* txt) {
      auto r = get_name_value_map().find(txt);
      if (r!=get_name_value_map().end()) {
        return r->second;
      }
      else {
        throw std::invalid_argument("text did not match any enum value representation");
      }
    }

  private:
    static const std::map<mytest::oknotok, std::string>& get_value_name_map() {
      static std::map<mytest::oknotok, std::string> m({
        {mytest::oknotok::ok, "ok"},
        {mytest::oknotok::not_ok, "not_ok"},
      });
      return m;
    }
    static const std::map<std::string, mytest::oknotok>& get_name_value_map() {
      static std::map<std::string, mytest::oknotok> m({
        {"ok",mytest::oknotok::ok},
        {"not_ok",mytest::oknotok::not_ok},
      });
      return m;
    }

  };
}
std::ostream& operator<< (std::ostream& mystream, const mytest::oknotok& myvalue) {
  mystream << reflection::Enum<mytest::oknotok>::str(myvalue);
  return mystream;
}


#endif

