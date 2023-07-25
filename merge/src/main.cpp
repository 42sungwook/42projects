#include "../includes/Kqueue.hpp"
#include "../includes/Parser.hpp"
#include "../includes/RootBlock.hpp"
#include "../includes/Server.hpp"

RootBlock *config(std::string path)
{
  Parser parser(path);
  RootBlock *root = parser.getRootBlock();
  return root;
}

void test(ServerInfo *info)
{
  std::cout << "===========INFO===========" << std::endl;
  std::cout << "_listen: " << info->_listen << std::endl;

  std::list<ServerBlock *>::iterator it;
  std::cout << std::endl;
  for (it = info->_serverList.begin(); it != info->_serverList.end(); it++)
    (*it)->test();
}

int main(int ac, char **av)
{
  if (ac != 2)
  {
    std::cout << "Invalid Arguments" << std::endl;
    return 1;
  }
  RootBlock *root = config(av[1]);
  //  root->test();

  std::list<ServerInfo *> info = root->getServerInfoList();

  std::list<ServerInfo *>::iterator it;
  std::cout << std::endl;
  for (it = info.begin(); it != info.end(); it++)
    test((*it));

<<<<<<< Updated upstream
  /* init server socket and listen */
  // Server server;
  //  if (server.init(root->getBlockList()) == EXIT_FAILURE) return EXIT_FAILURE;
=======
  int cntsever = root->getBlockList().size();
  Server *
      /* init server socket and listen */
      Server server;
  if (server.init(root->getBlockList()) == EXIT_FAILURE) return EXIT_FAILURE;
>>>>>>> Stashed changes

  /* main loop */
  // if (server.run() == EXIT_FAILURE) return EXIT_FAILURE;

  return (0);
}