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

	// ������Ⱦ��, ��2�����������ģ�Ĭ��ֵ
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	//SDL_RenderClear(renderer);
	//SDL_RenderPresent(renderer);

	// ������Ⱦ��
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 600, 450);

	do {
		// �¼�
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

		// ��һ��С����
		SDL_Rect rect;
		rect.w = 30;
		rect.h = 30;
		rect.x = rand() % 600;
		rect.y = rand() % 450;

		// ����������Ϊ��ǰ��ȾĿ�ꡣ
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// �ڵ�ǰ��ȾĿ���ϻ���һ�����Ρ�
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderFillRect(renderer, &rect);

		// Ŀ����������ʹ��SDL_TEXTUREACCESS_TARGET��־����������ʹ��NULL��ΪĬ����ȾĿ��
		SDL_SetRenderTarget(renderer, NULL);
		// �������һ���ָ��Ƶ���ǰ��ȾĿ�ꡣ
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		//ͨ��ִ�г��ָ�����Ļ��
		SDL_RenderPresent(renderer);

	} while (quit);

	// ������delayʱ�䣬���ھͻ��Զ��رգ�������Ҫ�¼�������
	//SDL_Delay(4000);

	//����
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(texture);

}