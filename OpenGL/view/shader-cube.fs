#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

//由于同一个物体有不同的结构，所有光照都是不同的
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
};

//光源对同一个物体有不同的镜面光度
struct Light {
	//光源位置
    vec3 position;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main()
{

	//环境光照
	vec3 ambient = material.ambient * light.ambient;
	
	//漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;
	
	// 镜面反射
	float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular); 
	
	vec3 result = ambient + diffuse + specular;
	
	FragColor = vec4(result, 1.0);
}