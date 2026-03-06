#pragma once
class Character{
  public:
    char id;
    float u0, v0;
    float u1, v1;
    float width;
    float height;
    float xOffset;
    float yOffset;
    float xAdvance;
    Character() = default;
    Character(char _id, int x,int y, int w,int h,float xOff,float yOff, float xAdv)
        : id(_id), u0((float)x), v0((float)y), u1((float)(x+w)), v1((float)(y+h)), width((float)w), height((float)h), xOffset(xOff), yOffset(yOff), xAdvance(xAdv)
    {}
};
