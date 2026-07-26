#include "headers/log.hpp"
#include <iostream>
void Log::Success(std::string success){
  std::cout << "[SUCCESS] " << success << "\n";
}
void Log::Warning(std::string warning){
  std::cout << "[WARNING] " << warning << "\n";
}
void Log::Fatal(std::string fatal){
  std::cerr << "[ERROR] " << fatal << "\n";
  std::exit(1);
}
void Log::Info(std::string info){
  std::cout << "[INFO] " << info << "\n";
}
