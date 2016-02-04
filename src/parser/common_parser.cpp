#include <iostream>
#include "clang/Tooling/CommonOptionsParser.h"
#include "data/file_model.h"

namespace parser {

using namespace std;
using namespace llvm;
using namespace clang::tooling;
using namespace data;

namespace clangstuff {

/** Apply a custom category to all command-line options so that they are the
 * only ones displayed.
 */
llvm::cl::OptionCategory MyToolCategory(
		"clang_reflection_generator options");

/** command line option */
llvm::cl::opt<bool> useDBFiles("useDBFiles", cl::desc("with this switch all files from the compilation database are processed.\nThe compilation database can be created with cmake using 'set(CMAKE_EXPORT_COMPILE_COMMANDS ON)'"), cl::cat(MyToolCategory));
/** command line option */
llvm::cl::opt<std::string> outFilename("outFilename", cl::desc("specify the output filename"), cl::init("reflection.h"), cl::value_desc("filename"), cl::cat(MyToolCategory));
/** command line option */
llvm::cl::opt<std::string> regexpFilter("regexpFilter", cl::desc("filter enum (type names)"), cl::init(".*"), cl::value_desc("regexp"), cl::cat(MyToolCategory));

/** CommonOptionsParser declares HelpMessage with a description of the common
 * command-line options related to the compilation database and input files.
 * It's nice to have this help message in all tools.
 */
llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

/** A help message for this specific tool can be added afterwards. */
llvm::cl::extrahelp MoreHelp(
		R"(
This tools allows to extract reflection information
from a code base and create reflection code for enums.
)");

CommonOptionsParser* OptionsParser;
}

int common_parser(int argc,
				const char **argv,
				data::file_model& myfile) {
	int ret = EXIT_SUCCESS;
	using namespace parser::clangstuff;
	try
	{
		OptionsParser = new CommonOptionsParser(argc, argv, MyToolCategory);
		//std::cout << "outFilename=" << outFilename.getValue() << std::endl;
		//std::cout << "useDBFiles=" << useDBFiles.getValue() << std::endl;
		myfile.outfile_name=outFilename.getValue();
		myfile.regexp_filter=regexpFilter.getValue();
		// compute guard (from filename)
		myfile.guard = myfile.outfile_name;
		std::transform(myfile.guard.begin(), myfile.guard.end(),
			myfile.guard.begin(), [](char c) -> char {
				if (not ::isalnum(c)) {
					return '_';
				}
				else {
					return static_cast<char>(::toupper(c));
				}
			});
		// end compute guard
	}
	catch(std::exception& ex) {
		cerr << ex.what() << endl;
		return EXIT_FAILURE;
	}
	return ret;
}

} // namespace
