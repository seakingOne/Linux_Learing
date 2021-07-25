//
//  illumination.cpp
//  sdl
//
//  Created by ynhuang on 2021/6/25.
//  Copyright © 2021年 ynhuang. All rights reserved.
//

#include "illumination.h"
#include "opengl.h"
#include <glad/glad.h>
#include <SDL.h>
#include "shader.h"
#include "camera.h"

//计算库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iomanip>
#include <iostream>

using namespace std;

void printMat4(const glm::mat4& srcMat4)
{
    std::cout << std::fixed;
    const float *pSource = (const float*)glm::value_ptr(srcMat4);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            float number = pSource[4 * j + i];
            std::cout.width(5);
            if (abs(number) < 0.0001f)
                std::cout << 0 << "\t";
            else
                std::cout << std::setprecision(2) << number << "\t";
        }
        std::cout << std::endl;
    }
}

SDL_Window *create_window() {
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_Window *window = SDL_CreateWindow("光照模块测试", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        return nullptr;
    }
    
    return window;
    
}

void test() {
    if(1 == 1) {
        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans;
        printMat4(trans);
        cout << "----one---" << endl;
        trans = glm::translate(trans, glm::vec3(1.2f, 1.0f, 2.0f));
        //std::cout << glm::(trans).c_str() << std::endl;
        printMat4(trans);
        
        trans = glm::scale(trans, glm::vec3(0.2f));
        cout << "----two---" << endl;
        printMat4(trans);
        
        return;
    }
}

int create_illumination_demo() {
    
    int quit = 1;
    
    SDL_Window *window = create_window();
    if (!window) {
        return -1;
    }
    
    SDL_GL_CreateContext(window);
    
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    
    //创建着色器
    myShader cube_shader("/Users/mac/Desktop/c_and_c++/sdl_test/sdl/sdl/cube.vs","/Users/mac/Desktop/c_and_c++/sdl_test/sdl/sdl/cube.fs");
    myShader light_cube_shader("/Users/mac/Desktop/c_and_c++/sdl_test/sdl/sdl/light_cube.vs", "/Users/mac/Desktop/c_and_c++/sdl_test/sdl/sdl/light_cube.fs");
    
    //启动深度测试
    glEnable(GL_DEPTH_TEST);
    
    //顶点坐标：物体坐标，光源坐标(没有设置纹理)
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    
    //首先，配置物体的VAO,VBO
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //设置法向量
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //创建光源的VAO,VBO可以直接复用
    unsigned int lightVBO, lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightVBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(lightCubeVAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Camera camera(
                  glm::vec3(3.7342, 2.0652f, -1.6181f),
                  glm::vec3(0.0f, 1.0f, 0.0f),
                  144.3973f,
                  -26.8f
                  );
    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    
    do {
        
        SDL_Event event;
        SDL_PollEvent(&event);
        
        switch (event.type) {
            case SDL_QUIT:
                quit = 0;
                break;
                
            case SDL_WINDOWEVENT:
                //窗口大小发生变化，需要重新渲染
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    glViewport(0, 0, w, h);
                }
                
                break;
                
            default:
                break;
        }
        
        //设置窗口颜色
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //设置物体着色器中的参数
        cube_shader.use();
        glUniform3f(glGetUniformLocation(cube_shader.id, "objectColor"), 1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(cube_shader.id, "lightColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(cube_shader.id, "lightPos"), 1.2f, 1.0f, 2.0f);
        glUniform3f(glGetUniformLocation(cube_shader.id, "viewPos"), 1.2f, 1.0f, 2.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glUniformMatrix4fv(glGetUniformLocation(cube_shader.id, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(cube_shader.id, "view"), 1, GL_FALSE, &view[0][0]);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(cube_shader.id, "model"), 1, GL_FALSE, &model[0][0]);

        // render the cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // also draw the lamp object
        light_cube_shader.use();
        glUniformMatrix4fv(glGetUniformLocation(light_cube_shader.id, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(light_cube_shader.id, "view"), 1, GL_FALSE, &view[0][0]);
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        
        glUniformMatrix4fv(glGetUniformLocation(light_cube_shader.id, "model"), 1, GL_FALSE, &model[0][0]);
        
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        SDL_GL_SwapWindow(window);
        
    } while(quit);
    
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
