#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include "RootBlock.hpp"
#include "ServerBlock.hpp"
#include "LocationBlock.hpp"

#define ISSPACE " \t\n\r\f\v"
#define SEMICOLON ";"

class Parser
{
private:
	std::size_t _pos;
	std::size_t _start;
	std::string _key;
	std::string _value;

public:
	Parser(std::string &line);
	~Parser();

	void setKey(std::string &line);
	std::string getKey() const;
	void setValue(std::string &line);
	std::string getValue() const;
	void parseRootBlock(std::string &line, RootBlock *root);
	void parseSeverBlock(std::string &line, ServerBlock *server);
	void parserLocationBlock(std::string &line, LocationBlock *location);
};

#endif
