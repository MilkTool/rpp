#cmake -G"Eclipse CDT4 - Unix Makefiles" 
#cmake -G"Unix Makefiles" && make && ./clang_reflection_generator example/testfile.h -- -x c++ -std=c++11
# clang -Xclang -ast-dump -fsyntax-only -x c++ -std=c++11 example/testfile.h


######################
#./clang_reflection_generator example/testfile.h -- -x c++ -std=c++11 |pygmentize -l cpp

# Note the two dashes after we specify the source file. The additional options for the compiler are passed after the dashes rather
# than loading them from a compilation database - there just aren’t any options needed right now.
# --> automatic creation of the database can be enabled manually by adding "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)" into the CMakeLists.txt
#
# for the ec framework we created a database.
# then we can use the db from the builddir:  ~/checkouts/clang_reflection_generator/clang_reflection_generator ../../SRC/pi/diagnosis/MiniWebServer.cpp


######################
# I can iterate over the whole database?
./clang_reflection_generator -useDBFiles . |pygmentize -l cpp
