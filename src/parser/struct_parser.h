/*
 * enum_parser.h
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

#ifndef STRUCT_PARSER_H_
#define STRUCT_PARSER_H_

#include <string>
#include <vector>
#include "data/struct_model.h"
#include "data/file_model.h"

namespace parser {

/** Parse the input given as command line arguments. store all found enums in "mystructs".
 * @param argc: command line arguments
 * @param argv: command line arguments
 * @param myfile: file model (input)
 * @param myenums: result variable (output)
 * @return 0 in case of no errors. Else return the clang error code.
 */
 int struct_parser(int argc,
 				const char **argv,
 				const data::file_model& myfile,
 				std::vector<data::struct_model> &mystructs);

} // namespace

#endif /* ENUM_PARSER_H_ */
