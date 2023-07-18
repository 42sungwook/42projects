#include "block/RootBlock.hpp"
#include "Parser.hpp"

RootBlock *config(std::string path) {
	Parser parser(path);
	RootBlock *root = parser.getRootBlock();
	return root;
}

int main() {
	RootBlock *root = config("default_webserv.conf");
	root->test();
	delete root;
}