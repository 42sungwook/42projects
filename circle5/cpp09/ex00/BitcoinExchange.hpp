#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class BitcoinExchange {
 private:
  std::map<std::string, float> _csvData;

 public:
  BitcoinExchange();
  ~BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& other);
  BitcoinExchange& operator=(const BitcoinExchange& other);
  void exchange(const char* filename);

 private:
  bool checkDate(const std::string& date);
};

bool checkDate(const std::string& date);
std::string split(std::string str, char Delimiter);

#endif