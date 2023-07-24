#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
#include "./RootBlock.hpp"
#include "./ServerBlock.hpp"
#include "./LocationBlock.hpp"

#define ISSPACE " \t\n\r\f\v"
#define SEMICOLON ";"

enum BLOCK
{
	ROOT,
	SERVER,
	LOCATION
};

class Parser
{
private:
	std::size_t _pos;
	std::size_t _start;
	std::string _key;
	std::string _value;
	std::string _line;
	RootBlock *_root;
	bool _error;

private:
	void setKey();
	void setValue();
	void readConfig(std::string &path);
	void parseRootBlock();
	void parseServerBlock();
	void parseLocationBlock(ServerBlock *server);
	bool skipBracket();

	void parseBlock(std::stack<enum BLOCK> &stack);
	void addBlock(enum BLOCK type);
	void setKeyVal(enum BLOCK type);

public:
	Parser(std::string &path);
	~Parser();
	RootBlock *getRootBlock();

	bool getState() const;
};

#endif
