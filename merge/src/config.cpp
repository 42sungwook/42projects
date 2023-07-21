#include "../includes/Parser.hpp"
#include "../includes/RootBlock.hpp"

RootBlock *config(std::string path) {
  Parser parser(path);
  RootBlock *root = parser.getRootBlock();
  return root;
}

int main() {
  RootBlock *root = config("default_webserv.conf");
  root->test();
  return 0;
}