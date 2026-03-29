#version 330 core
out vec4 FragColor;
in vec2 vUV;
in vec3 Normal;
uniform sampler2D uTexture;

void main(){
  FragColor = texture(uTexture, vUV);
}
