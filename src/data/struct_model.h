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

#ifndef STRUCT_MODEL_H
#define STRUCT_MODEL_H

namespace data {

/** enum model */
struct struct_model {
	/** constructor.
	@param p_fullname the enum typename including namespace
	*/
	struct_model(std::string p_fullname)
		: fullname(p_fullname), sourcefile("<unknown>"),
			the_namespace("") {
		int p = fullname.rfind("::");
		if (p!=-1) {
			the_namespace = fullname.substr(0,p);
		}
	}
	std::string fullname;                     /// the struct typename including namespace and template attributes
	std::string fullname_without_template;    /// the struct typename including namespace
	std::string template_declaration;         /// the template command (e.g. "class X" for template<class X>)
	bool is_a_template;                       /// template? true=yes/false=no
	std::string sourcefile;                   /// the source file (origin)
	std::string the_namespace;                /// the namespace of the underlying enum type
	std::vector<std::string> attribute_names; /// all possible enum values (names)

	/** returns a readable compressed representation of the enum */
	std::string str() {
		std::stringstream out;
		if (is_a_template) {
			out << template_declaration << " ";
		}
		out << "struct " << fullname << " { ";
		for(auto a: attribute_names) {
			out << a << " ";
		}
		out << "} @ "<< sourcefile;
		return out.str();
	}
};

} // namespace

#endif
