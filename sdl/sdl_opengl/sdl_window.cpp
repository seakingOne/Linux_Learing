//
//  sdl_window.cpp
//  sdl
//
//  Created by ynhuang on 2021/6/12.
//  Copyright © 2021年 ynhuang. All rights reserved.
//

#include "sdl_window.h"
#include <SDL.h>
#include <iostream>
#include <glad/glad.h>

using namespace std;

int create_sdl_window_demo() {
    
    const char *title = "sdl demo";
    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    // 纹理
    SDL_Texture *texture = NULL;
    //一个矩形
    SDL_Rect rect;
    
    rect.w = 100;
    rect.h = 50;
    
    //sdl init
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
    
    if (!window) {
        cout << "create windows fail" << endl;
        return -1;
    }
    
    // create renderer
    render = SDL_CreateRenderer(window, -1, 0);
    
    // create texture
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
    
    // 窗口不会关闭，除非我们点击关闭按钮
    int quit = 1;
    do {
        
        //事件
        SDL_Event event;
        SDL_WaitEvent(&event);
        
        switch (event.type) {
            case SDL_QUIT:
                quit = 0;
                break;
                
            default:
                SDL_Log("event.type = %d", event.type);
                break;
        }
        
        rect.x = rand() % 500;
        rect.y = rand() % 500;
        
        //设置纹理是当前渲染器的目标
        SDL_SetRenderTarget(render, texture);
        SDL_SetRenderDrawColor(render, 0, 245, 255, 255);
        SDL_RenderClear(render);
        
        // 画一个矩形
        SDL_RenderDrawRect(render, &rect);
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderFillRect(render, &rect);
        SDL_SetRenderTarget(render, NULL);
        
        //copy数据
        SDL_RenderCopy(render, texture, NULL, NULL);
        
        //数据开始渲染
        SDL_RenderPresent(render);
        
    } while (quit);
    
    
    //销毁
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    
    return 0;
}
