#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
  std::ifstream csvFile("data.csv");
  std::string line;
  std::string date;
  float value;

  if (!csvFile) {
    throw std::runtime_error("Error: Unable to open csv file");
  }

  std::getline(csvFile, line);
  if (line != "date,exchange_rate") {
    throw std::runtime_error("Error: Invalid csv file format");
  }

  while (std::getline(csvFile, line)) {
    date = line.substr(0, line.find(','));
    value = std::stof(line.substr(line.find(',') + 1));
    if (checkDate(date) == false) {
      throw std::runtime_error("Error: Invalid csv file format2");
    }
    _csvData[date] = value;
  }
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
  _data = other._data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
  _data = other._data;
  return *this;
}

void BitcoinExchange::exchange(const char* filename) {
  std::ifstream inputFile;
  std::string line;

  inputFile.open(filename);

  if (!inputFile) {
    throw std::runtime_error("Error: Unable to open input file");
  }
  std::getline(inputFile, line);
  if (line != "date | value") {
    throw std::runtime_error("Error: Invalid input file format");
  }

  while (std::getline(inputFile, line)) {
    std::string removeSpaceLine(line);
    removeSpaceLine.erase(std::remove_if(removeSpaceLine.begin(),
                                         removeSpaceLine.end(), ::isspace),
                          removeSpaceLine.end());
    if (removeSpaceLine.find_first_of('|') != 10) {
      std::cout << "Error: bad input => " << line << std::endl;
      continue;
    }
    std::string date = removeSpaceLine.substr(0, 10);
    if (!checkDate(date)) {
      std::cout << "Error: bad input => " << date << std::endl;
      continue;
    }
    float value = std::stof(removeSpaceLine.substr(11));
    if (value < 0) {
      std::cout << "Error: not a positive number" << std::endl;
      continue;
    }
    if (value > 1000) {
      std::cout << "Error: too large a number" << std::endl;
      continue;
    }

    std::cout << date << " => " << value << " = ";
    std::map<std::string, float>::iterator it = _csvData.lower_bound(date);
    std::cout << value * it->second << std::endl;
  }
  inputFile.close();
}

bool checkDate(const std::string& date) {
  // Year-Month-Day 포맷 확인
  for (int i = 0; i < 10; i++) {
    if (i == 4 || i == 7) {
      if (date[i] != '-') {
        return false;
      }
    } else {
      if (date[i] < '0' || date[i] > '9') {
        return false;
      }
    }
  }
  unsigned int year = std::stoi(date.substr(0, 4));
  unsigned int month = std::stoi(date.substr(5, 2));
  unsigned int day = std::stoi(date.substr(8, 2));

  if (year > 9999 || month > 12 || day > 31 || month == 0 || day == 0) {
    return false;
  }

  if (month % 2 == 1 && month > 7 && day > 30) {
    return false;
  } else if (month % 2 == 0 && month < 7) {
    if (month == 2) {
      if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        if (day > 29) return false;
      } else {
        if (day > 28) return false;
      }
    } else {
      if (day > 30) return false;
    }
  }

  return true;
}