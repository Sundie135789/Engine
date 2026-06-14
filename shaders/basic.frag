#version 330 core
in vec3 Normal;
in vec3 Color;
in vec2 UV;
in vec3 FragPos;

uniform sampler2D u_Texture;
uniform vec3 lightDirection;
uniform vec3 viewPos;
uniform float shininess;

out vec4 FragColor;

void main(){
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec4 texColor = texture(u_Texture, UV);
    vec3 objectColor = mix(Color, texColor.rgb, 0.5);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightDirection);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Ambient
    vec3 ambient = 0.15 * lightColor;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular (Phong) - BOOSTED
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * lightColor * 2.0;     

    vec3 finalColor = (ambient + diffuse) * objectColor + specular;

    FragColor = vec4(finalColor, texColor.a);
}
