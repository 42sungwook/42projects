#ifndef REPLACE_HPP
#define REPLACE_HPP

#include <fstream>
#include <iostream>

class Replace {
 private:
  std::string _filename;
  std::string _str1;
  std::string _str2;
  std::string _line;
  std::ifstream *_inputFile;

 public:
  Replace(const std::string &filename, const std::string &str1,
          const std::string &str2);
  ~Replace();
  void openInFile();
  void replaceStr();
  void makeLine();
  void makeOutFile();
};

#endif
