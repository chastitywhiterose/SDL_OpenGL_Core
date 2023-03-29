/*chaste_opengl_core.h*/

/*
special functions to convert orthographic coordinates(as used in legacy with glOrtho)
into normalized coordinates. These depend on the global width and height variables of the window.
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





void chaste_gl_triangle(float x0,float y0,float x1,float y1,float x2,float y2)
{
 vertices[0]=ortho_x(x0);
 vertices[1]=ortho_y(y0);
 vertices[2]=ortho_x(x1);
 vertices[3]=ortho_y(y1);
 vertices[4]=ortho_x(x2);
 vertices[5]=ortho_y(y2);
 
 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
 glDrawArrays(GL_TRIANGLES, 0, 3);
}
