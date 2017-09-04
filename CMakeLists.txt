cmake_minimum_required(VERSION 2.8.4)
set(APPNAME cpp_reflection_generator)
project(${APPNAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FindCurses)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_definitions(
-D__STDC_LIMIT_MACROS
-D__STDC_CONSTANT_MACROS
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # -fno-rtti

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

link_directories(${LINK_DIRECTORIES} ${LLVM_LIBRARY_DIR})
include_directories(${INCLUDE_DIRECTORIES} ${LLVM_INCLUDE_DIRS} src)

add_executable(${APPNAME} ${SOURCE_FILES})

target_link_libraries(${APPNAME}
  clangFrontend
  clangSerialization
  clangDriver
  clangParse
  clangSema
  clangAnalysis
  clangAST
  clangBasic
  clangEdit
  clangLex
  clangTooling
  clangASTMatchers
)

target_link_libraries(${APPNAME}
  LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
  LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
  LLVMX86AsmPrinter # MC, Support, X86Utils
  LLVMX86Info # MC, Support, Target
  LLVMX86Utils # Core, Support
  LLVMipo
  LLVMScalarOpts
  LLVMInstCombine
  LLVMTransformUtils
  LLVMAnalysis
  LLVMTarget
  LLVMOption # Support
  LLVMMCParser # MC, Support
  LLVMMC # Object, Support
  LLVMObject # BitReader, Core, Support
  LLVMBitReader # Core, Support
  LLVMCore # Support
  LLVMSupport
)

target_link_libraries(${APPNAME}
    pthread
    z
    dl
    ${CURSES_LIBRARIES}
)
