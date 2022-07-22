#include "glut.h"
#include "NPC.h"

const int MSZ = 100; // map size

NPC* pn = nullptr;
NPC* pn1 = nullptr;


void init()
{	//          Red Green Blue 
	glClearColor(0.5, 0.8, 0.5, 0);// color of window background
	
	// set the main axes
	glOrtho(0, MSZ, 0, MSZ,- 1, 1);

	pn = new NPC(20, 70);
	pn1 = new NPC(80, 50);
}

void DrawTree(double x, double y)
{
	glLineWidth(3);
	glColor3d(0.5, 0.5, 0); // brown
	glBegin(GL_LINES);
	glVertex2d(x, y);
	glVertex2d(x, y+2);
	glEnd();

	glColor3d(0, 0.4, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x-2, y+2);
	glVertex2d(x+2, y + 2);
	glVertex2d(x , y + 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(x - 1.5, y + 3.5);
	glVertex2d(x + 1.5, y + 3.5);
	glVertex2d(x, y + 5.5);
	glEnd();
	glLineWidth(1);
}

void DrawLumberJack(double x, double y)
{
	glColor3d(0.8, 0.8, 0.4); // brown
	glBegin(GL_POLYGON);
	glVertex2d(x - 5, y );
	glVertex2d(x- 5, y + 5);
	glVertex2d(x + 5, y + 5);
	glVertex2d(x + 5, y );
	glEnd();
	glColor3d(0, 0, 0); //frame
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 5, y);
	glVertex2d(x - 5, y + 5);
	glVertex2d(x + 5, y + 5);
	glVertex2d(x + 5, y);
	glEnd();

	glColor3d(0.3, 0.3, 0); // door
	glBegin(GL_POLYGON);
	glVertex2d(x - 1, y);
	glVertex2d(x - 1, y + 3);
	glVertex2d(x + 1, y + 3);
	glVertex2d(x + 1, y);
	glEnd();

}


void DrawHome(double x, double y)
{
	glColor3d(1, 1, 1); // brown
	glBegin(GL_POLYGON);
	glVertex2d(x - 5, y);
	glVertex2d(x - 5, y + 10);
	glVertex2d(x + 5, y + 10);
	glVertex2d(x + 5, y);
	glEnd();
	glColor3d(0, 0, 0); //frame
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 5, y);
	glVertex2d(x - 5, y + 10);
	glVertex2d(x + 5, y + 10);
	glVertex2d(x + 5, y);
	glEnd();

	glColor3d(0, 0, 0.4); // left window
	glBegin(GL_POLYGON);
	glVertex2d(x - 4, y+3);
	glVertex2d(x - 4, y + 6);
	glVertex2d(x - 1, y + 6);
	glVertex2d(x - 1, y+3);
	glEnd();

	glColor3d(0, 0, 0.4); // right window
	glBegin(GL_POLYGON);
	glVertex2d(x +1, y + 3);
	glVertex2d(x +1, y + 6);
	glVertex2d(x +4 , y + 6);
	glVertex2d(x + 4, y + 3);
	glEnd();

	// roof
	glColor3d(1, 0, 0); // right window

	glBegin(GL_POLYGON);
	glVertex2d(x - 5, y + 10);
	glVertex2d(x + 5, y + 10);
	glVertex2d(x , y + 18);
	glEnd();


}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	
	DrawTree(80, 80);
	DrawTree(85, 81);
	DrawTree(78, 84);

	DrawLumberJack(20, 15);
	DrawHome(20, 75);

	if (pn != nullptr)
		pn->DrawMe();
	if (pn1 != nullptr)
		pn1->DrawMe();

	glutSwapBuffers(); // show all
}

void idle()
{

	if (pn != nullptr)
		pn->DoSomeThing();
	if (pn1 != nullptr)
		pn1->DoSomeThing();

	glutPostRedisplay(); // indirect call to refresh function (display)
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double buffering for animation
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(800, 100);
	glutCreateWindow("FSM Example");

	glutDisplayFunc(display); // sets display function as window refresh function
	glutIdleFunc(idle); // runs all the time when nothing happens

	init();

	glutMainLoop(); // starts window queue of events
}