Unix_SDL_OpenGL:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lOpenGL -lm && ./main
Win_SDL_OpenGL:
	gcc main.c -o main `sdl2-config --cflags --libs` -lOpenGL32 -lm && ./main
