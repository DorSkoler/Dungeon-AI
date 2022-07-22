#include "ArmourBearer.h"
#include "NPC.h"
#include "glut.h"
#include "Definitions.h"
#include <math.h>
#include <string>
#include "GoToArsenal.h"

ArmourBearer::ArmourBearer()
{
}

ArmourBearer::ArmourBearer(double cx, double cy, int t)
{
	init();
	x = cx;
	y = cy;
	team = t;
}

ArmourBearer::~ArmourBearer()
{
}

void ArmourBearer::init()
{
	pCurrentState = new GoToArsenal();
	hp = MAX_HP_AB;
	grenade_count = MAX_GRENADES_AB;
	for (int i = 0; i < MAX_MAGAZINE_AB; i++)
		magazines.push_back(new Magazine());
}

void ArmourBearer::DrawMe()
{
	NPC::DrawMe();

	// cart
	glBegin(GL_LINE_STRIP);
	glVertex2d(x - 3, y);
	glVertex2d(x - 2, y - 1);
	glVertex2d(x - 0.5, y - 1);
	glVertex2d(x - 0.5, y);
	glEnd();
}

void ArmourBearer::DrawMyHp()
{
	glLineWidth(10);
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(xForInfo, yForInfo);
	glVertex2d(xForInfo + 20 * hp / MAX_HP_AB, yForInfo);
	glEnd();
	glLineWidth(1);

	NPC::drawInfo();

	std::string tmp = std::to_string(MAX_MAGAZINE_AB);
	char const* num_char = tmp.c_str();
	int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)num_char);
	glRasterPos2f(xForInfo + 54, yForInfo - 6);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num_char[0]);

	std::string tmp1 = std::to_string(MAX_GRENADES_AB);
	char const* num_char1 = tmp1.c_str();
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)num_char1);
	glRasterPos2f(xForInfo + 54, yForInfo - 1);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num_char1[0]);
}

void ArmourBearer::doSomething(int maze[MSZ][MSZ])
{
}

bool ArmourBearer::getSupplies(int g, int m)
{
	if (magazines.size() + m > MAX_MAGAZINE_AB || g + grenade_count > MAX_GRENADES_AB)
		return false;
	for (int i = 0; i < m; i++)
		magazines.push_back(new Magazine());
	grenade_count += g;
}
