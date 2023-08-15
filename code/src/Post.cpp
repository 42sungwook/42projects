/**
 * 1. POST 기본 동작
 *   - 없는 파일: 에러 404(임시)
 *   - 폴더 경로: 랜덤한 이름으로 생성 후, 응답에 생성 파일 이름 헤더로 전송 201
 *   - 없는 폴더: (없는 경로로 요청이 들어옴) 400
 *   - 있는 파일: append 200
 * 2. cgi cgi path 내용이 들어올 때 분기 처리 그외 에러처리
 * 3. chuncked 인코딩으로 들어왔을 때
 **/

#include "../includes/Post.hpp"

Post::Post() {}

Post::~Post() {}

std::string Post::generateRandomString() {
  static std::string charset =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string result;
  std::srand(std::time(0));

  for (int i = 0; i < 32; ++i)
    result.push_back(charset[std::rand() % charset.size()]);
  return result;
}

void Post::createResource(Response &response, std::string &fileName,
                          std::string &fullUri) {
  DIR *dp = opendir(fullUri.c_str());
  if (!dp) {
    throw ErrorException(400);
    closedir(dp);
  }
  fileName += generateRandomString();
  std::ifstream tempif(fileName);
  while (tempif.is_open() == true) {
    tempif.close();
    fileName = fullUri;
    fileName += generateRandomString();
    tempif = std::ifstream(fileName);
  }
  response.setHeaders("Location", fileName);
  response.setStatusLine(201);
}

void Post::process(Request &request, Response &response) {
  try {
    std::string fullUri = request.getHeaderByKey("RootDir");
    fullUri += request.getHeaderByKey("BasicURI");
    std::string fileName = fullUri;

    if (fullUri.find(".cgi") != std::string::npos) {
      Cgi cgi;
      cgi.reqToEnvp(request.getHeaderMap());
      cgi.excute(request.getBody());
      response.convertCGI(cgi.getRes());
    } else {
      if (fileName[(fileName.size() - 1)] == '/')
        createResource(response, fileName, fullUri);
      else {
        DIR *dp = opendir(fileName.c_str());
        if (dp) {
          closedir(dp);
          throw ErrorException(400);
        }
        std::ifstream tempif(fileName);
        if (tempif.is_open() == false) throw ErrorException(404);
        tempif.close();
        response.setStatusLine(200);
      }
      std::ofstream tempof(fileName, std::ios::app);
      _path = fileName;
      tempof << request.getBody();
      tempof.close();

      // TODO 임시
      response.setBody(
          "임시 response 입니다. 기본 동작 시, body를 생성하지 않습니다.");
      response.setHeaders("Content-Length",
                          ftItos(response.getBody().length()));
      // response.setHeaders("Content-Type", "text/html");
      response.setHeaders("Content-Type", "application/octet-stream");
      response.setResult();
    }
  } catch (ErrorException &e) {
    response.setErrorRes(e.getErrorCode());
  }
}