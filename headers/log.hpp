#pragma once
#include <string>
class Log{
  public:
    static void Warning(std::string warning);
    static void Fatal(std::string fatal);
    static void Success(std::string success);
};
