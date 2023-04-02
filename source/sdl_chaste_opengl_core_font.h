/*
sdl_chaste_opengl_core_font.h

A heavily modified version of my font library I used for the SDL version of Chaste Tris. This time it uses OpenGL instead of blitting functions.

*/




/*
font structure

In the raylib code, this uses a Texture2D. In another graphics library it may be different if ported.
In the SDL version, a surface is used.
*/
struct chaste_font
{
 int char_width; /*width of a char*/
 int char_height; /*height of a char*/
 SDL_Surface *surface; /*the surface of the image of loaded font*/
};


/*global fonts that will be reused many times*/
struct chaste_font main_font,font_8,font_16,font_32,font_64,font_128,font_pico8;




/*function to load a font and return a structure with the needed data to draw later*/
struct chaste_font chaste_font_load(char *s)
{
 struct chaste_font new_font;
 SDL_Surface *temp_surface;
 printf("Loading font: %s\n",s);

 /*load bitmap to temporary surface*/
 temp_surface=SDL_LoadBMP(s);

 /*convert to RGBA32 pixel format for easy handling for later functions*/
 new_font.surface=SDL_ConvertSurfaceFormat(temp_surface, SDL_PIXELFORMAT_RGBA32, 0);
 
 /*free the temp surface*/
 SDL_FreeSurface(temp_surface); 

 if(new_font.surface==NULL){printf( "SDL could not load image! SDL_Error: %s\n",SDL_GetError());return new_font;}

 /*
  by default,font height is detected by original image height
  but the font width is the width of the image divided by 95
  because there are exactly 95 characters in the font format that I created.
 */
 new_font.char_width=new_font.surface->w/95; /*there are 95 characters in my font files*/
 new_font.char_height=new_font.surface->h;

 if(new_font.char_height==0)
 {
  printf("Something went horribly wrong loading the font from file:\n%s\n",s);
 }
 else
 {
  /*printf("Font loaded correctly\n");*/
  printf("Size of loaded font is %d,%d\n",new_font.char_width,new_font.char_height);
 }

 return new_font;
}

