#ifndef Z_NET_SRC_LOG_H
#define Z_NET_SRC_LOG_H

#include <functional>
#include <cstdint>
#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef _WIN32
# define localtime_r(a, b) localtime_s(b, a)
#endif  // _WIN32

#define Z_CHECK(p) if (!(p)) return;

class Logger
{
public:
    ~Logger();
    static Logger& getInstance();
    void setFileBaseName(const char* fileBaseName);
    void setRollSize(uint64_t rollSize);
    void addToQueue(const char* level, const char* file, int line, const char* func, const char* fmt, ...);
    void start();

private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void stop();
    void threadFunc();

private:
    std::string fileBaseName_;
    uint64_t rollSize_{ 1024 * 1024 };  // 1M
    FILE* fp_{};
    std::thread thread_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::deque<std::string> queue_;
    bool started_{ false };
    bool exit_{ false };
    uint64_t writtenBytes_{ 0 };
};


#ifndef _WIN32
# define LOG_INFO(args...) Logger::getInstance().addToQueue("INFO", __FILE__, __LINE__, __func__, ##args)
# define LOG_WARN(args...) Logger::getInstance().addToQueue("WARN", __FILE__, __LINE__, __func__, ##args)
# define LOG_ERROR(args...) Logger::getInstance().addToQueue("ERROR", __FILE__, __LINE__, __func__, ##args)
#else
# define LOG_INFO(...) Logger::getInstance().addToQueue("INFO", __FILE__, __LINE__, __func__, __VA_ARGS__)
# define LOG_WARN(...) Logger::getInstance().addToQueue("WARN", __FILE__, __LINE__, __func__, __VA_ARGS__)
# define LOG_ERROR(...) Logger::getInstance().addToQueue("ERROR", __FILE__, __LINE__, __func__, __VA_ARGS__)
#endif


#endif  // Z_NET_SRC_LOG_H