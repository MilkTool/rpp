/*
 * enum_codegenerator.h
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

#ifndef ENUM_CODEGENERATOR_H_
#define ENUM_CODEGENERATOR_H_

#include <vector>
#include "data/enum_model.h"
#include "data/file_model.h"

namespace generator {

/** generate the code for one single enum.
  @param mymodel the enum to be generated.
 */
std::string generate_enum_reflection(const data::enum_model &mymodel);
/** generate the code for a set of enums.
  @param myenums the collection of enums to be generated.
 */
std::string generate_enum_reflection(const std::vector<data::enum_model> &myenums, const data::file_model &myfile);

} // namespace

#endif /* ENUM_CODEGENERATOR_H_ */
