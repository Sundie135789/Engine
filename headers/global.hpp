#pragma once
#include <vector>
#include <unordered_map>
#include <stdbool.h>
class GameObject;
class Character;
extern std::vector<GameObject*> gameobjects;
extern std::unordered_map<char, Character> fontCharacters;
extern unsigned int fontTextureID;
extern float fontLineHeight;
void goTerminate();
extern int fontAtlasWidth;
extern int fontAtlasHeight;
extern bool commandEnabled;
//extern float command_color[] = {0.303f,0.303f,0.303f};
//extern float command_default_color[] = {0.403f, 0.403f, 0.403f};
