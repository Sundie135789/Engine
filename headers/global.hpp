#pragma once
#include <vector>
#include "gameobject.hpp"
#include "Character.hpp"

extern std::vector<GameObject*> gameobjects;
extern std::unordered_map<char, Character> fontCharacters;
extern unsigned int fontTextureID;
extern int fontLineHeight;
void goTerminate();
