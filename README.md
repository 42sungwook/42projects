# webserv

## 개요
멤버 : jaekkang danpark juyojeon yejinam sungwook myko
시작일 : 07.03

## 테스트 실행법
- TCP / IP 소켓 프로그래밍 책 상의 예제 1번 코드 올렸습니다.  
```shell
# 사용법
> cd test
> make
> ./server port number (ex 1234)
> ./client 127.0.0.1 1234 (server의 포트번호)
```

## 참고 이미지

jaekkang님의 요청으로 추가

### HTTP 멱동성
![http_idempotent](/images/http_idempotent.png)

---

### Method 구조
![method_structure](/images/method_structure.png)

---

### Request 형식
![request_format](/images/request_format.png)

---

### Request 상태 의미
![request_status](/images/request_status.png)


## 참고 문헌

- [42seoul, webserv](reference/webserv.pdf)
- [42seoul, webserv_ko](reference/webserv_ko.md)
- [Webserv tutorials](https://42seoul.gitbook.io/webserv/)

서브젝트에서 RFC를 읽으라고는 되어 있지만 이전처럼 7230 ~ 7235를 읽으라는 문구는 없는 것 같습니다. (확인하시면 수정좀) 그래도 일단 올려놓습니다.

- [RFC 7230](https://www.ietf.org/rfc/rfc7230.txt)
- [RFC 7231](https://www.ietf.org/rfc/rfc7231.txt)
- [RFC 7232](https://www.ietf.org/rfc/rfc7232.txt)
- [RFC 7233](https://www.ietf.org/rfc/rfc7233.txt)
- [RFC 7234](https://www.ietf.org/rfc/rfc7234.txt)
- [RFC 7235](https://www.ietf.org/rfc/rfc7235.txt)
