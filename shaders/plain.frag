#version 330 core
uniform vec3 uColor;
// https://www.youtube.com/shorts/tPsp4dq6Opg
out vec4 FragColor;
in vec3 Normal;
void main(){
  FragColor = vec4(uColor, 1.0);
}

