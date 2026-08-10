#pragma once
struct GraphicsSettings{
  bool chromaticAbberation = false;
  float chromaticAbberationStrength = 0.05f;
  bool vsync = false;
};
struct ControlSettings{
  float camera_speed = 5.0f;
  float sensitivity = 0.1f;
};
struct WorldSettings{
  float gravity = 20.0f;
};
struct Settings{
  GraphicsSettings graphics;
  ControlSettings controls;
  WorldSettings world;
};

