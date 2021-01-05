#include <string>
#include "../src/tcp_client.h"
#include "../src/event_loop.h"
#include "../src/net_address.h"
#include "../src/buffer.h"
#include "../src/time_stamp.h"
#include "../src/logger.h"
 
class EchoClient
{
public:
    EchoClient(z_net::EventLoop* loop, const z_net::NetAddress& listenAddr)
        : client_(loop, listenAddr, "EchoClient")
    {
        client_.setConnectionCallback(std::bind(&EchoClient::onConnection, this, std::placeholders::_1));
        client_.setMessageCallback(std::bind(&EchoClient::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    void connect()
    {
        client_.connect();
    }

private:
    void onConnection(const z_net::TcpConnectionPtr& conn)
    {
        if (conn->connected()) {
            conn->setTcpNoDelay(true);
            conn->send(message_);
        }
        else {
            loop_->quit();
        }
    }

    void onMessage(const z_net::TcpConnectionPtr& conn, z_net::Buffer* buf, z_net::Timestamp time)
    {
        conn->send(buf);
    }

private:
    z_net::EventLoop* loop_;
    z_net::TcpClient client_;
    std::string message_;
};

int main(int argc, char* argv[])
{
    Logger::getInstance().setFileBaseName("echo_client");
    Logger::getInstance().setRollSize(100 * 1024 * 1024);  // 100M
    Logger::getInstance().start();

    z_net::EventLoop loop;
    z_net::NetAddress serverAddr("127.0.0.1", 8002);

    EchoClient client(&loop, serverAddr);
    client.connect();
    loop.loop();

    return 0;
}