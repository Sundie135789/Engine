#pragma once
#include <string>
#include <vector>
enum class LogType{
  INFO = 0,
  SUCCESS = 1,
  WARNING = 2,
  FATAL = 3
};
struct LogEntry {
  std::string message;
  LogType type;
};
class Log{
  public:
    static void Info(const std::string& msg);
    static void Fatal(const std::string& msg);
    static void Warning(const std::string& msg);
    static void Success(const std::string& msg);
    static std::vector<LogEntry> logs;
};

