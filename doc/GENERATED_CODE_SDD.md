
# SDD: Generated Code
Software Design Description of the Generated Code.
## Use Cases and Requirements
Here we sketch different use cases and specify high level requirements corresponding to the use cases.

If not specified otherwise,
* the **actor** of the use cases is the programmer, who is using the generated code.
* the **precondition** is that the code generator has already generated the code and included the corresponding reflection header file.

### General Requiremens
* The software should not induce unneeded memory dynamics.

### Use Case: Enum to string conversion
 Action: | convert an enum to a string |
 ----- | ---
 **Short Description:** | The programmer has an enum value and needs to convert the value to a string.
 **Preconditions:** |
 **Steps:** | convert the value.
 **Exceptions:** | The enum value is in an illegal state (e.g. a C++98 enum has an unexpected integer value).
 **Postconditions:** | The value was converted.

Requirements:
* In error cases the conversion should throw.
* The converted enum string should match the value name in enum definition in the C++ code.

### Use Case: String to enum conversion
Action: | convert a string to an enum |
----- | ---
**Short Description:** | The programmer has a string representing an enum value and needs to convert it ot the enum value.
**Preconditions:** |
**Steps:** | convert the string.
**Exceptions:** | The string does not match any value of the enum.
**Postconditions:** | The string was converted.

Requirements:
* In error cases the conversion should throw.

### Use Case: Iterate over all possible enum values
TBD

## Structure
TBD

## Behavior
TBD
