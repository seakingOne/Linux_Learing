#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //设置的世界坐标系中的立方体片段
    FragPos = vec3(model * vec4(aPos, 1.0));
    //设置法向量
    Normal = aNormal;
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
