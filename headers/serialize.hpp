#pragma once
#include <string>
namespace Serialize{
  void LoadEmptyWorld();
  void LoadWorld(std::string path);
  void SaveWorld(std::string path);
};
