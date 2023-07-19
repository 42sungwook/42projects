#include "Parser.hpp"
#include <sstream>

Parser::Parser(std::string &path) : _key(), _value(), _error(true)
{
	_start = 0;
	_pos = 0;
	readConfig(path);
	if (_line.empty())
		return;
	parseRootBlock();
}

Parser::~Parser() {}

void Parser::readConfig(std::string &path)
{
	//	std::string buf;
	//	std::ifstream filestream(path.c_str());
	//
	//	if (!filestream.is_open()) {
	//		std::cerr << "Error: " << strerror(errno) << std::endl;;
	//	}
	//	while (getline(filestream, buf)) {
	//		if (!filestream.eof())
	//			_line += '\n';
	//		else
	//			break;
	//	}
	//	std::cout <<"<" << _line<<">" << std::endl;
	std::ifstream filestream(path.c_str());
	if (!filestream.is_open())
	{
		std::cerr << "error" << std::endl;
		return;
	}
	std::stringstream buffer;
	buffer << filestream.rdbuf();
	_line = buffer.str();
}

void Parser::parseRootBlock()
{
	_root = new RootBlock();
	while (true)
	{
		setKey();
		if (_key == "server")
		{
			parseServerBlock();
			continue;
		}
		setValue();
		if (_key.empty() || _value.empty())
			break;
		_root->setKeyVal(_key, _value);
	}
}

void Parser::parseServerBlock()
{
	if (!skipBracket())
		return;
	ServerBlock *server = new ServerBlock();
	while (true)
	{
		setKey();
		if (_key == "}")
			break;
		if (_key == "location")
		{
			parseLocationBlock(server);
			continue;
		}
		setValue();
		if (_key.empty() || _value.empty())
			break;
		server->setKeyVal(_key, _value);
	}
	_root->addServerBlock(server);
}

void Parser::parseLocationBlock(ServerBlock *server)
{
	LocationBlock *location = new LocationBlock();
	setKey();
	location->setKeyVal("path", _key);
	if (!skipBracket())
		return;
	while (true)
	{
		setKey();
		if (_key == "}")
			break;
		setValue();
		if (_key.empty() || _value.empty())
			break;
		location->setKeyVal(_key, _value);
	}
	server->addLocationBlock(location);
}

bool Parser::skipBracket()
{
	_pos = _line.find_first_of("{", _pos);
	if (_pos == std::string::npos)
		return false;
	_start = _line.find_first_of("}", _pos);
	if (_start == std::string::npos)
		return false;
	++_pos;
	return true;
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
	++_pos;
}

RootBlock *Parser::getRootBlock()
{
	return _root;
}

bool Parser::getState() const
{
	return _error;
}
