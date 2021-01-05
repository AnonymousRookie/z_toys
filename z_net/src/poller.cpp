#include "poller.h"
#include "channel.h"
#include "event_loop.h"

NAMESPACE_BEGIN(z_net)

Poller::Poller(EventLoop* loop)
    : ownerLoop_(loop)
{

}

bool Poller::hasChannel(Channel* channel)
{
    assertInLoopThread();
    auto it = channels_.find(channel->fd());
    return (it != channels_.end() && it->second == channel);
}

void Poller::assertInLoopThread()
{
    ownerLoop_->assertInLoopThread();
}

NAMESPACE_END(z_net)