#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    
    //环境光照对物体颜色的影响
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    //漫反射光照
    vec3 norm = normalize(Normal);
    //计算光源与物体片段中的距离
    vec3 lightDir = normalize(lightPos - FragPos);
    //计算法向量与距离之间的点乘
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    //镜面反射高光
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    
    FragColor = vec4(result, 1.0);
}
