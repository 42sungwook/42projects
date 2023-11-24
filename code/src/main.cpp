#include "../includes/ConfigParser.hpp"
#include "../includes/Kqueue.hpp"
#include "../includes/RootBlock.hpp"
#include "../includes/Server.hpp"
#include "../includes/ServerOperator.hpp"

int main(int ac, char **av) {
  if (ac != 2) {
    std::cout << "Invalid Arguments" << std::endl;
    return EXIT_FAILURE;
  }
  try {
    RootBlock root;
    ConfigParser parser(av[1]);
    parser.parseBlocks(&root, ROOT);

    ServerBlockMap sbMap = parser.getServerBlockMap();
    ServerMap serverMap;

    for (ServerBlockMap::iterator it = sbMap.begin(); it != sbMap.end(); it++) {
      std::set<std::string> temp;
      bool defalutServerName = false;
      for (SPSBList::iterator spIt = (*(*it).second).begin();
           spIt != (*(*it).second).end(); spIt++) {
        if ((*spIt)->getServerName() == "") {
          if (defalutServerName == false)
            defalutServerName = true;
          else
            throw std::runtime_error("Duplicate Server Name");
        } else if (temp.find((*spIt)->getServerName()) == temp.end())
          temp.insert((*spIt)->getServerName());
        else
          throw std::runtime_error("Duplicate Server Name");
      }
      Server *newserver = new Server((*it).first, ((*it).second));
      if (newserver->init() == EXIT_FAILURE) {
        std::cout << "server init error" << std::endl;
        return EXIT_FAILURE;
      }
      serverMap[newserver->getSocket()] = newserver;
    }

    ServerOperator op(serverMap, parser.getSortedLocationMap());
    op.run();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return (0);
}
