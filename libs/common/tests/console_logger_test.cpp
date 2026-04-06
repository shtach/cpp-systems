#include "common/console_logger.h"

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace common;

TEST(ConsoleLogger, LogsCorrectLevel) {
    std::ostringstream oss;
    ConsoleLogger logger(oss);

    logger.setLevel(LogLevel::INFO);
    logger.log(LogLevel::DEBUG, "should not appear");
    logger.log(LogLevel::INFO, "server started");

    std::string output = oss.str();
    EXPECT_EQ(output, "[INFO] server started\n");
}

TEST(ConsoleLogger, LevelFiltering) {
    std::ostringstream oss;
    ConsoleLogger logger(oss);

    logger.log(LogLevel::DEBUG, "debug");
    logger.log(LogLevel::INFO, "info");
    logger.log(LogLevel::WARNING, "warn");
    logger.log(LogLevel::ERROR, "error");

    std::string output = oss.str();

    EXPECT_EQ(output.find("debug"), std::string::npos);

    EXPECT_NE(output.find("info"), std::string::npos);
    EXPECT_NE(output.find("warn"), std::string::npos);
    EXPECT_NE(output.find("error"), std::string::npos);
}

TEST(ConsoleLogger, ThreadSafeLogging) {
    std::ostringstream oss;
    ConsoleLogger logger(oss);
    logger.setLevel(LogLevel::DEBUG);

    auto log_func = [&logger](int id) {
        for (int i = 0; i < 10; ++i)
            logger.log(LogLevel::INFO, "msg" + std::to_string(id) + "_" + std::to_string(i));
    };

    std::vector<std::thread> threads;
    for (int t = 0; t < 5; ++t) 
        threads.emplace_back(log_func, t);

    for (auto &th : threads) th.join();

    std::string output = oss.str();
    
    for (int t = 0; t < 5; ++t) {
        for (int i = 0; i < 10; ++i) {
            std::string msg = "msg" + std::to_string(t) + "_" + std::to_string(i);
            EXPECT_NE(output.find(msg), std::string::npos);
        }
    }
}