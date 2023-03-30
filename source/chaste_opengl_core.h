/*chaste_opengl_core.h*/

/*
special functions to convert orthographic coordinates(as used in legacy with glOrtho)
into normalized coordinates. These depend on the global width and height variables of the window.
I figured out the formula in my head because I understand how it works.

I shall explain it like this:
*/

float gl_chastity_ortho_x(float f)
{
 f=f/width*2-1;
 return f;
}

float gl_chastity_ortho_y(float f)
{
 f=f/height*2-1;
 return -f;
}


float (*ortho_x)(float)=gl_chastity_ortho_x;
float (*ortho_y)(float)=gl_chastity_ortho_y;



/*
 Loads the 6 floats into the global vertices array.
 2 dimensions times 3 points in a triangle is always 6.
 So it updates the buffer like this:
 
 glBufferData(GL_ARRAY_BUFFER,6*sizeof(float),vertices,GL_DYNAMIC_DRAW);

 And then draws a triangle using:
 
 glDrawArrays(GL_TRIANGLES, 0, 3);
 
 Because there are 3 points and we are only using those 3 points / 6 float vertices
 
 These pages provide more detail on these functions:
 https://docs.gl/gl3/glBufferData
 https://docs.gl/gl3/glDrawArrays
*/

void chaste_gl_triangle(float x0,float y0,float x1,float y1,float x2,float y2)
{
 vertices[0]=ortho_x(x0);
 vertices[1]=ortho_y(y0);
 vertices[2]=ortho_x(x1);
 vertices[3]=ortho_y(y1);
 vertices[4]=ortho_x(x2);
 vertices[5]=ortho_y(y2);
 
 glBufferData(GL_ARRAY_BUFFER,6*sizeof(float),vertices,GL_DYNAMIC_DRAW);
 glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*
This function draws a square by drawing two triangles. It sets the 12 vertices required
for the 6 corners for 2 triangles

2 triangles = 6 points of X and Y coordinates
*/

void chaste_gl_rectangle(float x,float y,float w,float h)
{
 vertices[0]=ortho_x(x);
 vertices[1]=ortho_y(y);
 vertices[2]=ortho_x(x+w);
 vertices[3]=ortho_y(y);
 vertices[4]=ortho_x(x);
 vertices[5]=ortho_y(y+h);
 
 vertices[6]=ortho_x(x+w);
 vertices[7]=ortho_y(y+h);
 vertices[8]=ortho_x(x+w);
 vertices[9]=ortho_y(y);
 vertices[10]=ortho_x(x);
 vertices[11]=ortho_y(y+h);

 glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), vertices, GL_DYNAMIC_DRAW);
 glDrawArrays(GL_TRIANGLES, 0, 6);
}




/*
For more information on OpenGL functions, I use this site:
https://docs.gl/
*/
