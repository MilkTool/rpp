
# SDD: Code Generator
Software Design Description of the Code Code Generator.
## Use Cases and Requirements
Here we sketch different use cases and specify high level requirements corresponding to the use cases.

If not specified otherwise,
* the **actor** of the use cases is the makefile, who is generating code.

### General Requiremens
* The code generator should be compatible with C++14.
* The code generator should use normal C++ code as input. Additional code information (like comments or attributes) should only be considered if no other way yields the desired information.

### Use Case: Generate Enum Reflection Code
 Action: | generate enum reflection code |
 ----- | ---
 **Short Description:** | Generate reflection code for given enum definitions.
 **Preconditions:** | The files containing the definintions are avalailabe togeter with the corresponding build informations (e.g., #defines).
 **Steps:** | (1) read the definitions. <br> (2) generate the code.
 **Exceptions:** | Parse errors or code ambiguities.
 **Postconditions:** | The reflection code is generated.

Requirements:
* The code generator should read enum definitions from C++ code as input.
* In error cases the code generation should stop with an error and print a readable error text.
* The code generator should accept compiler switches from the corresponding project to generate correct refection code (the enums may be, e.g., influenced by a C++ preprocessor macro).


## Structure
The code is divided in three modules:
* Parser
* Data Model
* Code Generator

### Parser
The **parser** is mapped to the "clang LibTooling" library. This allows us
* to include compiler switches
* to embed the code generator in a cmake project to automaticaly deduce all compiler swiches.
* easily parse and interpret modern C++ code.

The **entry point** for this module is [enum_parser.h](src/enum_parser.h).

### Data Model
The **data model* is described by a C++ struct for each enum. Thus, we are decouple the data representation from the underlying parser implementation.

The **entry point** for this module is [enum_model.h](src/enum_model.h).

### Code Generator
The **code generator** depends on the data model and is designed to be easily exchanged. Thus, a different code generator for enums can easily be forked from the descibed project.

The **entry point** for this module is [enum_codegenerator.h](src/enum_codegenerator.h).

## Behavior
TBD
