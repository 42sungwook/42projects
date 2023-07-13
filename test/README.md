# 테스트 방법

## server-client

```shell
# 사용법
> cd server-test
> make
> ./server port number (ex 1234)
> ./client 127.0.0.1 1234 (server의 포트번호)
```

## kqueue

```shell
> cd kqueue
> make
> ./test
```

```shell
> nc 127.0.0.1 8080
```