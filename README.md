# C++ Reflection Generator
The reflection generator is used to generate C++ code to provide meta information about C++ elements, such as enums or structs.

The reflection code allows
 * for enums:
   * converting enum values to/from strings
   * iterating over all possible enum values
 * for structs
   * iterating over all attributes of a struct (visitor-pattern-like)

[See Doxygen docu for more information](http://goto40.github.io/rpp/)

## Project state
alpha
 * buildscript depends on clang/llvm folder (to be specified)
 * no test scripts

## Build
* Call ./build.sh to build the software.
* See [this page](doc/BUILD.md) for more details.
