#version 330 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

uniform vec3 lightColor;
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

const float PI = 3.14159265;
void main(){
  vec3 albedo = hasAlbedoTex ? texture(albedoTexture, UV).rgb : albedoValue;
  float roughness = hasRoughnessTex ? texture(roughnessTexture, UV).r : roughnessValue;
  float metallic = hasMetallicTex ? texture(metallicTexture, UV).r : metallicValue;

  vec3 N = normalize(Normal); // fragment normal
  vec3 V = normalize(viewPos - FragPos); // view vector
  vec3 L = normalize(lightDirection); // light vector
  vec3 H = normalize(V + L); // halfway

  float NdotL = max(dot(N, L), 0.0); // light angle (0.0 to 1.0)
  float NdotV = max(dot(N, V), 0.0); // view angle (0.0 to 1.0)
  float NdotH = max(dot(N, H), 0.0); // halfway vector's angle (0.0 to 1.0)
  float VdotH = max(dot(V, H), 0.0); // view - halfway angle (0.0 to 1.0)
  /*
     Fresnel Shlick - An object reflects more light when we look at it at a shallow angle.
   */
  vec3 F0 = mix(vec3(0.04), albedo, metallic); // minimum reflectivity of a fragment
  vec3 F = F0 + (1.0 - F0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
  float a = roughness * roughness; // small changes feel too strong without squaring
  float d = (NdotH*NdotH*(a*a-1.0)+1.0); // 
  float D = (a*a) / (PI * d * d);

  float k = (roughness+1.0); 
  k = (k*k)/8.0;
  float numG1 = NdotV / (NdotV * (1.0 - k) + k);
  float numG2 = NdotL / (NdotL * (1.0 - k) + k);
  float G = numG1 * numG2;
  vec3 numerator = D * F * G;
  float denominator = 4.0f * NdotV * NdotL + 0.0001;
  vec3 spec = numerator / denominator;
  vec3 kS = F;
  vec3 kD = vec3(1.0) - kS;
  kD *= 1.0 - metallic;

  vec3 radiance = (lightColor != vec3(0.0)) ? lightColor : vec3(5.0);
  vec3 diff = kD * albedo / PI;
  vec3 col = (diff + spec) * radiance * NdotL;

  col += vec3(0.03) * albedo;
  FragColor.rgb = pow(FragColor.rgb, vec3(1.0 / 2.2));
  FragColor = vec4(col, 1.0);
}
