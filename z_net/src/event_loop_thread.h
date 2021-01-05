#ifndef Z_NET_SRC_EVENT_LOOP_THREAD_H
#define Z_NET_SRC_EVENT_LOOP_THREAD_H

#include <string>
#include <cstdint>
#include <mutex>
#include <thread>
#include <string>
#include <functional>
#include <condition_variable> 
#include "defines.h"

NAMESPACE_BEGIN(z_net)

class EventLoop;

class EventLoopThread
{
public:
    EventLoopThread(const std::string& name);
    ~EventLoopThread();

    EventLoop* startLoop();

private:
    void threadFunc();

private:
    EventLoop* loop_ = nullptr;
    bool exiting_ = false;
    std::unique_ptr<std::thread> thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

NAMESPACE_END(z_net)

#endif  // Z_NET_SRC_EVENT_LOOP_THREAD_H