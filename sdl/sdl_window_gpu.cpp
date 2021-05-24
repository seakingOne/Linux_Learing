#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

int main()
{

	int quit = 1;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;

	// sdl init
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("my window", 200, 400, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Window create fail." << std::endl;
		return -1;
	}

	// 创建渲染器, 后2个参数不关心，默认值
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	//SDL_RenderClear(renderer);
	//SDL_RenderPresent(renderer);

	// 创建渲染器
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 600, 450);

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

		// 画一个小矩形
		SDL_Rect rect;
		rect.w = 30;
		rect.h = 30;
		rect.x = rand() % 600;
		rect.y = rand() % 450;

		// 将纹理设置为当前渲染目标。
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// 在当前渲染目标上绘制一个矩形。
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderFillRect(renderer, &rect);

		// 目标纹理，必须使用SDL_TEXTUREACCESS_TARGET标志创建，或者使用NULL作为默认渲染目标
		SDL_SetRenderTarget(renderer, NULL);
		// 将纹理的一部分复制到当前渲染目标。
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		//通过执行呈现更新屏幕。
		SDL_RenderPresent(renderer);

	} while (quit);

	// 不设置delay时间，窗口就会自动关闭，所有需要事件来处理
	//SDL_Delay(4000);

	//销毁
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);

}