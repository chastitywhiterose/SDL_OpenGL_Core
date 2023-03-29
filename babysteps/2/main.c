#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>

SDL_Window* window;
SDL_GLContext context;
SDL_Event event;
GLuint vbo;
int loop=1;

float vertices[]=
{
 0.0f,  0.5f, /* Vertex 1 (X, Y) */
 0.5f, -0.5f, /* Vertex 2 (X, Y) */
 -0.5f, -0.5f  /* Vertex 3 (X, Y) */
};

char vertexSource[]=
"#version 150 core\n"
"in vec2 position;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(position, 0.0, 1.0);\n"
"}\n";

char fragmentSource[]=
"#version 150 core\n"
"out vec4 outColor;\n"
"void main()\n"
"{\n"
" outColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n";

int main(int argc, char *argv[])
{
 SDL_Init(SDL_INIT_VIDEO);
 
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
 SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
 
 window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
 
 context = SDL_GL_CreateContext(window);

 /*use modern functions*/ 
 glewExperimental = GL_TRUE;
 glewInit();
 
 /*set up the vertex buffer object*/
 glGenBuffers(1, &vbo);
 glBindBuffer(GL_ARRAY_BUFFER, vbo);
 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

 /*optionally, display the shader source to test if it is correct*/
/*
 printf("Vertex Shader Source:\n\n%s\n",vertexSource);
 printf("Fragment Shader Source:\n\n%s\n",fragmentSource);
*/




 loop=1;
 while(loop)
 {

  /*stuff will go here in next step*/

  SDL_PollEvent( &event );
  if( event.type == SDL_QUIT ){loop=0;}
  if(event.type == SDL_KEYDOWN)
  {
   if(event.key.keysym.sym==SDLK_ESCAPE){loop=0;}
  }
  
  SDL_GL_SwapWindow( window );
  
 }

 SDL_GL_DeleteContext(context);
 SDL_Quit();

 return 0;
}

/*
this source was made by following the SDL section of this page:
https://open.gl/context

The entire thing can be compiled and run on Linux with:
gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` -lOpenGL -lGLEW -lm && ./main

It only makes a window and OpenGL context. Nothing else. It is merely the start of things.
*/

