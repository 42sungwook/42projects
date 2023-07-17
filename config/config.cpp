// root block
// server block
// location block

// mime
//

#include <iostream>
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
}
