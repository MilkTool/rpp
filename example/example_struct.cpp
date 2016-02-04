//! [using the generator]
#include <iostream>
#include <array>

// ../cpp_reflection_generator example_struct.cpp -outFilename=example_struct.h -- -x c++ -std=c++11 && g++ -std=c++11 example_struct.cpp && a.out
// cd example && ../cpp_reflection_generator example_struct.cpp -regexpFilter="example.*" -outFilename=example_struct.h -- -x c++ -std=c++11 && g++ -std=c++11 example_struct.cpp && ./a.out


namespace example {
    //! [defining a struct]
    template<class T>
    struct Struct { T data; };

    template<class T>
    struct Point {
        T x,y;
        std::array<float,3> rgb;
    };
    template<class T>
    struct Line {
        Struct<Point<T>> a,b;
    };
    //! [defining a struct]
    struct Example1 {
        int myIntValue;
        std::string myStringValue;
        bool myBoolValue;
    };

    template<int M>
    struct Example2i {
        std::array<int,2> values1;
        std::array<std::string,3> values2;
    };

    template<class X, int N, int M>
    struct Example2 {
        std::array<X,N> the_values;
        Struct<Example2i<M>> c;
    };
}

#include "example_struct.h"

//! [defining a visitor]
struct cout_visitor {
    template<class T, size_t N>
    void visit(const char*name, const std::array<T,N> &x) const {
        using namespace std;
        cout << name << " == [";
        for (auto v: x) cout << v << " ";
        cout << "];" << endl;
    }
    template<class T>
    void visit(const char*name, const example::Struct<T> &x) const {
        using namespace std;
        cout << name << ":"<< endl;
        reflection::for_each_attribute(x.data,*this);;
    }
    template<class T>
    void visit(const char*name, const T &x) const {
        using namespace std;
        cout << name << " == " << x << ";" << endl;
    }
};
//! [defining a visitor]

int main(int argc, const char**argv) {
    using namespace std;
    example::Example1 ex1{30775,"goto40",true};
    //example::Example2<float,2,3> ex2{0.1,0.2,1,2,"a","b","c"};
    example::Example2<float,1,3> ex2{0.1,1,2,"a","b","c"};
    cout << "struct example." << endl;
    cout_visitor v;
    reflection::for_each_attribute(ex1,v);
    reflection::for_each_attribute(ex2,v);

    //! [using the generated code]
    example::Point<int> point{1,2,0.0,0.0,1.0};
    example::Line<int>  line{10,11,0.5,0.2,1.0, 20,21,1.0,0.1,0.7};
    reflection::for_each_attribute(point,v);
    reflection::for_each_attribute(line,v);
    //! [using the generated code]
}
