#include "headers/log.hpp"
#include "headers/logtime.hpp"
#include <cstdlib>
#include <iostream>
std::vector<LogEntry> Log::logs;
void Log::Success(const std::string& success){
  std::cout << Time::Now() << "[SUCCESS] " << success;
  Log::logs.push_back(LogEntry{success, LogType::SUCCESS, Time::Now()});
}
void Log::Warning(const std::string& warning){
  std::cout << Time::Now() << "[WARNING] " << warning;
  Log::logs.push_back(LogEntry{warning, LogType::WARNING, Time::Now()});
}
void Log::Fatal(const std::string& fatal){
  std::cout << Time::Now() << "[FATAL] " << fatal;
  Log::logs.push_back(LogEntry{fatal, LogType::FATAL, Time::Now()});
  std::exit(1);
}
void Log::Info(const std::string& info){
  std::cout << Time::Now() << "[INFO] " << info;
  Log::logs.push_back(LogEntry{info, LogType::INFO, Time::Now()});
}
