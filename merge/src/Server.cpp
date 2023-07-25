#include "../includes/Server.hpp"

Server::Server(const int port) : _port(port){};

void Server::setServerBlockList(ServerBlock *serverBlockList) {}

const int Server::getSocket() const { return _socket; }

const std::string Server::getClientContents(int clientSock) {
  return _clients[clientSock];
}

bool Server::isExistClient(int clientSock) {
  if (_clients.find(clientSock) == _clients.end()) return false;
  return true;
}

void Server::disconnectClient(int clientSock) {
  std::cout << "client disconnected: " << clientSock << std::endl;
  close(clientSock);
  _clients.erase(clientSock);
}

void Server::setClientContentsClear(int clientSock) {
  _clients[clientSock].clear();
}

void Server::setClientContents(int clientSock, std::string buffer) {
  _clients[clientSock] += buffer;
}

std::vector<ServerBlock *> Server::getServerBlockList() { return _serverBlock; }

int Server::init(std::list<ServerBlock *> serverBlockList) {
  std::list<ServerBlock *>::iterator it;
  for (it = serverBlockList.begin(); it != serverBlockList.end(); it++) {
    if ((*it)->getListen() == _port) _serverBlock.push_back(*it);
  }

  if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    std::cout << "socket() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  // config 세팅

  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(_port);

  if (bind(_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    std::cout << "bind() error\n" << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }

  if (listen(_socket, 5) == -1) {
    std::cout << "listen() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  fcntl(_socket, F_SETFL, O_NONBLOCK);
  return (EXIT_SUCCESS);
}
