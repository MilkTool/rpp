/*! \mainpage Introduction
The reflection generator is used to generate C++ code to provide meta
information about C++ elements, such as enums or structs.
### Enums
 - Defining an enum:
   \snippet enum_testfile.h defining an enum

 - Generating reflection code: reflection::Enum<mytest::oknotok>

 - Using the generated code:
   \snippet example.cpp using the generator
   This code generates an output:
   \verbatim
green is ok
red is not_ok
\endverbatim

### Structs
 - Defining an struct:
   \snippet example_struct.cpp defining a struct

 - Generating reflection code: example_struct.h

 - Defining an visitor:
   \snippet example_struct.cpp defining a visitor

 - Using the generated code:
   \snippet example_struct.cpp using the generated code
   This code generates an output:
   \verbatim
x == 1;
y == 2;
rgb == [0 0 1 ];
a:
x == 10;
y == 11;
rgb == [0.5 0.2 1 ];
b:
x == 20;
y == 21;
rgb == [1 0.1 0.7 ];
\endverbatim
*/

/**
\page SDD Software Design Descriptions
The design of the presenetd software is two fold:
the design of the code generator and the design of the generated code.
- \subpage SDD_Code_Generator
- \subpage SDD_Generated_Code
*/

/**
\page SDD_Code_Generator SDD Code Generator
 - All Code Generator aspects are implemented in namespaces \ref data, \ref parser, and \ref generator
   and main.cpp.
 - The Code Generator **behavior** is described as follow (compare main.cpp)
   - **Parse** the code
   - Store the parsed data in the **Data Model**
   - **Generate code** from the data model.

\section section_data_model The Data Model
The \ref data is described by
- An output file (with additional input filter specification): data::file_model
- An enum description (for each enum): data::enum_model
- An struct description (for each struct/class): data::struct_model

\section section_parser The Code Parser
The code \ref parser task is delegated to the clang tooling library. We also
employ the command line argument parser of this framework.
- common_parser.h parses the command line arguments and prepares
the clang modules for further code parsing.
- enum_parser.h contains classes to parse enums,
  enum_parser.cpp contains additioal helper classes.
- struct_parser.h contains classes to parse structs,
  struct_parser.cpp contains additioal helper classes.

\section section_generator The Code Generator
The idea is that this part (the \ref generator) of the software is easily maintained, extended or
exchanged. Thus, the model information can be used for any other code generation
task.
- enum_codegenerator.h contains functions to generate refelction code from the
data model.
  enum_codegenerator.cpp contains additional helper functions.
*/

/**
\page SDD_Generated_Code SDD Generated Code
### Enums
 - All enum tools are contained in reflection::Enum, where the template
 parameter specifies the underying enum type.
 - The each Enum struct has the following capabilities:
   - Type information
   - introspection of possible enum values
   - parse and str conversion functions.
 - A std::stream convienience operator<< is defined to easily output an
 enum value on a stream
 - Example: reflection::Enum<mytest::oknotok>

### Structs
 - For every struct a for_each_attribute which visits all attributes of a struct.
 - Usage: The visitor is reponsible to handle the types of all attributes passed
   the visitor (visit method).
*/
