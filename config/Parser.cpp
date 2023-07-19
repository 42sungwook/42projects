#include "Parser.hpp"
#include <sstream>

Parser::Parser(std::string &path) : _key(), _value(), _error(true)
{
	std::stack<enum BLOCK> stack;

	_root = new RootBlock();
	_start = 0;
	_pos = 0;
	readConfig(path);
	if (_line.empty())
		return;
	stack.push(ROOT);
	parseBlock(stack);
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

void Parser::parseBlock(std::stack<enum BLOCK> &stack)
{
	ServerBlock *serverBlock;
	LocationBlock *locationBlock;

	if (stack.size() == 0)
		return;
	enum BLOCK block = stack.top();
	while (true)
	{
		setKey();
		switch (block) // key확인 및 block 생성 후 재귀
		{
		case ROOT:
			if (_key == "server")
			{
				if (!skipBracket())
					continue;
				serverBlock = new ServerBlock();
				_root->addServerBlock(serverBlock);
				stack.push(SERVER);
				parseBlock(stack);
				continue;
			}
		case SERVER:
			if (_key == "}")
			{
				stack.pop();
				return;
			}
			else if (_key == "location")
			{
				locationBlock = new LocationBlock();
				_root->getServerBlockList().back()->addLocationBlock(locationBlock);
				stack.push(LOCATION);
				setKey();
				locationBlock->setKeyVal("path", _key);
				if (!skipBracket())
					continue;
				parseBlock(stack);
				continue;
			}
		case LOCATION:
			if (_key == "}")
			{
				stack.pop();
				return;
			}
		default:
			break;
		}
		setValue();
		if (_key.empty() || _value.empty())
		{
			stack.pop();
			break;
		}
		// keyVal 넣기
		switch (block)
		{
		case ROOT:
			_root->setKeyVal(_key, _value);
			continue;
		case SERVER:
			serverBlock = _root->getServerBlockList().back();
			serverBlock->setKeyVal(_key, _value);
			continue;
		case LOCATION:
			serverBlock = _root->getServerBlockList().back();
			if (serverBlock)
			{
				locationBlock = serverBlock->getLocationBlockList().back();
				if (locationBlock)
					locationBlock->setKeyVal(_key, _value);
			}
			continue;
		default:
			break;
		}
	}
}