#include "Kqueue.hpp"
#include "Server.hpp"

int main() {
  /* init server socket and listen */
  Server server;
  if (server.init() == EXIT_FAILURE) return EXIT_FAILURE;

  /* main loop */
  if (server.run() == EXIT_FAILURE) return EXIT_FAILURE;

  return (0);
}