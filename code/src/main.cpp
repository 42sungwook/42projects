#include "../includes/Kqueue.hpp"
#include "../includes/ConfigParser.hpp"
#include "../includes/RootBlock.hpp"
#include "../includes/Server.hpp"
#include "../includes/ServerOperator.hpp"

// void test(t_serverInfo *info)
//{
//   std::cout << "===========INFO===========" << std::endl;
//   std::cout << "listen: " << info->listen << std::endl;

//  std::vector<ServerBlock *>::iterator it;
//  std::cout << std::endl;
//  for (it = info->serverList.begin(); it != info->serverList.end(); it++)
//    (*it)->test();
//}

int main(int ac, char **av)
{
  if (ac != 2)
  {
    std::cout << "Invalid Arguments" << std::endl;
    return EXIT_FAILURE;
  }
  RootBlock *root = new RootBlock;
  ConfigParser parser(av[1]);
  parser.parseBlocks(root, ROOT);
  root->test();

  ServerBlockMap serverMap = parser.getServerBlockMap();
  LocationMap locationMap = parser.getLocationMap();

  ServerBlockMap::iterator iter;

  for (iter = serverMap.begin(); iter != serverMap.end(); iter++)
  {
    SPSBList list = *(iter)->second;
    SPSBList::iterator spsbIter;
    for (spsbIter = list.begin(); spsbIter != list.end(); spsbIter++)
    {
      (*spsbIter)->test();
      LocationList locList = *locationMap[*spsbIter];
      LocationList::iterator locIter;
      for (locIter = locList.begin(); locIter != locList.end(); locIter++)
        (*locIter)->test();
    }
  }

  // for (iter = serverMap.begin(); iter != serverMap.end(); iter++)
  //{
  //   SPSBList *list = (*iter)->second;d
  // }
  //  std::vector<t_serverInfo *> info = parser.getServerBlockMap();

  // std::vector<t_serverInfo *>::iterator it;
  // std::cout << std::endl;
  // std::vector<Server *> serverList;
  // for (it = info.begin(); it != info.end(); it++)
  //{
  //   Server *server = new Server((*it));
  //   if (server->init() == EXIT_FAILURE)
  //     return EXIT_FAILURE;
  //   serverList.push_back(server);
  //   // test((*it));
  // }
  // ServerOperator op(serverList);
  // op.run();
  // return (0);
}