#include "Server.hpp"

Server::Server() {
  _socket = 0;
  memset(&_serverAddr, 0, sizeof(_serverAddr));
}

Server::~Server() {}

int Server::init(/*config*/) {
  if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    std::cout << "socket() error\n"
              << std::string(strerror(errno)) << std::endl;
    return EXIT_FAILURE;
  }
  // config 세팅
  _serverAddr.sin_family = AF_INET;
  _serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  _serverAddr.sin_port = htons(8080);

  if (bind(_socket, (struct sockaddr *)&_serverAddr, sizeof(_serverAddr)) ==
      -1) {
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

int Server::run() {
  /* init kqueue & add event for server socket*/
  Kqueue kq;
  if (kq.init(_socket) == EXIT_FAILURE) return EXIT_FAILURE;

  struct kevent *currEvent;
  int eventNb;

  while (1) {
    /*  apply changes and return new events(pending events) */
    eventNb = kq.countEvents();
    kq.clearCheckList();  // clear change_list for new changes

    for (int i = 0; i < eventNb; ++i) {
      currEvent = &(kq.getEventList())[i];

      /* check error event return */
      if (currEvent->flags & EV_ERROR) {
        if (currEvent->ident == _socket) {
          std::cerr << "server socket error" << std::endl;
          return EXIT_FAILURE;
        } else {
          std::cerr << "client socket error" << std::endl;
          kq.disconnectClient(currEvent->ident, kq.getClients());
        }
      } else if (currEvent->filter == EVFILT_READ) {
        if (currEvent->ident == _socket) {
          /* accept new client */
          int clientSocket;

          if ((clientSocket = accept(_socket, NULL, NULL)) == -1) {
            std::cerr << "accept() error\n";
            return EXIT_FAILURE;
          }
          std::cout << "accept new client: " << clientSocket << std::endl;
          fcntl(clientSocket, F_SETFL, O_NONBLOCK);

          /* add event for client socket - add read && write event */
          kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0,
                          NULL);
          kq.changeEvents(clientSocket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0,
                          NULL);
          kq.getClients()[clientSocket] = "";
        } else if (kq.getClients().find(currEvent->ident) !=
                   kq.getClients().end()) {
          /* read data from client */
          char buf[1024];
          int n = read(currEvent->ident, buf, sizeof(buf));

          if (n <= 0) {
            if (n < 0) std::cerr << "client read error!" << std::endl;
            kq.disconnectClient(currEvent->ident, kq.getClients());
          } else {
            buf[n] = '\0';
            kq.getClients()[currEvent->ident] += buf;
            std::cout << "received data from " << currEvent->ident << ": "
                      << kq.getClients()[currEvent->ident] << std::endl;
          }
        }
      } else if (currEvent->filter == EVFILT_WRITE) {
        /* send data to client */
        std::map<int, std::string>::iterator it =
            kq.getClients().find(currEvent->ident);
        if (it != kq.getClients().end()) {
          if (kq.getClients()[currEvent->ident] != "") {
            Request req;
            Response res;
            req.parsing(kq.getClients()[currEvent->ident]);
            if (req.getError() > 0) std::cout << "fill error\n";
            // res.fillError(req.getError());
            else if (req.getProcess() == CGI) {
              if (req.getMethod() == GET)
                std::cout << "CGI GET" << std::endl;
              else if (req.getMethod() == POST)
                std::cout << "CGI POST" << std::endl;
            } else if (req.getProcess() == NORMAL) {
              if (req.getMethod() == GET)
                std::cout << "NORMAL GET" << std::endl;
              else if (req.getMethod() == POST)
                std::cout << "NORMAL POST" << std::endl;
              else if (req.getMethod() == DELETE)
                std::cout << "NORMAL DELETE" << std::endl;
            }

            int n;
            if ((n = write(currEvent->ident, res.getResult().c_str(),
                           res.getResult().size()) == -1)) {
              std::cerr << "client write error!" << std::endl;
              kq.disconnectClient(currEvent->ident, kq.getClients());
            } else
              kq.getClients()[currEvent->ident].clear();
          }
        }
      }
    }
  }
}
