#include "headers/logtime.hpp"
#include <string>
#include <cstdio>
#include <chrono>

namespace {
  using Clock = std::chrono::steady_clock;
  static Clock::time_point start = Clock::now();
  thread_local char buffer[16];
};
void Time::Init(){
  start = Clock::now();
}
std::string Time::Now(){
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start).count();
  long long m = ms / 60000;
  long long s = (ms / 1000) % 60;
  long long milli = ms % 1000;
  std::snprintf(buffer, sizeof(buffer), "%02lld:%02lld:%03lld", m, s, milli);
  return std::string(buffer);
}
