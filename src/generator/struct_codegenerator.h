/*
 * struct_codegenerator.h
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

#ifndef STRUCT_CODEGENERATOR_H_
#define STRUCT_CODEGENERATOR_H_

#include <vector>
#include "data/struct_model.h"
#include "data/file_model.h"

namespace generator {

/** generate the code for one single struct.
  @param mymodel the struct to be generated.
 */
std::string generate_struct_reflection(const data::struct_model &mymodel);
/** generate the code for a set of structs.
  @param mystructs the collection of structs to be generated.
 */
std::string generate_struct_reflection(const std::vector<data::struct_model> &mystructs, const data::file_model &myfile);

} // namespace

#endif /* struct_CODEGENERATOR_H_ */
