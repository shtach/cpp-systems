#pragma once

#include <ostream>
#include <mutex>

#include "common/logger.h"

namespace common {

    class ConsoleLogger : public Logger {
        public:
            explicit ConsoleLogger(std::ostream& output);

            void log(LogLevel level, std::string_view message) override;

            void setLevel(LogLevel level) override;
            LogLevel getLevel() const override;

        private:
            std::ostream& output_;
            LogLevel level_ { LogLevel::INFO };

            mutable std::mutex mutex_; // needed for const getLevel()
    };

} // namespace common