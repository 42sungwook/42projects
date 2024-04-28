#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>
#include <algorithm> // for std::transform
#include <cctype>		 // for std::tolower

#define LEVELS 4

struct ToLower
{
	char operator()(char c) const
	{
		return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
	}
};

class Harl
{
private:
	static const int NUM_LEVELS = 4;
	typedef void (Harl::*LevelFunction)();

	LevelFunction levelFunctions[NUM_LEVELS];

	void debug();
	void info();
	void warning();
	void error();

public:
	Harl();
	void complain(std::string level);
};

#endif
