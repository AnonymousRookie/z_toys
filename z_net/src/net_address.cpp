#include <string.h>
#include "net_address.h"
#include "sockets_ops.h"

NAMESPACE_BEGIN(z_net)

NetAddress::NetAddress()
{
    
}

NetAddress::NetAddress(const std::string& ip, uint16_t port)
{
    memset(&addr_, 0, sizeof(addr_));
	sockets::fromIpPort(ip.c_str(), port, &addr_);
}

const struct sockaddr_in& NetAddress::getSockAddr() const
{
    return addr_;
}

void NetAddress::setSockAddr(const struct sockaddr_in& addr)
{
    addr_ = addr;
}

std::string NetAddress::toIpPort() const
{
	char buf[32];
	sockets::toIpPort(buf, sizeof(buf), addr_);
	return buf;
}

std::string NetAddress::toIp() const
{
	char buf[32];
	sockets::toIp(buf, sizeof(buf), addr_);
	return buf;
}

NAMESPACE_END(z_net)