#define SDL_MAIN_HANDLED
#pragma warning(disable:4996)
#include <SDL.h>
#include <iostream>
#define REFRESH_EVENT 288
#define QUIT_EVENT 289


int thread_exit = 0;

int refresh_video_timer(void *udata) {
	thread_exit = 0;

	while (!thread_exit) {
		
		SDL_Event event;
		event.type = REFRESH_EVENT;
		SDL_PushEvent(&event);
		SDL_Delay(40);
	}

	thread_exit = 0;
	SDL_Event event;
	event.type = QUIT_EVENT;
	SDL_PushEvent(&event);

	return 0;
}

int main()
{

	FILE* video_fd = NULL;

	SDL_Event event;
	SDL_Rect rect;

	int w_width = 864;
	int w_height = 480;
	const int video_width = 864;
	const int video_height = 480;

	unsigned int remain_len = 0;
	size_t video_buf_len = 0;
	size_t blank_space_len = 0;
	size_t size = 1;
	Uint8 *video_buf = NULL;

	Uint8 *video_pos = NULL;
	Uint8 *video_end = NULL;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *texture = NULL;

	SDL_Thread *timer_thread = NULL;

	const char* path = "D:\\FFmpeg\\ffmpeg-N-101450-gc35e456f54-win64-gpl-shared-vulkan\\bin\\test.yuv";
	const unsigned int yuv_frame_len = video_width * video_height * 3 / 2;
	unsigned int tmp_yuv_frame_len = yuv_frame_len;

	if (yuv_frame_len & 0xF) {
		tmp_yuv_frame_len = (yuv_frame_len & 0xFFF0) + 0x10;
	}
	

	// init
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "init fail" << std::endl;
		return -1;
	}

	window = SDL_CreateWindow("player", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_height, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cout << "window create fail" << std::endl;
		return -1;
	}

	// 创建渲染器
	renderer = SDL_CreateRenderer(window, -1, 0);
	// 创建纹理
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, video_width, video_height);

	// 文件大小分配内存
	video_buf = (Uint8 *)malloc(tmp_yuv_frame_len);

	// 打开视频文件
	video_fd = fopen(path, "rb+");
	printf("size of = %d \n", sizeof(video_fd));
	if (video_fd == NULL) {
		std::cout << "fail open file" << std::endl;
		return -1;
	}

	/*video_buf_len = fread(video_buf, 1, tmp_yuv_frame_len, video_fd);
	printf("video_buf_len  = %d \n", video_buf_len);
	if (video_buf_len <= 0) {
		perror("error read file \n");
		std::cout << "fail read file" << std::endl;
		return -1;
	}*/

	video_pos = video_buf;

	// 线程初始化
	timer_thread = SDL_CreateThread(refresh_video_timer, NULL, NULL);

	do {
	
		SDL_WaitEvent(&event);

		if (event.type == REFRESH_EVENT) {

			printf("tmp_yuv_frame_len  = %d \n", tmp_yuv_frame_len);
			video_buf_len = fread(video_buf, 1, tmp_yuv_frame_len, video_fd);
			//video_buf_len = fread_s(video_buf, sizeof(video_buf), size, yuv_frame_len, video_fd);
			printf("video_buf_len  = %d \n", video_buf_len);
			if (video_buf_len <= 0) {
				thread_exit = 1;
				break;
			}

			SDL_RenderClear(renderer);
			SDL_UpdateTexture(texture, NULL, video_buf, video_width);

			rect.x = 0;
			rect.y = 0;
			rect.w = w_width;
			rect.h = w_height;

			SDL_RenderCopy(renderer, texture, NULL, &rect);
			SDL_RenderPresent(renderer);
			
		}
		else if (event.type == SDL_WINDOWEVENT) {
			SDL_GetWindowSize(window, &w_width, &w_height);
		}
		else if (event.type == SDL_QUIT)
		{
			thread_exit = 1;
		}
		else if (event.type == QUIT_EVENT) {
			break;
		}

	} while (1);

}