// root block
// server block
// location block

// mime
//

#include <iostream>
#include <fstream>
#include "RootBlock.hpp"
#include "Parser.hpp"

RootBlock *config(std::string path)
{
	Parser parser(path);
	RootBlock *root = new RootBlock();
	std::string line;
	std::string buf;
	std::size_t pos = 0;
	std::size_t start = 0;

	std::ifstream filestream(path.c_str());
	if (!filestream.is_open())
	{
		std::cerr << "Error: " << strerror(errno) << std::endl;
		exit(1);
	}

	while (getline(filestream, buf))
	{
		if (!filestream.eof())
			line += '\n';
		else
			break;
	}
	if (line.empty())
		return NULL;

	
}
