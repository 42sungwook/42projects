all:
	c++ -Wall -Werror -Wextra -g -fsanitize=address config.cpp Parser.cpp block/LocationBlock.cpp block/ServerBlock.cpp block/RootBlock.cpp -I. -Iblock -o config

clean:
	rm -rf config
