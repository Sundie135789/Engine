#pragma once
#include <vector>
#include <unordered_map>
#include "character.hpp"
class GameObject;

extern std::vector<GameObject*> gameobjects;
extern std::unordered_map<char, Character> fontCharacters;
extern unsigned int fontTextureID;
extern int fontLineHeight;
void goTerminate();
