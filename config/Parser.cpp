#include "Parser.hpp"

Parser::Parser(std::string &line) : _start(0), _pos(0), _key(), _value() {}

Parser::~Parser() {}

void Parser::setKey(std::string &line)
{
	_key.clear();
	_start = line.find_first_not_of(ISSPACE, _pos);
	if (_start == std::string::npos)
		return;
	_pos = line.find_first_of(ISSPACE, _start);
	if (_pos == std::string::npos)
		return;
	_key = line.substr(_start, _pos - _start);
}

std::string Parser::getKey() const
{
	return _key;
}

void Parser::setValue(std::string &line)
{
	_value.clear();
	_start = line.find_first_not_of(ISSPACE, _pos);
	if (_start == std::string::npos)
		return;
	_pos = line.find_first_of(SEMICOLON, _start);
	if (_pos == std::string::npos)
		return;
	_value = line.substr(_start, _pos - _start);
}

std::string getValue() const
{
	return _value;
}

void Parser::parseRootBlock(std::string &line, RootBlock *root)
{
	while (true)
	{
		setKey(line);
		setValue(line);
		root->check(key, value);
		_pos++;
	}
}