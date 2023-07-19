#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <map>
#include <list>
#include <iostream>
#include "LocationBlock.hpp"

class ServerBlock
{
private:
	int _listen;
	std::string _root;
	std::string _index;
	std::string _serverName;
	unsigned long _clientMaxBodySize;
	// CgiType _cgi;
	std::list<LocationBlock *> _locationList;

public:
	ServerBlock();
	~ServerBlock();

	void setListen(std::string value);
	void setRoot(std::string value);
	void setIndex(std::string value);
	void setServerName(std::string value);
	void setClientMaxBodySize(std::string value);
	//		void setCgi(std::string value);
	void setKeyVal(std::string key, std::string value);
	void addLocationBlock(LocationBlock *location);

	std::list<LocationBlock *> getBlockList();

	void test(); // TODO test
};

#endif
