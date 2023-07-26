#include "../includes/ServerOperator.hpp"

ServerOperator::ServerOperator(std::list<Server *> serverList)
    : _shutDown(false), _serverList(serverList) {}

int ServerOperator::run()
{
    /* init kqueue & add event for server socket*/
    Kqueue kq;
    if (kq.init(_serverList) == EXIT_FAILURE)
        return EXIT_FAILURE;

    struct kevent *currEvent;
    int eventNb;
    while (1)
    {
        /*  apply changes and return new events(pending events) */
        eventNb = kq.countEvents();
        kq.clearCheckList(); // clear change_list for new changes
        for (int i = 0; i < eventNb; ++i)
        {
            currEvent = &(kq.getEventList())[i];
            if (currEvent->flags & EV_ERROR)
            {
                handleEventError(currEvent, kq);
            }
            else if (currEvent->filter == EVFILT_READ)
            {
                handleReadEvent(currEvent, kq);
            }
            else if (currEvent->filter == EVFILT_WRITE)
            {
                handleWriteEvent(currEvent, kq);
            }
            if (_shutDown == true)
                return EXIT_FAILURE;
        }
    }
}

void ServerOperator::handleEventError(struct kevent *event, Kqueue kq)
{
    std::list<Server *>::iterator it;
    (void)kq;
    for (it = _serverList.begin(); it != _serverList.end(); it++)
    {
        if (event->ident == (unsigned int)(*it)->getSocket())
        {
            std::cerr << "server socket error" << std::endl;
            _shutDown = true;
            return;
        }
    }
    std::cerr << "client socket error" << std::endl;
    (*it)->disconnectClient(event->ident);
}

void ServerOperator::handleReadEvent(struct kevent *event, Kqueue kq)
{
    std::list<Server *>::iterator it;
    // 발생한 이벤트가 어느 소켓으로 들어왔는지 찾음
    for (it = _serverList.begin(); it != _serverList.end(); it++)
    {
        // 만약 이벤트가 서버 소켓으로 들어왔다면 새로운 클라이언트 소켓을
        // 만들고, 초기화 함
        if (event->ident == (unsigned int)(*it)->getSocket())
        {
            int clientSocket;
            if ((clientSocket = accept((*it)->getSocket(), NULL, NULL)) == -1)
            {
                std::cerr << "accept() error\n";
                _shutDown = true;
                return;
            }
            std::cout << "accept new client: " << clientSocket << std::endl;
            fcntl(clientSocket, F_SETFL, O_NONBLOCK);

            /* add event for client socket - add read && write event */
            kq.changeEvents(clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0,
                            NULL);
            kq.changeEvents(clientSocket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0,
                            0, NULL);
            (*it)->setClientContents(clientSocket, "");
        }
        else if ((*it)->isExistClient(event->ident))
        {
            /* read data from client */
            char buf[1024];
            int n = read(event->ident, buf, sizeof(buf));

            if (n <= 0)
            {
                if (n < 0)
                    std::cerr << "client read error!" << std::endl;
                (*it)->disconnectClient(event->ident);
            }
            else
            {
                buf[n] = '\0';
                (*it)->setClientContents(event->ident, buf);
                std::cout << "received data from " << event->ident << ": "
                          << (*it)->getClientContents(event->ident)
                          << std::endl;
            }
        }
    }
}

void ServerOperator::handleWriteEvent(struct kevent *event, Kqueue kq)
{
    /* send data to client */
    std::list<Server *>::iterator it;
    (void)kq;
    for (it = _serverList.begin(); it != _serverList.end(); it++)
    {
        if ((*it)->isExistClient(event->ident))
        {
            if ((*it)->getClientContents(event->ident) != "")
            {
                Request req;
                Response res;
                LocationBlock *loc;

                req.parsing((*it)->getClientContents(event->ident));
                loc = getLocationBlockBy(req.getHost(), req.getPort(), req.getUri());
                if (req.getError() > 0)
                    std::cout << "fill error\n";
                // res.fillError(req.getError());
                else if (req.getProcess() == CGI)
                {
                    if (req.getMethod() == GET)
                        std::cout << "CGI GET" << std::endl;
                    else if (req.getMethod() == POST)
                        std::cout << "CGI POST" << std::endl;
                }
                else if (req.getProcess() == NORMAL)
                {
                    if (req.getMethod() == GET)
                        std::cout << "NORMAL GET" << std::endl;
                    else if (req.getMethod() == POST)
                        std::cout << "NORMAL POST" << std::endl;
                    else if (req.getMethod() == DELETE)
                        std::cout << "NORMAL DELETE" << std::endl;
                }

                if (write(event->ident, res.getResult().c_str(),
                          res.getResult().size()) == -1)
                {
                    std::cerr << "client write error!" << std::endl;
                    (*it)->disconnectClient(event->ident);
                }
                else
                    (*it)->setClientContentsClear(event->ident);
            }
        }
    }
}

std::list<ServerBlock *> ServerOperator::getServerBlockListBy(int port)
{
    std::list<Server *>::iterator it;
    for (it = _serverList.begin(); it != _serverList.end(); it++)
    {
        if ((*it)->getListen() == port)
            return (*it)->getServerBlockList();
    }
    throw std::runtime_error("location block is empty");
}

ServerBlock *ServerOperator::getServerBlockBy(std::string host, int port)
{
    std::list<ServerBlock *> serverBlockList;
    std::list<ServerBlock *>::iterator it;

    serverBlockList = getServerBlockListBy(port);
    for (it = serverBlockList.begin(); it != serverBlockList.end(); it++)
    {
        if ((*it)->getServerName() == host)
            return (*it);
    }
    return (*serverBlockList.begin());
}

LocationBlock *ServerOperator::getLocationBlockBy(std::string host, int port, std::string uri)
{
    std::list<LocationBlock *> locationBlockList;
    std::list<LocationBlock *>::iterator it;

    locationBlockList = getServerBlockBy(host, port)->getBlockList();
    for (it = locationBlockList.begin(); it != locationBlockList.end(); it++)
    {
        if ((*it)->getPath() == uri)
            return (*it);
    }
    return (*locationBlockList.begin());
}