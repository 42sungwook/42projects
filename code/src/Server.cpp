#include "../includes/Server.hpp"

Server::Server(t_serverInfo *serverBlockInfo)
    : _serverBlockInfo(serverBlockInfo)
{
  _socket = -1;
};
Server::~Server(){};
int Server::getSocket() const { return _socket; }

std::vector<ServerBlock *> Server::getServerBlockList()
{
  return _serverBlockInfo->serverList;
}

int Server::getListen() { return _serverBlockInfo->listen; }

int Server::init()
{
  if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
  {
    std::cout << "socket() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  // config 세팅
  fcntl(_socket, F_SETFL, O_NONBLOCK);

  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(_serverBlockInfo->listen);
  std::cout << "listen: " << _serverBlockInfo->listen << std::endl;

  if (bind(_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
  {
    std::cout << "bind() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }

  if (listen(_socket, 5) == -1)
  {
    std::cout << "listen() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  return (EXIT_SUCCESS);
}
