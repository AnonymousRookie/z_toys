#include "z_net.h"

// 创建套接字并进行绑定监听
int SocketBind(const char* ip, int port)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd) {
        perror("socket error!");
        exit(1);
    }

    int reuse = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (-1 == ret) {
        perror("socket error!");
        exit(1);
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;

    if (NULL == ip) {
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else {
        inet_pton(AF_INET, ip, &servaddr.sin_addr);
    }

    servaddr.sin_port = htons(port);

    ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (-1 == ret) {
        perror("socket error!");
        exit(1);
    }

    ret = listen(listenfd, BACKLOG);
    if (-1 == ret) {
        perror("listen error!");
        exit(1);
    }
    return listenfd;
}

// IO多路复用epoll
void DoEpoll(int listenfd, void (*cb)(int, int, char*))
{
    // 创建一个描述符
    int epollfd = epoll_create(FDSIZE);
    // 添加监听描述符事件
    AddEvent(epollfd, listenfd, EPOLLIN);
    struct epoll_event events[EPOLLEVENTS];
    char buf[MAXSIZE];
    memset(buf, 0, sizeof(buf));
    for (;;) {
        // 获取已经准备好的描述符事件
        int ret = epoll_wait(epollfd, events, EPOLLEVENTS, TIMEOUT);
        if (0 == ret) {
            printf("epoll timeout...\n");
            continue;
        }
        if (ret < 0)
        {
            if (errno == EINTR) {
                continue;
            }
            break;
        }
        HandleEvents(epollfd, events, ret, listenfd, buf, cb);
    }
    close(epollfd);
}

// 事件处理
void HandleEvents(int epollfd, struct epoll_event* events, int num, int listenfd, char* buf, void (*cb)(int, int, char*))
{
    for (int i = 0; i < num; ++i) {
        int fd = events[i].data.fd;
        // 根据描述符的类型和事件类型进行处理
        if ((fd == listenfd) && (events[i].events & EPOLLIN)) {
            HandleAcceptEvent(epollfd, listenfd);
        }
        else if (events[i].events & EPOLLIN) {
            HandleReadEvent(epollfd, fd, buf, cb);
        }
        else if (events[i].events & EPOLLOUT) {
            HandleWriteEvent(epollfd, fd, buf);
        }
    }
}

// 处理连接事件
void HandleAcceptEvent(int epollfd, int listenfd)
{
    int clientfd = 0;
    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen = sizeof(clientaddr);

    do {
        clientfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientaddrlen);
    } while (-1 == clientfd && errno == EINTR);

    if (-1 == clientfd) {
        perror("accept error!");
    }
    else {
        printf("accept a new client: %s:%d\n", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port);
        // 添加一个客户端描述符和事件
        AddEvent(epollfd, clientfd, EPOLLIN);
    }
}

// 处理读事件
void HandleReadEvent(int epollfd, int fd, char* buf, void (*cb)(int, int, char*))
{
    int nread = read(fd, buf, MAXSIZE);
    if (-1 == nread) {
        perror("read error!");
        close(fd);
        DeleteEvent(epollfd, fd, EPOLLIN);
    }
    else if (0 == nread) {
        fprintf(stderr, "client closed!\n");
        close(fd);
        DeleteEvent(epollfd, fd, EPOLLIN);
    }
    else {
        printf("recv: %s\n", buf);
        cb(epollfd, fd, buf);
    }
}

// 处理写事件
void HandleWriteEvent(int epollfd, int fd, char* buf)
{
    int nwrite = write(fd, buf, strlen(buf));
    if (-1 == nwrite) {
        perror("write error!");
        close(fd);
        DeleteEvent(epollfd, fd, EPOLLOUT);
    }
    else {
        printf("send: %s\n", buf);
    }
    memset(buf, 0, MAXSIZE);
}

// 添加事件
void AddEvent(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

// 修改事件
void ModifyEvent(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

// 删除事件
void DeleteEvent(int epollfd, int fd, int state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}