#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>
#include <functional>
#include <map>
#include <algorithm> // for std::transform
#include <cctype>		 // for std::tolower

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
