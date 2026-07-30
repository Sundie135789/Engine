#include "headers/log.hpp"
#include <cstdlib>
#include <iostream>
std::vector<LogEntry> Log::logs;
void Log::Success(const std::string& success){
  std::cout << "[SUCCESS] " << success;
  Log::logs.push_back(LogEntry{success, LogType::SUCCESS});
}
void Log::Warning(const std::string& warning){
  std::cout << "[WARNING] " << warning;
  Log::logs.push_back(LogEntry{warning, LogType::WARNING});
}
void Log::Fatal(const std::string& fatal){
  std::cout << "[FATAL] " << fatal;
  Log::logs.push_back(LogEntry{fatal, LogType::FATAL});
  std::exit(1);
}
void Log::Info(const std::string& info){
  std::cout << "[INFO] " << info;
  Log::logs.push_back(LogEntry{info, LogType::INFO});
}
