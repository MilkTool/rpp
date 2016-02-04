/*
Generate my reflection class manually:
../cpp_reflection_generator example2.cpp -regexpFilter="std::errc" -outFilename=example2.h -- -x c++ -std=c++11
Compile me:
  g++ -std=c++11 example2.cpp
Run me:
  ./a.out
*/

//! [using the generator]
#include <system_error>
#include <iostream>
#include "example2.h"

int main(int argc, const char**argv) {
    using namespace std;
    cout << "All possible values of std::errc:" << endl;
    reflection::Enum<std::errc>::for_each_possible_value([](std::errc x) {
        cout << " - " << x << endl;
    });
}
//! [using the generator]
