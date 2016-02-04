/*
Generate my reflection class manually:
  ../cpp_reflection_generator example.cpp -outFilename=example.h -- -x c++ -std=c++11
Compile me:
  g++ -std=c++11 example.cpp
Run me:
  ./a.out
*/

//! [using the generator]
#include <iostream>
#include "enum_testfile.h" // the enum definition
#include "example.h"       // the generated reflection code

int main(int argc, const char**argv) {
    using namespace std;
    using namespace mytest_xmacro;
    using namespace mytest;
    Color color = Color::green;
    oknotok value = oknotok::ok;
    cout << color << " is " << value << endl;
    cout << Color::red << " is " << oknotok::not_ok << endl;
}
//! [using the generator]
