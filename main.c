#include <stdio.h>
#include <GL/glut.h>

int rad;
int i;

void plot_point(int x, int y, int X, int Y)
{
  glBegin(GL_POINTS);
  glVertex2i(X+x, Y+y);
  glVertex2i(X+x, Y-y);
  glVertex2i(X+y, Y+x);
  glVertex2i(X+y, Y-x);
  glVertex2i(X-x, Y-y);
  glVertex2i(X-y, Y-x);
  glVertex2i(X-x, Y+y);
  glVertex2i(X-y, Y+x);
  glEnd();
}

void bresenham_circle(int X, int Y, int r)
{
  int x=0,y=r;
  float pk=(5.0/4.0)-r;

  plot_point(x,y,X,Y);
  
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_point(x,y,X,Y);
  }
  glFlush();
}

void recurse(int a,int b,int radius,int preva, int prevb, int rep)
{
	if(rep == i)
	return;
	
	if(preva == a)
	{
		if((prevb-b)<0){
			glColor3f(1.0,0.0,0.0);
			bresenham_circle(a-((3*radius)/2), b, radius/2);
			bresenham_circle(a, b+((3*radius)/2), radius/2);
			bresenham_circle(a+((3*radius)/2), b, radius/2);
			
			recurse(a-((3*radius)/2), b, radius/2,a,b,rep+1);
			recurse(a, b+((3*radius)/2), radius/2,a,b,rep+1);
			recurse(a+((3*radius)/2), b, radius/2,a,b,rep+1);
		}
		if((prevb-b)>0)
		{
			glColor3f(0.0,1.0,0.0);
			bresenham_circle(a+((3*radius)/2), b, radius/2);
			bresenham_circle(a, b-((3*radius)/2), radius/2);
			bresenham_circle(a-((3*radius)/2), b, radius/2);
			
			recurse(a+((3*radius)/2), b, radius/2,a,b,rep+1);
			recurse(a, b-((3*radius)/2), radius/2,a,b,rep+1);
			recurse(a-((3*radius)/2), b, radius/2,a,b,rep+1);
		}
	}
	
	if(prevb == b)
	{
		if((preva-a)<0)
		{
			glColor3f(0.0,0.0,1.0);
			bresenham_circle(a, b+((3*radius)/2), radius/2);
			bresenham_circle(a+((3*radius)/2), b, radius/2);
			bresenham_circle(a, b-((3*radius)/2), radius/2);
			
			recurse(a, b+((3*radius)/2), radius/2,a,b,rep+1);
			recurse(a+((3*radius)/2), b, radius/2,a,b,rep+1);
			recurse(a, b-((3*radius)/2), radius/2,a,b,rep+1);
		}
		if((preva-a)>0)
		{
			glColor3f(1.0,0.0,1.0);
			bresenham_circle(a, b-((3*radius)/2), radius/2);
			bresenham_circle(a-((3*radius)/2), b, radius/2);
			bresenham_circle(a, b+((3*radius)/2), radius/2);
			
			recurse(a, b-((3*radius)/2), radius/2,a,b,rep+1);
			recurse(a-((3*radius)/2), b, radius/2,a,b,rep+1);
			recurse(a, b+((3*radius)/2), radius/2,a,b,rep+1);
		}
	}
}

void renderBitmapString(int x, int y, const char* str)
{
	int l= strlen(str),i;
	glRasterPos2i(x, y);
	for(i=0; i<l;i++){
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, str[i]);
	}
}

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	renderBitmapString(-200,0,"Circle Fractal By Shahzeb Rizvi");
	glFlush();
	bresenham_circle(0,0,rad);
	glColor3f(1.0,0.0,0.0);
	bresenham_circle(0,-(3*rad)/2, rad/2);
	bresenham_circle(0, (3*rad)/2, rad/2);
	bresenham_circle((3*rad)/2, 0, rad/2);
	bresenham_circle(-(3*rad)/2, 0, rad/2);
	
	recurse(-(3*rad)/2, 0, rad/2,0,0,1);	
	recurse(0, (3*rad)/2, rad/2,0,0,1);
	recurse((3*rad)/2, 0, rad/2,0,0,1);
	recurse(0,-(3*rad)/2, rad/2,0,0,1);
}

void Init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1000,1000,-1000,1000);
}

int main(int argc, char *argv[]) {
	printf("Enter the number of recursion!\n");
	scanf("%d",&i);
	printf("Enter the length of radius!\n");
	scanf("%d",&rad);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800,800);
	glutCreateWindow("Fractal");
	Init();
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
