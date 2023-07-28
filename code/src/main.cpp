#include "../includes/Kqueue.hpp"
#include "../includes/Parser.hpp"
#include "../includes/RootBlock.hpp"
#include "../includes/Server.hpp"
#include "../includes/ServerOperator.hpp"

void test(t_serverInfo *info) {
  std::cout << "===========INFO===========" << std::endl;
  std::cout << "listen: " << info->listen << std::endl;

  std::vector<ServerBlock *>::iterator it;
  std::cout << std::endl;
  for (it = info->serverList.begin(); it != info->serverList.end(); it++)
    (*it)->test();
}

int main(int ac, char **av) {
  if (ac != 2) {
    std::cout << "Invalid Arguments" << std::endl;
    return 1;
  }
  RootBlock *root = config(av[1]);
  root->test();

  std::vector<t_serverInfo *> info = root->getServerInfoList();

  std::vector<t_serverInfo *>::iterator it;
  std::cout << std::endl;
  std::vector<Server *> serverList;
  for (it = info.begin(); it != info.end(); it++) {
    Server *server = new Server((*it));
    if (server->init() == EXIT_FAILURE) return EXIT_FAILURE;
    serverList.push_back(server);
    // test((*it));
  }
  ServerOperator op(serverList);
  op.run();
  return (0);
}