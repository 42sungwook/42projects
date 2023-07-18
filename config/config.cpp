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
	RootBlock *root = parser.getRootBlock();
	return (root);
}
