#include "headers/log.hpp"
#include "headers/logtime.hpp"
#include "headers/serialize.hpp"
#include <iostream>
std::vector<LogEntry> Log::logs;
void Log::Success(const std::string& success){
  std::cout << Time::Now() << "[SUCCESS] " << success;
  Log::logs.push_back(LogEntry{"[SUCCESS] " + success, LogType::SUCCESS, Time::Now()});
}
void Log::Warning(const std::string& warning){
  std::cout << Time::Now() << "[WARNING] " << warning;
  Log::logs.push_back(LogEntry{"[WARNING] " + warning, LogType::WARNING, Time::Now()});
}
void Log::Fatal(const std::string& fatal){
  std::cout << Time::Now() << "[FATAL] " << fatal;
  Log::logs.push_back(LogEntry{"[FATAL]" + fatal, LogType::FATAL, Time::Now()});
  Serialize::ExitEngine(1);
}
void Log::Info(const std::string& info){
  std::cout << Time::Now() << "[INFO] " << info;
  Log::logs.push_back(LogEntry{"[INFO]" + info, LogType::INFO, Time::Now()});
}
// clear the logs vector and free memory by calling shrink_to_fit
void Log::Clear(){
  logs.clear();
  logs.shrink_to_fit();
}
