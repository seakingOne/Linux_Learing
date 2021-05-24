#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

int main()
{
	
	int quit = 1;
	SDL_Window *window = NULL;
	SDL_Renderer* renderer = NULL;

	// sdl init
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("my window", 200, 400, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Window create fail." << std::endl;
		return -1;
	}

	// 创建渲染器, 后2个参数不关心，默认值
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	do {
		// 事件
		SDL_Event event;
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = 0;
			break;
		default:
			SDL_Log("event.type = %d", event.type);
			break;
		}
	
	} while (quit);

	// 不设置delay时间，窗口就会自动关闭，所有需要事件来处理
	//SDL_Delay(4000);

	//销毁
	SDL_DestroyWindow(window);

}