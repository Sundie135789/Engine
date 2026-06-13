#version 330 core
in vec3 Normal;
in vec3 Color;
in vec2 UV;
uniform sampler2D u_Texture;

out vec4 FragColor;
void main(){
  vec3 lightColor = vec3(1.0, 1.0, 1.0);
  vec4 texColor = texture(u_Texture, UV);
  vec3 objectColor = mix(Color, texColor.rgb, 0.5);
  float ambientStrength = 0.2;
  vec3 ambient = ambientStrength * lightColor;
  vec3 finalColor = (ambient) * objectColor;
  
  FragColor = vec4(finalColor, texColor.a);
}
