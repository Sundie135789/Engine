
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
    Character(char _id, int x,int y, int w,int ,h,int xOff,int yOff, int xAdv)
      : id(_id), width((float) w), height((float)h), xOffset((float)xOff), yOffset((float)yOff), xAdvance((float)xAdv)
    {
      u0 = x/ 256.0f;
      v0 = y / 512.0f;
      u1 = (x + w) / 256.0f;
      v1 = (y + h) / 512.0f;

      float tmpV0 = 1.0f - v0;
      float tmpV1 = 1.0f - v1;
      v0 = tmpV1;
      v1 = tmpV0;
    }
}
