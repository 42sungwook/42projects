#ifndef ROOTBLOCK_HPP
#define ROOTBLOCK_HPP

#include <map>
#include <list>
#include <iostream>
#include "ServerBlock.hpp"

class RootBlock
{
private:
	std::string _user;
	std::string _include;
	int _maxConnection;
	int _workerCnt;
	std::list<ServerBlock *> _serverList;

public:
	RootBlock();
	~RootBlock();

	void setUser(std::string value);
	void setInclude(std::string value);
	void setMaxConnection(std::string value);
	void setWorkerCnt(std::string value);
	void setKeyVal(std::string key, std::string value);
	void addServerBlock(ServerBlock *server);

	std::list<ServerBlock *> getServerBlockList();

	void test(); // TODO test
};

#endif
