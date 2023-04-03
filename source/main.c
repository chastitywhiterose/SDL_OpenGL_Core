#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <math.h>

int width=1280,height=720;



SDL_Window* window;
SDL_GLContext context;
SDL_Event event;
int loop=1;

float vertices[0x1000000]=
{
 0.0f,  0.5f, /* Vertex 1 (X, Y) */
 0.5f, -0.5f, /* Vertex 2 (X, Y) */
 -0.5f, -0.5f  /* Vertex 3 (X, Y) */
};

GLint uniColor;

#include "chaste_opengl_core.h"
#include "sdl_chaste_opengl_core_polygon.h"
#include "sdl_chaste_opengl_core_checkerboard.h"
#include "sdl_chaste_opengl_core_font.h"

GLuint vao;
GLuint vbo;

GLuint vertexShader;
const char *vertexSource=
"#version 150 core\n"
"in vec2 position;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(position, 0.0, 1.0);\n"
"}\n";

GLuint fragmentShader;
const char *fragmentSource=
"#version 150 core\n"
"uniform vec3 triangleColor;\n"
"out vec4 outColor;\n"
"void main()\n"
"{\n"
" outColor = vec4(triangleColor, 1.0);\n"
"}\n";



/*for checking if shaders are ok*/
GLint status;
char buffer[512];
GLuint shaderProgram;

GLint posAttrib;

int main(int argc, char *argv[])
{
 SDL_Init(SDL_INIT_VIDEO);
 
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
 SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
 
 window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
 
 context = SDL_GL_CreateContext(window);

 /*use modern functions*/ 
 glewExperimental = GL_TRUE;
 glewInit();
 
 /*vertex array object*/
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);
 
 /*set up the vertex array buffer object*/
 glGenBuffers(1, &vbo);
 glBindBuffer(GL_ARRAY_BUFFER, vbo);
 /*glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);*/

 /*optionally, display the shader source to test if it is correct*/
/*
 printf("Vertex Shader Source:\n\n%s\n",vertexSource);
 printf("Fragment Shader Source:\n\n%s\n",fragmentSource);
*/

/*compile the vertex shader*/
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexSource, NULL);
glCompileShader(vertexShader);

/*glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
if(status==GL_TRUE){printf("Vertex Shader is Compiled\n");}*/

/*compile the fragment shader*/
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
glCompileShader(fragmentShader);

/*glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
if(status==GL_TRUE){printf("Fragment Shader is Compiled\n");}*/

/*connect the shaders into a program*/
shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
glUseProgram(shaderProgram);

/*set up the position attribute as defined in the shader program*/
posAttrib = glGetAttribLocation(shaderProgram, "position");
glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
glEnableVertexAttribArray(posAttrib);

 /*set up the global color which is used for all shapes drawn*/
 uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
 glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

 /*set background color*/
 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

/*set up the regular polygon*/
 init_polygon(); /*set up polygon with default values*/
 
 /*modify polygon before starting main loop*/
 main_polygon.sides=5;
 main_polygon.step=2;
 main_polygon.radians=0;
 
 init_checkerboard();
 main_check.rectsize=16;

/*
 can set whether the screen refreshes in sync with the hardware or whether it is unlimited
 and goes crazy fast! 0=crazy 1=vsync
*/
 SDL_GL_SetSwapInterval(1);
 
  /*this game will only load two fonts*/
 font_pico8=chaste_font_load("./font/PICO-8_4x6.bmp");
 font_8=chaste_font_load("./font/FreeBASIC Font 8.bmp");

 loop=1;
 while(loop)
 {
  /*SDL_GetWindowSize(window, &width,&height);
  glViewport( 0, 0, width, height );*/
  
  glClear(GL_COLOR_BUFFER_BIT);
 
  /*glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);
  gl_chaste_checker();*/
  
  glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);
  
  glUniform3f(uniColor, 0.0f, 1.0f, 0.0f);
  gl_chaste_polygon();
  main_polygon.radians+=PI/180; 
  
  glUniform3f(uniColor, 0.0f, 0.0f, 1.0f);
  gl_chaste_triangle(600,350,700,350,650,250);
  
  glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
  gl_chaste_rectangle(100,100,100,100);
  

  
  SDL_PollEvent( &event );
  if( event.type == SDL_QUIT ){loop=0;}
  if(event.type == SDL_KEYDOWN)
  {
   if(event.key.keysym.sym==SDLK_ESCAPE){loop=0;}
  }
  
  SDL_GL_SwapWindow( window );
  
 }

 /*free font surfaces from memory*/ 
 SDL_FreeSurface(font_pico8.surface);
 SDL_FreeSurface(font_8.surface);
 
 
 glDeleteProgram(shaderProgram);
 glDeleteShader(fragmentShader);
 glDeleteShader(vertexShader);
 glDeleteBuffers(1, &vbo);
 glDeleteVertexArrays(1, &vao);
 

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



