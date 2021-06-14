//
//  shader.hpp
//  sdl
//
//  Created by ynhuang on 2021/6/13.
//  Copyright © 2021年 ynhuang. All rights reserved.
//

#ifndef shader_h
#define shader_h

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class myShader {
    
public:
    //程序id
    int id;
    
    //构建着色器
    myShader(const GLchar *vertexPath, const GLchar *fragmentPath);
    
    //激活程序
    void use();
    
    // uniform工具函数
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
};

#endif /* shader_h */
