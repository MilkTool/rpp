/*
 * enum_parser.h
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

#ifndef ENUM_PARSER_H_
#define ENUM_PARSER_H_

#include <string>
#include "data/enum_model.h"
#include "data/file_model.h"

namespace parser {

/** Parse the input given as command line arguments. store all found enums in "myenums".

\startuml
 start
:make enum model variable and filter variable 
 globally availabe in this file;
partition "determine input files" {
 if (useDBFiles) then (yes)
:use all files and settings from the compiler database;
else (no)
:use the files and compiler settings from the command line;
endif
 }
partition "parse code" {
:EnumVisitor::VisitNamedDecl;
note right
 clang AST (abstract syntax tree) visitor
end note
if (enum is found) then (yes)
 partition "EnumVisitor::process_enum" {
   if (enum name matches filter) then (yes)
  :extract enum information;
  if (number of enum entries) then (>1)
    :store enum in enum model;
      endif
 endif
   }
endif
 }
stop
\enduml

 * @param argc: command line arguments
 * @param argv: command line arguments
 * @param myenums: result variable
 * @param myfile: file model
 * @return 0 in case of no errors. Else return the clang error code.
 */
int enum_parser(int argc, const char **argv, const data::file_model& myfile, std::vector<data::enum_model> &myenums);

} // namespace

#endif /* ENUM_PARSER_H_ */
