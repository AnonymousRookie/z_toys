#ifndef Z_NET_H
#define Z_NET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>

#define MAXSIZE 1024
#define FDSIZE 1000
#define EPOLLEVENTS 100
#define TIMEOUT 5000
#define BACKLOG 5


// 创建套接字并进行绑定监听
int SocketBind(const char* ip, int port);

// IO多路复用epoll
void DoEpoll(int listedfd, void (*cb)(int, int, char*));

// 事件处理
void HandleEvents(int epollfd, struct epoll_event* events, int num, int listenfd, char* buf, void (*cb)(int, int, char*));

// 处理连接事件
void HandleAcceptEvent(int epollfd, int listenfd);

// 处理读事件
void HandleReadEvent(int epollfd, int fd, char* buf, void (*cb)(int, int, char*));

// 处理写事件
void HandleWriteEvent(int epollfd, int fd, char* buf);

// 添加事件
void AddEvent(int epollfd, int fd, int state);

// 修改事件
void ModifyEvent(int epollfd, int fd, int state);

// 删除事件
void DeleteEvent(int epollfd, int fd, int state);

#endif  // Z_NET_H