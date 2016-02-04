#ifndef COMMON_PARSER_H
#define COMMON_PARSER_H
#include "clang/Tooling/CommonOptionsParser.h"
#include "data/file_model.h"

namespace parser {

/** here, we hide some global variabes shared by all parsers.
These variables are used to parse and represent the command
line options.
*/
namespace clangstuff {

/** Apply a custom category to all command-line options so that they are the
 * only ones displayed.
 */
extern llvm::cl::OptionCategory MyToolCategory;

/** command line option */
extern llvm::cl::opt<bool> useDBFiles;
/** command line option */
extern llvm::cl::opt<std::string> outFilename;
/** command line option */
extern llvm::cl::opt<std::string> regexpFilter;

/** CommonOptionsParser declares HelpMessage with a description of the common
 * command-line options related to the compilation database and input files.
 * It's nice to have this help message in all tools.
 */
extern llvm::cl::extrahelp CommonHelp;

/** A help message for this specific tool can be added afterwards. */
extern llvm::cl::extrahelp MoreHelp;

extern clang::tooling::CommonOptionsParser* OptionsParser;

}

/** Main entry point of the enum parser. */
int common_parser(int argc,
				const char **argv,
				data::file_model& myfile);

} // namespace
#endif
