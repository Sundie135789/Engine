#version 330 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

uniform vec3 lightDirection;
uniform vec3 viewPos;
out vec4 FragColor;

uniform sampler2D albedoTexture;
uniform sampler2D roughnessTexture;
uniform sampler2D metallicTexture;

uniform bool hasAlbedoTex;
uniform bool hasRoughnessTex;
uniform bool hasMetallicTex;

uniform vec3 albedoValue;
uniform float roughnessValue;
uniform float metallicValue;

void main(){
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 objectColor;
    if(hasAlbedoTex)
      objectColor = texture(albedoTexture, UV).rgb;
    else
      objectColor = albedoValue;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightDirection);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 ambient = 0.15 * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = spec * vec3(3.0);

    vec3 finalColor = (ambient + diffuse) * objectColor + specular;
    FragColor = vec4(finalColor, 1.0);
}
