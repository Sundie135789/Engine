#version 330 core
in vec2 TexCoords;
out vec4 FragColor;
uniform bool chromaticAbberation;
uniform float chromaticAbberationStrength;
uniform sampler2D screenTexture;
const float maxAbberation = 0.015;
const float falloff = 2.0;
const float r_displacement =3.0, g_displacement = 0.0, b_displacement = -3.0;
void main(){
  vec3 color = texture(screenTexture, TexCoords).rgb;
  vec2 uv = TexCoords;
  if(chromaticAbberation){
    vec2 screenFactor = (uv - 0.5);
    vec2 CAoffset = vec2(screenFactor.x * chromaticAbberationStrength, 0.0);
    color.r = texture(screenTexture, uv + CAoffset).r;
    color.g = texture(screenTexture, uv ).g;
    color.b = texture(screenTexture, uv - CAoffset).b;
  }

  color = pow(color, vec3(1.0 / 2.2));
  FragColor = vec4(color, 1.0);
}
