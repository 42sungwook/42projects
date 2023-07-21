#include "../includes/Kqueue.hpp"
#include "../includes/Parser.hpp"
#include "../includes/RootBlock.hpp"
#include "../includes/Server.hpp"

RootBlock *config(std::string path) {
  Parser parser(path);
  RootBlock *root = parser.getRootBlock();
  return root;
}

int main(int ac, char **av) {
  if (ac != 2) {
    std::cout << "Invalid Arguments" << std::endl;
    return 1;
  }
  RootBlock *root = config(av[1]);
  root->test();

  /* init server socket and listen */
  Server server;
  if (server.init(root->getBlockList()) == EXIT_FAILURE) return EXIT_FAILURE;

  /* main loop */
  if (server.run() == EXIT_FAILURE) return EXIT_FAILURE;

  return (0);
}