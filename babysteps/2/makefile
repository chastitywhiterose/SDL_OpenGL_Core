Unix_SDL_OpenGL_GLEW:
	gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lOpenGL -lGLEW -lm && ./main
Win_SDL_OpenGL_GLEW:
	gcc main.c -o main `sdl2-config --cflags --libs` -lOpenGL32 -lGLEW32 -lm && ./main
	
