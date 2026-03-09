#include "lang.hpp"
#include <stdint.h>
#include <iostream>


std::vector<std::string> lex_line(std::string buffer){
  std::vector<std::string> tokens;
  uint16_t position = 0;
  std::string token = "";
  while(position < buffer.size()){
    // create_object triangle;
    char c = buffer[position];
    if(std::isalpha(c) || c == '_'){
      while(position < buffer.size() && (std::isalpha(buffer[position]) || buffer[position] == '_')){
        token += buffer[position];
        position++;
      }
      tokens.push_back(token);
      token =  "";
    }else if(c == ' '){
      if(token != "") tokens.push_back(token);
      position++;
    }
    position++;
  }
  std::cout << "TOKENS : start\n";
  for(std::string s : tokens){
    std::cout << s << '\n';
  }
  std::cout << "TOKENS : end\n";
  return tokens;
}
void run_line(std::vector<std::string> tokens){

}
void run_command(std::string command){
  run_line(lex_line(command));
}
