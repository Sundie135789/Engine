#version 330 core
in vec2 TexCoords;
out vec4 FragColor;
uniform bool chromaticAbberation;
uniform float chromaticAbberationStrength;
uniform sampler2D screenTexture;
void main(){
  vec3 color = texture(screenTexture, TexCoords).rgb;

  if(chromaticAbberation){
    vec2 offset = chromaticAbberationStrength * (TexCoords-0.5);
    color.r = texture(screenTexture, TexCoords + offset).r;
    color.g = texture(screenTexture, TexCoords).g;
    color.b = texture(screenTexture, TexCoords - offset).b;
  }

  FragColor = vec4(color, 1.0);
}
