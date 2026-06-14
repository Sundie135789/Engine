#version 330 core
in vec3 Normal;
in vec3 Color;
in vec2 UV;
uniform sampler2D u_Texture;

uniform vec3 lightDirection;
uniform vec3 viewPos;
uniform float shininess;

out vec4 FragColor;
in vec3 FragPos;
void main(){
  vec3 lightColor = vec3(1.0, 1.0, 1.0); // Light Color
  vec4 texColor = texture(u_Texture, UV); // Color from texture sample
  vec3 objectColor = mix(Color, texColor.rgb, 0.5); // Mixing object color, and texture color
  // Ambient lighting
  float ambientStrength = 0.2; 
  vec3 ambient = ambientStrength * lightColor;  
  // Diffuse lighting
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightDirection); 
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  //Specular lighting
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  vec3 specular = spec * lightColor;
  vec3 finalColor = (ambient + diffuse) * objectColor + specular;
  FragColor = vec4(finalColor, texColor.a);
}
