#include "../includes/Server.hpp"

Server::Server(int port, SPSBList *sbList)
    : _socket(-1), _listenPort(port), _sbList(sbList) {}

Server::~Server() {}

int Server::init() {
  if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    std::cout << "socket() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  // TODO setsockopt 지우기
  int opt = 1;
  if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  // config 세팅
  fcntl(_socket, F_SETFL, O_NONBLOCK);

  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(this->_listenPort);
  std::cout << "listen: " << this->_listenPort << std::endl;

  if (bind(_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    std::cout << "bind() error\n" << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }

  if (listen(_socket, 5) == -1) {
    std::cout << "listen() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int Server::getSocket() const { return _socket; }
int Server::getListenPort() const { return _listenPort; }
SPSBList *Server::getSPSBList() const { return _sbList; }
