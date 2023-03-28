/*
    Compile and run with: gcc main.c `sdl2-config --libs --cflags` -lGL -Wall && ./a.out
*/

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>

#include <stdio.h>

#include "ortho.h"

    static const int width = 1280;
    static const int height = 720;
        
    int loop=1;
    SDL_Window *window;
    SDL_GLContext context;
    SDL_Event event;
    

    
    
        GLfloat g_vertex_buffer_data[] = {
    /*  R, G, B, A, X, Y  */
        150, 100, 1, 0, 0, 1,
        100, 200, 0, 1, 0, 1,
        200, 200, 0, 0, 1, 1

    };



int main( int argc, char * argv[] )
{
    SDL_Init( SDL_INIT_VIDEO );
    
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    window = SDL_CreateWindow("Modern OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    context = SDL_GL_CreateContext( window );

    /*load the shaders defined in ortho.h*/
    load_shaders();

/*    glDisable( GL_DEPTH_TEST );*/
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glViewport( 0, 0, width, height );

    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );

    glEnableVertexAttribArray( attrib_position );
    glEnableVertexAttribArray( attrib_color );

    glVertexAttribPointer( attrib_position, 2, GL_FLOAT, GL_FALSE, sizeof( float ) * 6, (void *)0 );
    glVertexAttribPointer( attrib_color, 4, GL_FLOAT, GL_FALSE, sizeof( float ) * 6, (void *)(2 * sizeof(float)) );

    glBufferData( GL_ARRAY_BUFFER, sizeof( g_vertex_buffer_data ), g_vertex_buffer_data, GL_STATIC_DRAW );

    
    mat4x4_ortho( projection_matrix, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 100.0f );
    glUniformMatrix4fv( glGetUniformLocation( program, "u_projection_matrix" ), 1, GL_FALSE, projection_matrix );

 while(loop)
 {
  glClear( GL_COLOR_BUFFER_BIT );
  
  
  glBindVertexArray( vao );
  glDrawArrays( GL_TRIANGLES, 0, 3 );

  

  while( SDL_PollEvent( &event ) )
  {
   if( event.type == SDL_QUIT ){loop=0;}
   if(event.type == SDL_KEYUP)
   {
    if(event.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }
  }


        SDL_GL_SwapWindow( window );
        /*SDL_Delay( 1 );*/
    }

    SDL_GL_DeleteContext( context );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}

