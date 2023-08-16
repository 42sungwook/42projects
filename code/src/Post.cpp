/**
 * 1. POST 기본 동작
 *   - 없는 파일: 에러 404(임시)
 *   - 폴더 경로: 랜덤한 이름으로 생성 후, 응답에 생성 파일 이름 헤더로 전송 201
 *   - 없는 폴더: (없는 경로로 요청이 들어옴) 400
 *   - 있는 파일: append 200
 * 2. cgi cgi path 내용이 들어올 때 분기 처리 그외 에러처리
 * 3. chuncked 인코딩으로 들어왔을 때
 * 4. '/' 끝에 없고 폴더일 경우 301
 **/

#include "../includes/Post.hpp"

Post::Post() {}

Post::~Post() {}

bool Post::isCgi(const std::string &fullUri, Request &request) {
  (void)fullUri;
  (void)request;
  return false;
  // findCgi function fullUri.find(".cgi") != std::string::npos
}

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
  fileName += generateRandomString();
  std::ifstream tempif(fileName);
  while (tempif.is_open() == true) {
    tempif.close();
    fileName = fullUri;
    fileName += generateRandomString();
	  std::ifstream temif(fileName);
//    tempif = std::ifstream(fileName); // TODO 클러스터 맥에서 대입연산자 에러
  }
  response.setHeaders("Location", fileName);
  response.setStatusLine(201);
}

void Post::appendResource(const std::string &fileName, const Request &request) {
  std::ofstream tempof(fileName, std::ios::app);
  _path = fileName;
  tempof << request.getBody();
  tempof.close();
}

void Post::process(Request &request, Response &response) {
  try {
    std::string fullUri = request.getHeaderByKey("RootDir");
    fullUri += request.getHeaderByKey("BasicURI");
    std::string fileName = fullUri;

    if (isCgi(fullUri, request) == true) {
      Cgi cgi;
      cgi.reqToEnvp(request.getHeaderMap());
      cgi.excute(request.getBody());
      response.convertCGI(cgi.getRes());
    } else {
      if (fileName.back() == '/') {
        std::cout << "/ mime: " << request.getMime() << std::endl;
        if (request.getMime() != "directory") {
          throw ErrorException(400);
        }
        createResource(response, fileName, fullUri);
      } else {
        std::cout << "none / mime: " << request.getMime() << std::endl;
        if (request.getMime() == "directory") {
          fileName += '/';
          response.setHeaders("Location", fileName);
          throw ErrorException(301);
        }
        std::ifstream tempif(fileName);
        if (tempif.is_open() == false) throw ErrorException(404);
        tempif.close();
        response.setStatusLine(200);
      }
      appendResource(fileName, request);

      // TODO 임시
      response.setBody(
          "POST 동작의 임시 response 입니다.\n기본 동작 시, body를 생성하지 않는다고 합니다.\n만약 생성한다면 알려주세요.");
      response.setHeaders("Content-Length",
                          ftItos(response.getBody().length()));
      // response.setHeaders("Content-Type", "text/html");
      response.setHeaders("Content-Type", "application/octet-stream");
      response.setResult();
    }
  } catch (ErrorException &e) {
    if (e.getErrorCode() >= 400) {
	    response.setErrorRes(e.getErrorCode());
    }
	  else { // TODO 300번대 에러에 대해서 더 알아보기
	    response.setRedirectRes(e.getErrorCode());
    }
  }
}