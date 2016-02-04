#include <iostream>
#include <fstream>
#include <vector>
#include "data/enum_model.h"
#include "data/file_model.h"
#include "parser/common_parser.h"
#include "parser/enum_parser.h"
#include "parser/struct_parser.h"
#include "generator/enum_codegenerator.h"
#include "generator/struct_codegenerator.h"


/**
   \startuml
    start
    :create model variables;
    partition "parse and filter code" {
    :common_parser;
     note right
      parse command line options
      determine input files and output file
     end note
    :enum_parser;
     note right
      parse and filter enums in code
     end note
    :struct_parser;
     note right
      parse and filter structs in code
     end note
    }
    partition "generate reflection code" {
	:open file;
	:write start of header file;
	note right
	header guard,
	includes...
	end note
    :generate enum code;
    :generate struct code;
	:write start of header file;
	note right
	header guard
	end note
    }
    stop
   \enduml
*/
int main(int argc, const char **argv) {
	int ret = EXIT_SUCCESS;

	// create model variables
	// ----------------------
	std::vector<data::enum_model> myenums;
	std::vector<data::struct_model> mystructs;
	data::file_model myfile;

	// parse and filter code
	// ---------------------
	ret |= parser::common_parser(argc, argv, myfile);
	ret |= parser::enum_parser(argc, argv, myfile, myenums);
	ret |= parser::struct_parser(argc, argv, myfile, mystructs);

	// generate reflection code
	// ------------------------
	std::ofstream out(myfile.outfile_name);
	out << "#ifndef " << myfile.guard << std::endl;
	out << "#define " << myfile.guard << std::endl;
	out << "#include <stdexcept>" << std::endl;
	out << "#include <functional>" << std::endl;
	out << "#include <map>" << std::endl;
	out << std::endl;
	out << generator::generate_enum_reflection(myenums, myfile) << std::endl;
	out << generator::generate_struct_reflection(mystructs, myfile) << std::endl;
	out << "#endif" << std::endl;
	out.close();

	return ret;
}
