#include "../includes/Post.hpp"

Post::Post() {}

Post::~Post() {}

// std::string Post::generateRandomString() {
//   static std::string charset =
//       "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//   std::string result;
//   std::srand(std::time(0));

//   for (int i = 0; i < 32; ++i)
//     result.push_back(charset[std::rand() % charset.size()]);
//   return result;
// }

void Post::process(Request &request, Response &response) {
  // try {
  std::string fullUri = request.getHeaderByKey("RootDir");
  fullUri += request.getHeaderByKey("BasicURI");
  // std::string filename = fullUri;

  //   if (filename[(filename.size() - 1)] == '/') {
  //     filename += generateRandomString();
  //     std::ifstream tempif(filename);
  //     while (tempif.is_open() == true) {
  //       tempif.close();
  //       filename = fullUri;
  //       filename += generateRandomString();
  //       tempif = std::ifstream(filename);
  //     }
  //     response.setHeaders("Content-Location", filename);
  //   } else {
  //     std::ifstream tempif(filename);
  //     if (tempif.is_open() == true) {
  //       tempif.close();
  //       throw ErrorException(400);
  //     }
  //   }
  //   std::ofstream tempof(filename);
  //   _path = filename;
  Cgi cgi;
  cgi.reqToEnvp(request.getHeaderMap());
  cgi.excute(request.getBody());
  response.convertCGI(cgi.getRes());
  return;
  // } catch (ErrorException &e) {
  //   response.setErrorRes(e.getErrorCode());
  // }
}