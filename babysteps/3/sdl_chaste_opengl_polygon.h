/*
This is a part of my code for making convex regular polygons. It has been copied and modified from my original chaste library.
*/


struct polygon
{
 double cx,cy;
 int sides;
 double radius;
 double radians;
 int color;
 int step; /*used only in star polygons of 5 or more sides*/
};

struct polygon main_polygon;


void init_polygon()
{
 main_polygon.cx=width/2;
 main_polygon.cy=height/2;
 main_polygon.sides=3;
 main_polygon.radius=height/2;
 main_polygon.radians=0;
 main_polygon.color=0xFFFFFF;
 main_polygon.step=2;
}

/*these point arrays are temporary and not included in the polygon structure*/
int polygon_xpoints[0x1000],polygon_ypoints[0x1000];

/*Define PI the same as M_PI in math.h*/
 #define PI 3.14159265358979323846f

/*
 this function created because the standard round function did not exist in C until 1999 standard.
 I only use 1989 standard. It is sometimes helpful to round to neared integer when the data type requires it.
 Original source here: https://en.cppreference.com/w/c/numeric/math/round
*/
double chaste_round(double x)
{
 return x<0 ? ceil(x - 0.5) : floor(x + 0.5);
}


void chaste_polygon_points()
{
 double angle,x,y;
 int i=0;
 while(i<main_polygon.sides)
 {
  angle=2*PI*i/main_polygon.sides+main_polygon.radians;
  x=main_polygon.cx+sin(angle)*main_polygon.radius;
  y=main_polygon.cy-cos(angle)*main_polygon.radius;
  polygon_xpoints[i]=chaste_round(x);
  polygon_ypoints[i]=chaste_round(y);
  i++;
 }
}



/*a function pointer that points to whichever function I currently use to get the points
 for the next polygon drawn. This is for conveniently testing new functions.
*/
void (*poly_points_func)()=chaste_polygon_points;


/*
polygon

The polygon is filled. This is the reason I learned OpenGL.
SDL lacks polygon/triangle drawing functions.
*/
void gl_chaste_polygon()
{
 int i;
 poly_points_func();
 glBegin(GL_POLYGON);
 i=0;
 while(i<main_polygon.sides)
 {
  glVertex2f(polygon_xpoints[i],polygon_ypoints[i]);
  i+=1;
 }
 glEnd();
}

/*
I finally learned how to use a function pointer!
This function pointer allows me to change which function is currently being called each frame by various keypresses while the program is running. It defaults to the filled polygon function above but can be changed to anything else!
*/
void (*polyfunc)()=gl_chaste_polygon;



/*
polyline

only the lines are drawn. The polygon is not filled.
*/
void gl_chaste_polygon1()
{
 int i;
 poly_points_func();
 glBegin(GL_LINE_LOOP);
 i=0;
 while(i<main_polygon.sides)
 {
  glVertex2f(polygon_xpoints[i],polygon_ypoints[i]);
  i+=1;
 }
 glEnd();
}


/*
filled star polygon
*/
void gl_chaste_polygon2()
{
 int i,i1;
 poly_points_func();
 glBegin(GL_TRIANGLES);
 i=0; i1=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  glVertex2f(polygon_xpoints[i],polygon_ypoints[i]);
  glVertex2f(polygon_xpoints[i1],polygon_ypoints[i1]);
  glVertex2f(main_polygon.cx,main_polygon.cy);
  i+=1;
 }
 glEnd();
}


/*
star polyline

only the lines are drawn. The polygon is not filled.
*/
void gl_chaste_polygon3()
{
 int i,i1,i2;
 poly_points_func();
 glBegin(GL_LINE_LOOP);
 i=0; i1=0;i2=0;
 while(i<main_polygon.sides)
 {
  glVertex2f(polygon_xpoints[i1],polygon_ypoints[i1]);
  /*printf("i1==%d\n",i1);*/
  i1=(i1+main_polygon.step)%main_polygon.sides;
  if(i1==i2){i2++;i1=i2;glEnd();glBegin(GL_LINE_LOOP);}
  i+=1;
 }
 glEnd();
}

/*
lines are drawn from the center to the corners but not from corner to corner.
*/
void gl_chaste_polygon4()
{
 int i;
 poly_points_func();
 glBegin(GL_LINES);
 i=0;
 while(i<main_polygon.sides)
 {
  glVertex2f(polygon_xpoints[i],polygon_ypoints[i]);
  glVertex2f(main_polygon.cx,main_polygon.cy);
  i+=1;
 }
 glEnd();
}

/*
Only the points of the corners are drawn.
*/
void gl_chaste_polygon5()
{
 int i;
 poly_points_func();
 glBegin(GL_POINTS);
 i=0;
 while(i<main_polygon.sides)
 {
  glVertex2f(polygon_xpoints[i],polygon_ypoints[i]);
  i+=1;
 }
 glEnd();
}




/*
 opengl version of the checkerboard function
 uses global width and height of the window and the rectsize global defined below
 although this is a rather efficient checkerboard drawing function, it does noticably slow the polygon down compared to when the polygon is the only thing being drawn. Until I learn fast blitting methods this may be an issue. But it's still a hundred times faster than my previous SDL methods even so.
*/
int rectsize=16;
void gl_chaste_checker()
{
 int x,y,index,index1;
 float v[4];

 /*store current drawing color in here*/
 glGetFloatv(GL_CURRENT_COLOR,v);

 index=0;
 y=0;
 while(y<height)
 {
  index1=index;
  x=0;
  while(x<width)
  {
   if(index==0){glColor3f(0.0f, 0.0f, 0.0f);}
   if(index==1){glColor3f(1.0f, 1.0f, 1.0f);}
   glRecti(x,y,x+rectsize,y+rectsize);
   index^=1;
   x+=rectsize;
  }
  index=index1^1;
  y+=rectsize;
 }

 /*restore original drawing color from here*/
 glColor4fv(v);

}



/*
simple function to enable XOR mode
*/
void gl_Enable_XOR()
{
 glEnable(GL_COLOR_LOGIC_OP);
 glLogicOp(GL_XOR);
}

/*
simple function to disable XOR mode
*/
void gl_Disable_XOR()
{
 glDisable(GL_COLOR_LOGIC_OP);
}



/*
These references are valuable when I need to look up a function.

https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/
http://freeglut.sourceforge.net/docs/api.php
https://www.opengl.org/resources/libraries/glut/spec3/spec3.html
https://www.khronos.org/opengl/wiki/OpenGL_Type
https://docs.gl/gl2/glBegin
https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glReadPixels.xml
https://github.com/markkilgard/glut
*/
