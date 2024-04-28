#include "BitcoinExchange.hpp"

// map container 사용이 유리
int main(int ac, char **av) {
  if (ac != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }
  try {
    BitcoinExchange exchange;
    exchange.exchange(av[1]);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
