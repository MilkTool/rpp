cmake_minimum_required(VERSION 2.8.4)
set(APPNAME cpp_reflection_generator)
project(${APPNAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FindCurses)

#set(LIBTOOLING_MINIMUM_VERSION "3.4")
#find_package(LibTooling ${LIBTOOLING_MINIMUM_VERSION} REQUIRED)
##find_package(LLVM REQUIRED)

set(LLVM_PATH /usr/lib/llvm-3.5)
link_directories(${LLVM_PATH}/lib)
include_directories(${LLVM_PATH}/include)

add_definitions(
-D__STDC_LIMIT_MACROS
-D__STDC_CONSTANT_MACROS
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # -fno-rtti

set(SOURCE_FILES src/main.cpp
src/generator/enum_codegenerator.cpp
src/generator/struct_codegenerator.cpp
src/parser/common_parser.cpp
src/parser/enum_parser.cpp
src/parser/struct_parser.cpp
)

include_directories(src)

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
  LLVMipa
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
