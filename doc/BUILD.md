# Build
Here you find details about how to buid the software.

The tool is build using cmake.
## CMakeLists.txt
Adapt the CmakeLists.txt to find your clang and llvm installlation.
```
...
set(LLVM_PATH /usr/lib/llvm-3.5)
link_directories(${LLVM_PATH}/lib)
include_directories(${LLVM_PATH}/include)
...
```
