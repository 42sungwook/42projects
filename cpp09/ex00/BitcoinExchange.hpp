#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

class BitcoinExchange {
 public:
  BitcoinExchange();
  ~BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& other);
  BitcoinExchange& operator=(const BitcoinExchange& other);

  void exchange(const char* filename);

 private:
  std::map<std::string, float> _data;
  std::map<std::string, float> _csvData;
};

bool checkDate(const std::string& date);
std::string split(std::string str, char Delimiter);

#endif
