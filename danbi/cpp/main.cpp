#include "Kqueue.hpp"
#include "Server.hpp"

int main() {
  /* init server socket and listen */
  Server server;
  if (server.init() == EXIT_FAILURE) return EXIT_FAILURE;

  /* init kqueue & add event for server socket*/
  Kqueue kqueue;
  kqueue.init(server.getSocket());

  /* main loop */
  server.run(kqueue);

  return (0);
}