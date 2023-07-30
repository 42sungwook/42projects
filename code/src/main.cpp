#include "../includes/Kqueue.hpp"
#include "../includes/ConfigParser.hpp"
#include "../includes/RootBlock.hpp"
#include "../includes/Server.hpp"
#include "../includes/ServerOperator.hpp"

int main(int ac, char **av)
{
  if (ac != 2)
  {
    std::cout << "Invalid Arguments" << std::endl;
    return EXIT_FAILURE;
  }
  RootBlock root;
  ConfigParser parser(av[1]);
  parser.parseBlocks(&root, ROOT);
  root->test();

  ServerBlockMap sbMap = parser.getServerBlockMap();
  ServerMap serverMap;

  for (ServerBlockMap::iterator it = sbMap.begin(); it != sbMap.end(); it++)
  {
    Server *newserver = new Server((*it).first, (*it).second);
    if (serverList.back()->init() == EXIT_FAILURE)
      return EXIT_FAILURE;
    serverMap[newserver->getSocket()] = newserver;
  }

  ServerOperator op(serverMap, parser.getLocationMap());
  op.run();

  return (0);
}

  // ServerBlockMap serverMap = parser.getServerBlockMap();
  // LocationMap locationMap = parser.getLocationMap();

  // ServerBlockMap::iterator iter;

  // for (iter = serverMap.begin(); iter != serverMap.end(); iter++)
  // {
  //   SPSBList list = *(iter)->second;
  //   SPSBList::iterator spsbIter;
  //   for (spsbIter = list.begin(); spsbIter != list.end(); spsbIter++)
  //   {
  //     (*spsbIter)->test();
  //     LocationList locList = *locationMap[*spsbIter];
  //     LocationList::iterator locIter;
  //     for (locIter = locList.begin(); locIter != locList.end(); locIter++)
  //       (*locIter)->test();
  //   }
  // }

  // for (iter = serverMap.begin(); iter != serverMap.end(); iter++)
  //{
  //   SPSBList *list = (*iter)->second;d
  // }
  //  std::vector<t_serverInfo *> info = parser.getServerBlockMap();

  // std::vector<t_serverInfo *>::iterator it;
  // std::cout << std::endl;
  // std::vector<Server *> serverList;

  //   for (it = info.begin(); it != info.end(); it++)
  // {
  //   Server *server = new Server((*it));
  //   if (server->init() == EXIT_FAILURE)
  //     return EXIT_FAILURE;
  //   serverList.push_back(server);
  //   test((*it));
  // }