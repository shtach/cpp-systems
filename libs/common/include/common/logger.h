#pragma once

#include <string_view>

namespace common {

    enum class LogLevel {
        DEBUG   = 0,
        INFO    = 1,
        WARNING = 2,
        ERROR   = 3
    };

    // Thread-safety contract:
    // Implementations must be safe for concurrent use:
    // - log() may be called from multiple threads simultaneously.
    // - setLevel() and getLevel() may be called concurrently with log().
    // - Implementations are responsible for internal synchronization.
    class Logger {
        public:
            virtual ~Logger() = default;

            virtual void log(LogLevel level, std::string_view message) = 0;

            virtual void setLevel(LogLevel level) = 0;
            virtual LogLevel getLevel() const = 0;
    };

} // namespace common