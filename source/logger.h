#ifndef LOGGER_H
#define LOGGER_H

// 轻量日志桩：ezremote 原项目没有文件日志系统，
// vendored 的 httpclient 源码调用 Logger::Logf，这里提供空实现以解耦。
namespace Logger
{
    inline void Init() {}
    inline void Log(const std::string &msg) { (void)msg; }
    template <typename... Args>
    inline void Logf(const char *fmt, ...) { (void)fmt; }
}

#endif
