/*
 * enum_model.h
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

#include <string>
#include <vector>
#include <initializer_list>
#include <sstream>

#ifndef ENUM_MODEL_H
#define ENUM_MODEL_H

namespace data {

/** enum model */
struct enum_model {
	/** constructor.
	@param p_fullname the enum typename including namespace
	@param p_int_typ_name the name of the underlying integer type
	*/
	enum_model(std::string p_fullname, std::string p_int_typ_name)
		: fullname(p_fullname), sourcefile("<unknown>"),
			int_type_name(p_int_typ_name), the_namespace("") {
		int p = fullname.rfind("::");
		if (p!=-1) {
			the_namespace = fullname.substr(0,p);
		}
	}
	std::string fullname;                  /// the enum typename including namespace
	std::string sourcefile;                /// the source file (origin)
	std::string int_type_name;             /// the name of the underlying integer type
	std::string the_namespace;             /// the namespace of the underlying enum type
	std::vector<std::string> value_names;  /// all possible enum values (names)

	/** returns a readable compressed representation of the enum */
	std::string str() {
		std::stringstream out;
		out << "" << fullname << " : " << int_type_name << " ( ";
		for(auto a: value_names) {
			out << a << " ";
		}
		out << ") @ "<< sourcefile;
		return out.str();
	}
};

} // namespace

#endif
