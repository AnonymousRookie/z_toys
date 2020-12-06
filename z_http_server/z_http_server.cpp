#include <sys/stat.h>
#include "z_http_server.h"
#include "z_net.h"

ZHttpServer::ZHttpServer()
{

}

ZHttpServer::~ZHttpServer()
{

}

void ZHttpServer::Start(int port)
{
    int listenfd = SocketBind(NULL, port);
    DoEpoll(listenfd, &ReadCallBack);
}

void ZHttpServer::ReadCallBack(int epollfd, int clientfd, char* buf)
{
    // 处理http请求行数据, 分析出要请求的资源文件名
    char requestType[16] = {0};
    char path[255] = {0};
    char filename[255] = {0};
    char protocol[16] = {0};

    // GET /index.html HTTP/1.1
    sscanf(buf, "%[^ ] %[^ ] %[^\r\n]", requestType, filename, protocol);
    printf("requestType = %s, filename = %s, protocol = %s\n", requestType, filename, protocol);

    if (0 == strcasecmp(requestType, "GET"))
    {
        sprintf(path, "htdocs%s", filename);

        printf("path = %s\n", path);

        if (path[strlen(path) - 1] == '/') {
            strcat(path, "index.html");
        }

        // 判断文件是否存在
        struct stat st;
        if (-1 == stat(path, &st)) {
            printf("file:%s not exist!\n", path);
            SendHttpHeader(clientfd, "404", "NOT FOUND", "text/html", 0);
            SendFile(epollfd, clientfd, "htdocs/404.html");
        }
        else {
            printf("file:%s ok!\n", path);
            SendHttpHeader(clientfd, "200", "OK", "text/html", 0);
            SendFile(epollfd, clientfd, path);
        }
    }
    else
    {
        // 未实现的请求
        printf("unimplemented!!!\n");
    }
}

int ZHttpServer::SendHttpHeader(int clientfd, char* code, char* msg, char* fileType, int len)
{
    char buf[1024] = {0};
    sprintf(buf, "HTTP/1.1 %s %s\r\n", code, msg);
    sprintf(buf + strlen(buf), "Content-Type:%s\r\n", fileType);

    if (len > 0) {
        sprintf(buf + strlen(buf), "Content-Length:%d\r\n", len);
    }
    strcat(buf, "\r\n");
    write(clientfd, buf, strlen(buf));

    return 0;
}

int ZHttpServer::SendFile(int epollfd, int clientfd, char* filename)
{
    FILE* fp = fopen(filename, "r");
    if(!fp) {
        perror("open error!");
        return -1;
    }

    // 循环读文件并发送
    char buf[1024] = {0};
    while(!feof(fp)) {
        fgets(buf, sizeof(buf), fp);
        write(clientfd, buf, strlen(buf));
    }
    fclose(fp);

    DeleteEvent(epollfd, clientfd, EPOLLIN | EPOLLOUT);
    close(clientfd);

    return 0;
}

