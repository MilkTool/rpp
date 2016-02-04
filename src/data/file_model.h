#ifndef FILE_MODEL_H
#define FILE_MODEL_H

#include <string>
#include <vector>

namespace data {

struct file_model {
  std::string outfile_name;                          /// the output filename
  std::string guard;                                 /// header guard
  std::string regexp_filter;                         /// regexp enum tpye name filter
  std::vector<std::string> inputs;                   /// input files
};

} // namespace

#endif
