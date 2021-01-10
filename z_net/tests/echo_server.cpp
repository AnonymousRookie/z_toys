#include <string>
#include <signal.h>
#include "../src/tcp_server.h"
#include "../src/event_loop.h"
#include "../src/net_address.h"
#include "../src/buffer.h"
#include "../src/time_stamp.h"
#include "../src/logger.h"

class EchoServer
{
public:
    EchoServer(z_net::EventLoop* loop, const z_net::NetAddress& listenAddr)
        : server_(loop, listenAddr, "EchoServer")
    {
        server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        server_.setThreadNum(2);
    }

    void start()
    {
        server_.start();
    }

private:
    void onConnection(const z_net::TcpConnectionPtr& conn)
    {
        conn->setTcpNoDelay(true);
    }

    void onMessage(const z_net::TcpConnectionPtr& conn, z_net::Buffer* buf, z_net::Timestamp time)
    {
        size_t len = buf->readableBytes();
        conn->send(buf);
    }

private:
    z_net::EventLoop* loop_;
    z_net::TcpServer server_;
};

int main(int argc, char* argv[])
{
    signal(SIGPIPE, SIG_IGN);

    Logger::getInstance().setFileBaseName("echo_server");
    Logger::getInstance().setRollSize(100 * 1024 * 1024);  // 100M
    Logger::getInstance().start();

    z_net::EventLoop loop;
    z_net::NetAddress listenAddr("127.0.0.1", 8001);

    EchoServer server(&loop, listenAddr);
    server.start();
    loop.loop();

    return 0;
}