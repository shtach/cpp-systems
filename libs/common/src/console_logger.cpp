#include "console_logger.h"

#include <format>

namespace common {

    namespace {
        const char* toString(LogLevel level) {
            switch (level) {
                case LogLevel::DEBUG:   return "DEBUG";
                case LogLevel::INFO:    return "INFO";
                case LogLevel::WARNING: return "WARNING";
                case LogLevel::ERROR:   return "ERROR";
                default:                return "UNKNOWN";
            }
        }
    }

    ConsoleLogger::ConsoleLogger(std::ostream& output) : output_(output) {}

    void ConsoleLogger::log(LogLevel level, std::string_view message) {
        LogLevel currentLevel;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            currentLevel = level_;
        }

        if (level < currentLevel) return;

        std::string formatted = std::format("[{}] {}", toString(level), message);

        {
            std::lock_guard<std::mutex> lock(mutex_);
            output_ << formatted << '\n';
        }
    }

    void ConsoleLogger::setLevel(LogLevel level) {
        std::lock_guard<std::mutex> lock(mutex_);
        level_ = level;
    }

    LogLevel ConsoleLogger::getLevel() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return level_;
    }

} // namespace common