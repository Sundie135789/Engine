#pragma once
#include <glm/glm.hpp>
#include "../vendor/json/json.hpp"

using json = nlohmann::json;
namespace glm{
  inline void from_json(const json& j, vec3& v){
    v = vec3(j.at(0).get<float>(),
             j.at(1).get<float>(),
             j.at(2).get<float>());
  }
  inline void from_json(const json& j, vec2& v){
    v = vec2(j.at(0).get<float>(),
             j.at(1).get<float>());
  }
};
