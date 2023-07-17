#include "Parser.hpp"

Parser::Parser(std::string &path) : _error(false), _start(0), _pos(0), _key(), _value()
{
	readConfig(path);
	if (_line.empty())
		return;
	parseRootBlock();
}

Parser::~Parser() {}

void Parser::readConfig(std::string &path)
{
	std::string buf;
	std::ifstream filestream(path.c_str());

	if (!filestream.is_open())
	{
		std::cerr << "Error: " << strerror(errno) << std::endl;
		;
	}
	while (getline(filestream, buf))
	{
		if (!filestream.eof())
			_line += '\n';
		else
			break;
	}
}

void Parser::parseRootBlock()
{
	_root = new RootBlock();

	while (true)
	{
		setKey();
		setValue();
		if (_key.empty() || _value.empty())
			break;
	}
}

void Parser::setKey()
{
	_key.clear();
	_start = _line.find_first_not_of(ISSPACE, _pos);
	if (_start == std::string::npos)
		return;
	_pos = _line.find_first_of(ISSPACE, _start);
	if (_pos == std::string::npos)
		return;
	_key = _line.substr(_start, _pos - _start);
}

void Parser::setValue()
{
	_value.clear();
	_start = _line.find_first_not_of(ISSPACE, _pos);
	if (_start == std::string::npos)
		return;
	_pos = _line.find_first_of(SEMICOLON, _start);
	if (_pos == std::string::npos)
		return;
	_value = _line.substr(_start, _pos - _start);
}

RootBlock *Parser::getRootBlock()
{
	return _root;
}

bool Parser::getState() const
{
	return _error;
}
