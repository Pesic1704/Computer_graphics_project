//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;;
    TexCoords = aTexCoords;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

//#shader fragment
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 dirLightDirection;
uniform vec3 dirLightColor;
uniform vec3 pointLightPosition;
uniform vec3 pointLightColor;

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 textureColor = texture(texture_diffuse1, TexCoords).rgb;

    vec3 ambient = 0.1 * textureColor;

    vec3 dirLightDir = normalize(-dirLightDirection);
    float dirDiff = max(dot(norm, dirLightDir), 0.0);
    vec3 directional = dirDiff * dirLightColor * textureColor;

    vec3 pointDir = normalize(pointLightPosition - FragPos);
    float pointDiff = max(dot(norm, pointDir), 0.0);
    float distance = length(pointLightPosition - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);
    vec3 point = pointDiff * pointLightColor * attenuation * textureColor;

    FragColor = vec4(ambient + directional + point, 1.0);
}