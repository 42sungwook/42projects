#include "Replace.hpp"

int main(int ac, char **av) {
  if (ac < 4) {
    std::cout << "argument error: <filename> <string1> <string2> needed"
              << std::endl;
    return 1;
  }

  std::string filename = av[1];
  std::string str1 = av[2];
  std::string str2 = av[3];

  Replace replace(filename, str1, str2);
  replace.openInFile();
  replace.makeLine();
  replace.replaceStr();
  replace.makeOutFile();
  return 0;
}