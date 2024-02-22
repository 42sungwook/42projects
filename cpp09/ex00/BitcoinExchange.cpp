#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
  _data = other._data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
  _data = other._data;
  return *this;
}

void BitcoinExchange::fileRead(const char* filename) {
  // 값 앞뒤로 공백 제거
  // 구분자 | 확인
}

void BitcoinExchange::fileWrite(const char* filename) {
  // Year-Month-Day 포맷 확인
  // 0 and 1000 사이 int 또는 float인지 확인
  /* If the date used in the input does not exist in your DB then you
     must use the closest date contained in your DB. Be
     careful to use the lower date and not the upper one */
  // print하기
}