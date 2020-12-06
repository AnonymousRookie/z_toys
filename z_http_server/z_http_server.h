#ifndef Z_HTTP_SERVER_H
#define Z_HTTP_SERVER_H

#include <stdio.h>

class ZHttpServer
{
public:
    ZHttpServer();
    ~ZHttpServer();

    void Start(int port);

private:
    static void ReadCallBack(int epollfd, int clientfd, char* buf);
    static int SendHttpHeader(int clientfd, char* code, char* msg, char* fileType, int len);
    static int SendFile(int epollfd, int clientfd, char* filename);
};


#endif  // Z_HTTP_SERVER_H