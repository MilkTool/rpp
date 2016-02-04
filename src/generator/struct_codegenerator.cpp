/*
 * struct_codegenerator.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

#include <sstream>
#include "data/struct_model.h"
#include "generator/struct_codegenerator.h"

namespace { // private code

/**
 * internal: generate a "for each possible value"-function.
 * @param mymodel: the struct model element to be generated
 * @param intend: a string (spaces) to be inserted in front of each line.
 */
std::string generate_struct_reflection_for_each(const data::struct_model &mymodel, std::string intend = "") {
	std::stringstream out;

	for (auto const_str: {"","const"})
	{
		if (mymodel.is_a_template) {
			out << intend << "template<"<< mymodel.template_declaration <<", class VISITOR>" << std::endl;
		}
		else {
			out << intend << "template<class VISITOR>" << std::endl;
		}
		out << intend << "void for_each_attribute(typename "<< mymodel.fullname << " " << const_str <<" &data, VISITOR &v) {" << std::endl;
		for(auto name: mymodel.attribute_names) {
			out << intend << "  v.visit(\""<< name << "\", data." << name << ");" << std::endl;
		}
		out << intend << "}" << std::endl;
	}
	return out.str();
}

/**
 * internal: generate stream operators.
 * howto: http://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
 * @param mymodel: the struct model element to be generated
 * @param intend: a string (spaces) to be inserted in front of each line.
 */
std::string generate_struct_reflection_free_stream_functions(const data::struct_model &mymodel, std::string intend = "") {
	std::stringstream out;
	if (mymodel.is_a_template) {
		out << intend << "template<"<< mymodel.template_declaration <<">" << std::endl;
	}
	out << intend << "std::ostream& operator<< (std::ostream& mystream, const "<< mymodel.fullname <<"& myvalue) {" << std::endl;
	//out << intend << "  mystream << reflection::struct<"<< mymodel.fullname <<">::str(myvalue);" << std::endl;
	out << intend << "  return mystream;" << std::endl;
	out << intend << "}" << std::endl;
	return out.str();
}

} // end of private code

namespace generator {

/**
 * generate code.
 * howto: http://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
 * @param mymodel: the struct model element to be generated
 * @return the generated code
 */
std::string generate_struct_reflection(const data::struct_model &mymodel) {
	std::stringstream out;
	out << "namespace reflection {" << std::endl;
	out << generate_struct_reflection_for_each(mymodel, "    ") << std::endl;
	out << "}" << std::endl;
	//out << generate_struct_reflection_free_stream_functions(mymodel) << std::endl;
	return out.str();
}

std::string generate_struct_reflection(const std::vector<data::struct_model> &mystructs, const data::file_model &myfile) {
	std::stringstream out;
	//out << "namespace reflection {" << std::endl;
	//out << "  template<class T>" << std::endl;
	//out << "  struct Struct { T data; };" << std::endl;
	//out << "}" << std::endl;
	for(auto m: mystructs) {
		out << std::endl;
		out << "// ---------------------------" << std::endl;
		out << "// " << m.str() << std::endl;
		out << "// ---------------------------" << std::endl;
		out << generate_struct_reflection(m) << std::endl;
	}
	return out.str();
}

} // namespace
