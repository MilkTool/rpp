/*
 * enum_codegenerator.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: goto40
 */

#include <sstream>
#include "data/enum_model.h"
#include "generator/enum_codegenerator.h"

namespace { // private code

/**
 * internal: generate a "for each possible value"-function.
 * @param mymodel: the enum model element to be generated
 * @param intend: a string (spaces) to be inserted in front of each line.
 */
std::string generate_enum_reflection_for_each(const data::enum_model &mymodel, std::string intend = "") {
	std::stringstream out;
	out << intend << "static void for_each_possible_value(std::function<void("<< mymodel.fullname <<")> f) {" << std::endl;
	for(auto value: mymodel.value_names) {
		out << intend << "  f(" << mymodel.fullname << "::" << value << ");" << std::endl;
	}
	out << intend << "}" << std::endl;
	return out.str();
}

/**
 * internal: generate a name-value map and vice versa.
 * @param mymodel: the enum model element to be generated
 * @param intend: a string (spaces) to be inserted in front of each line.
 */
std::string generate_enum_reflection_private_maps(const data::enum_model &mymodel, std::string intend ="") {
	std::stringstream out;
	out << intend << "static const std::map<" << mymodel.fullname << ", std::string>& get_value_name_map() {" << std::endl;
	out << intend << "  static std::map<" << mymodel.fullname << ", std::string> m({" << std::endl;
	for(auto value: mymodel.value_names) {
		out << intend << "    {" << mymodel.fullname << "::" << value << ", \"" << value<<"\"}," << std::endl;
	}
	out << intend << "  });" << std::endl;
	out << intend << "  return m;" << std::endl;
	out << intend << "}" << std::endl;

	out << intend << "static const std::map<std::string, " << mymodel.fullname << ">& get_name_value_map() {" << std::endl;
	out << intend << "  static std::map<std::string, " << mymodel.fullname << "> m({" << std::endl;
	for(auto value: mymodel.value_names) {
		out << intend << "    {\"" << value<<"\"," << mymodel.fullname << "::" << value << "}," << std::endl;
	}
	out << intend << "  });" << std::endl;
	out << intend << "  return m;" << std::endl;
	out << intend << "}" << std::endl;
	return out.str();
}

/**
 * internal: generate string conversion functions.
 * @param mymodel: the enum model element to be generated
 * @param intend: a string (spaces) to be inserted in front of each line.
 */
std::string generate_enum_reflection_str_functions(const data::enum_model &mymodel, std::string intend ="") {
	std::stringstream out;
	out << intend << "static const char* str("<< mymodel.fullname <<" v) {" << std::endl;
	out << intend << "  auto r = get_value_name_map().find(v);" << std::endl;
	out << intend << "  if (r!=get_value_name_map().end()) {" << std::endl;
	out << intend << "    return r->second.c_str();" << std::endl;
	out << intend << "  }" << std::endl;
	out << intend << "  else {" << std::endl;
	out << intend << "    throw std::invalid_argument(\"unexpected enum value\");" << std::endl;
	out << intend << "  }" << std::endl;
	out << intend << "}" << std::endl;

	out << intend << "static "<< mymodel.fullname <<" parse(const char* txt) {" << std::endl;
	out << intend << "  auto r = get_name_value_map().find(txt);" << std::endl;
	out << intend << "  if (r!=get_name_value_map().end()) {" << std::endl;
	out << intend << "    return r->second;" << std::endl;
	out << intend << "  }" << std::endl;
	out << intend << "  else {" << std::endl;
	out << intend << "    throw std::invalid_argument(\"text did not match any enum value representation\");" << std::endl;
	out << intend << "  }" << std::endl;
	out << intend << "}" << std::endl;

	return out.str();
}

/**
 * internal: generate stream operators.
 * howto: http://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
 * @param mymodel: the enum model element to be generated
 * @param intend: a string (spaces) to be inserted in front of each line.
 */
std::string generate_enum_reflection_free_stream_functions(const data::enum_model &mymodel, std::string intend = "") {
	std::stringstream out;
	out << intend << "std::ostream& operator<< (std::ostream& mystream, const "<< mymodel.fullname <<"& myvalue) {" << std::endl;
	out << intend << "  mystream << reflection::Enum<"<< mymodel.fullname <<">::str(myvalue);" << std::endl;
	out << intend << "  return mystream;" << std::endl;
	out << intend << "}" << std::endl;
	return out.str();
}

} // end of private code

namespace generator {

/**
 * generate code.
 * howto: http://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream
 * @param mymodel: the enum model element to be generated
 * @return the generated code
 */
std::string generate_enum_reflection(const data::enum_model &mymodel) {
	std::stringstream out;
	out << "namespace reflection {" << std::endl;
	out << "  template<>" << std::endl;
	out << "  struct Enum<" << mymodel.fullname << "> {" << std::endl;
	out << "    //using int_type  = " << mymodel.int_type_name << ";" << std::endl;
	out << "    using enum_type = " << mymodel.fullname << ";" << std::endl;
	out << generate_enum_reflection_for_each(mymodel, "    ") << std::endl;
	out << generate_enum_reflection_str_functions(mymodel, "    ") << std::endl;
	out << "  private:" << std::endl;
	out << generate_enum_reflection_private_maps(mymodel, "    ") << std::endl;
	out << "  };" << std::endl;
	out << "}" << std::endl;
	out << generate_enum_reflection_free_stream_functions(mymodel) << std::endl;
	return out.str();
}

std::string generate_enum_reflection(const std::vector<data::enum_model> &myenums, const data::file_model &myfile) {
	std::stringstream out;
	out << "namespace reflection {" << std::endl;
	out << "  template<class T>" << std::endl;
	out << "  struct Enum {};" << std::endl;
	out << "}" << std::endl;
	for(auto m: myenums) {
		out << std::endl;
		out << "// ---------------------------" << std::endl;
		out << "// " << m.str() << std::endl;
		out << "// ---------------------------" << std::endl;
		out << generate_enum_reflection(m) << std::endl;
	}
	return out.str();
}

} // namespace
