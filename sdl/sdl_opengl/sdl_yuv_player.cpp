//
//  sdl_yuv_player.cpp
//  sdl
//
//  Created by ynhuang on 2021/6/12.
//  Copyright © 2021年 ynhuang. All rights reserved.
//

#include "sdl_yuv_player.h"
#include <SDL.h>
#include <stdlib.h>
#include <iostream>

#define REFRESH_EVENT (SDL_USEREVENT+1)

using namespace std;

static int timeExit;

int refreshTimer(void *data) {
    
    timeExit = 0;
    
    while (!timeExit) {
        SDL_Event event;
        event.type = REFRESH_EVENT;
        SDL_PushEvent(&event);
        SDL_Delay(1000/25);
    }

    timeExit = 0;
    
    return 0;
}

int sdl_yuv_player(char *filePath) {
    
    SDL_Window *window = NULL;
    SDL_Renderer *render = NULL;
    SDL_Texture *texture = NULL;
    
    int quit = 0;
    SDL_Event event;
    
    size_t readLen;
    
    int videoHeight = 480;
    int videoWidth = 640;
    
    // 一帧数据长度 yuv420
    int frameLen = videoWidth * videoHeight * 3 / 2;
    
    // 分配一帧数据长度内存
    unsigned char *frameBuffer = (unsigned char *)malloc(frameLen);
    if (!frameBuffer) {
        cout << "malloc fail" << endl;
        return -1;
    }
    
    // 初始化SDL
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    window = SDL_CreateWindow("yuv player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, videoWidth, videoWidth, SDL_WINDOW_RESIZABLE);
    render = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, videoWidth, videoHeight);
    
    //读取视频文件
    FILE *vFile = fopen(filePath, "r");
    if (!vFile) {
        cout << "file read fail" << endl;
        return -1;
    }
    
    //窗口颜色处理
    SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);
    
    SDL_CreateThread(refreshTimer, "timer", NULL);
    
    while (!quit) {
        SDL_WaitEvent(&event);
        
        switch (event.type) {
            case SDL_QUIT:
                timeExit = 1;
                quit = 1;
                break;
            case REFRESH_EVENT:
                readLen = fread(frameBuffer, 1, frameLen, vFile);
                if (readLen <= 0) {
                    cout << "read fail" << endl;
                    timeExit = 1;
                    quit = 1;
                }
                
                //更新纹理数据
                SDL_UpdateTexture(texture, NULL, frameBuffer, videoWidth);
                SDL_RenderClear(render);
                SDL_RenderCopy(render, texture, NULL, NULL);
                SDL_RenderPresent(render);
                
                break;
                
            default:
                break;
        }
        
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_DestroyTexture(texture);
    
    SDL_Quit();
    
    return 0;
    
}
