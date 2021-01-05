#include <cstdio>
#include <ctime>
#include <cstdarg>
#include <cstring>
#include "z_log.h"

Logger::~Logger()
{
    stop();
}

Logger& Logger::getInstance()
{
    static Logger logger;
    return logger;
}

void Logger::setFileBaseName(const char* fileBaseName)
{
    fileBaseName_ = fileBaseName;
}

void Logger::setRollSize(uint64_t rollSize)
{
    rollSize_ = rollSize;
}

void Logger::start()
{
    Z_CHECK(false == started_);

    time_t now = time(NULL);
    struct tm t;
    localtime_r(&now, &t);

    char name[256] = { 0 };
    sprintf(name, "%s_%04d%02d%02d%02d%02d%02d.log",
        fileBaseName_.c_str(),
        t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
        t.tm_hour, t.tm_min, t.tm_sec);

    fp_ = fopen(name, "wt+");
    Z_CHECK(fp_ != nullptr);

    char startInfo[] = "Logger started!\n";
    fwrite((void*)startInfo, strlen(startInfo), 1, fp_);
    thread_ = std::thread(std::bind(&Logger::ThreadFunc, this));
    started_ = true;
}

void Logger::stop()
{
    exit_ = true;
    cv_.notify_one();
    if (thread_.joinable()) {
        thread_.join();
    }
    if (fp_) {
        while (!queue_.empty()) {
            const std::string& log = queue_.front();
            if (writtenBytes_ > rollSize_) {
                fclose(fp_);
                writtenBytes_ = 0;
                time_t now = time(NULL);
                struct tm t;
                localtime_r(&now, &t);
                char name[256] = { 0 };
                sprintf(name, "%s_%04d%02d%02d%02d%02d%02d.log",
                    fileBaseName_.c_str(),
                    t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
                    t.tm_hour, t.tm_min, t.tm_sec);

                fp_ = fopen(name, "wt+");
            }
            fwrite((void*)log.c_str(), log.length(), 1, fp_);
            fflush(fp_);
            writtenBytes_ += log.size();
            queue_.pop_front();
        }
        fclose(fp_);
        fp_ = nullptr;
    }
}

void Logger::addToQueue(const char* level, const char* file, int line, const char* func, const char* fmt, ...)
{
    char msg[256] = { 0 };

    va_list va;
    va_start(va, fmt);
    vsnprintf(msg, sizeof(msg), fmt, va);
    va_end(va);

    time_t now = time(NULL);
    struct tm t;
    localtime_r(&now, &t);
    char content[512] = { 0 };
    sprintf(content, "[%04d-%02d-%02d %02d:%02d:%02d][%s][0x%04x][%s:%d %s] %s\n",
        t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
        t.tm_hour, t.tm_min, t.tm_sec,
        level,
        std::this_thread::get_id(),
        file, line, func,
        msg);

    printf("%s\n", content);

    std::unique_lock<std::mutex> lock(mutex_);
    queue_.push_back(content);
    cv_.notify_one();
}

void Logger::threadFunc()
{
    Z_CHECK(fp_ != nullptr);

    while (!exit_) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            if (exit_) {
                return;
            }
            cv_.wait(lock);
        }

        const std::string& log = queue_.front();
        if (writtenBytes_ > rollSize_) {
            fclose(fp_);
            writtenBytes_ = 0;

            time_t now = time(NULL);
            struct tm t;
            localtime_r(&now, &t);

            char name[256] = { 0 };

            sprintf(name, "%s_%04d%02d%02d%02d%02d%02d.log",
                fileBaseName_.c_str(),
                t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
                t.tm_hour, t.tm_min, t.tm_sec);

            fp_ = fopen(name, "wt+");
        }
        fwrite((void*)log.c_str(), log.length(), 1, fp_);
        fflush(fp_);
        writtenBytes_ += log.size();
        queue_.pop_front();
    }
}
