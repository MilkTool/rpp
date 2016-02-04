#ifndef EXAMPLE_STRUCT_H
#define EXAMPLE_STRUCT_H
#include <stdexcept>
#include <functional>
#include <map>

namespace reflection {
  template<class T>
  struct Enum {};
}


// ---------------------------
// class TMPL_T struct example::template Struct<TMPL_T> { data } @ <unknown>
// ---------------------------
namespace reflection {
    template<class TMPL_T, class VISITOR>
    void for_each_attribute(typename example::template Struct<TMPL_T>  &data, VISITOR &v) {
      v.visit("data", data.data);
    }
    template<class TMPL_T, class VISITOR>
    void for_each_attribute(typename example::template Struct<TMPL_T> const &data, VISITOR &v) {
      v.visit("data", data.data);
    }

}


// ---------------------------
// class TMPL_T struct example::template Point<TMPL_T> { x y rgb } @ <unknown>
// ---------------------------
namespace reflection {
    template<class TMPL_T, class VISITOR>
    void for_each_attribute(typename example::template Point<TMPL_T>  &data, VISITOR &v) {
      v.visit("x", data.x);
      v.visit("y", data.y);
      v.visit("rgb", data.rgb);
    }
    template<class TMPL_T, class VISITOR>
    void for_each_attribute(typename example::template Point<TMPL_T> const &data, VISITOR &v) {
      v.visit("x", data.x);
      v.visit("y", data.y);
      v.visit("rgb", data.rgb);
    }

}


// ---------------------------
// class TMPL_T struct example::template Line<TMPL_T> { a b } @ <unknown>
// ---------------------------
namespace reflection {
    template<class TMPL_T, class VISITOR>
    void for_each_attribute(typename example::template Line<TMPL_T>  &data, VISITOR &v) {
      v.visit("a", data.a);
      v.visit("b", data.b);
    }
    template<class TMPL_T, class VISITOR>
    void for_each_attribute(typename example::template Line<TMPL_T> const &data, VISITOR &v) {
      v.visit("a", data.a);
      v.visit("b", data.b);
    }

}


// ---------------------------
// struct example::Example1 { myIntValue myStringValue myBoolValue } @ <unknown>
// ---------------------------
namespace reflection {
    template<class VISITOR>
    void for_each_attribute(typename example::Example1  &data, VISITOR &v) {
      v.visit("myIntValue", data.myIntValue);
      v.visit("myStringValue", data.myStringValue);
      v.visit("myBoolValue", data.myBoolValue);
    }
    template<class VISITOR>
    void for_each_attribute(typename example::Example1 const &data, VISITOR &v) {
      v.visit("myIntValue", data.myIntValue);
      v.visit("myStringValue", data.myStringValue);
      v.visit("myBoolValue", data.myBoolValue);
    }

}


// ---------------------------
// int TMPL_M struct example::template Example2i<TMPL_M> { values1 values2 } @ <unknown>
// ---------------------------
namespace reflection {
    template<int TMPL_M, class VISITOR>
    void for_each_attribute(typename example::template Example2i<TMPL_M>  &data, VISITOR &v) {
      v.visit("values1", data.values1);
      v.visit("values2", data.values2);
    }
    template<int TMPL_M, class VISITOR>
    void for_each_attribute(typename example::template Example2i<TMPL_M> const &data, VISITOR &v) {
      v.visit("values1", data.values1);
      v.visit("values2", data.values2);
    }

}


// ---------------------------
// class TMPL_X, int TMPL_N, int TMPL_M struct example::template Example2<TMPL_X,TMPL_N,TMPL_M> { the_values c } @ <unknown>
// ---------------------------
namespace reflection {
    template<class TMPL_X, int TMPL_N, int TMPL_M, class VISITOR>
    void for_each_attribute(typename example::template Example2<TMPL_X,TMPL_N,TMPL_M>  &data, VISITOR &v) {
      v.visit("the_values", data.the_values);
      v.visit("c", data.c);
    }
    template<class TMPL_X, int TMPL_N, int TMPL_M, class VISITOR>
    void for_each_attribute(typename example::template Example2<TMPL_X,TMPL_N,TMPL_M> const &data, VISITOR &v) {
      v.visit("the_values", data.the_values);
      v.visit("c", data.c);
    }

}


#endif
