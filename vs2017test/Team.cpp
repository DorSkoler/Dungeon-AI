#include "Team.h"
#include <iostream>

void findXandY(int maze[MSZ][MSZ], int* cx, int* cy, int minX, int minY, int maxX, int maxY)
{
	do {
		*cx = rand() % (maxX - minX) + minX;
		*cy = rand() % (maxY - minY) + minY;
	} while (maze[*cy][*cx] != SPACE);
}

Team::Team(int t, Room* r, int maze[MSZ][MSZ])
{
	x = 0, y = 0;
	team_num = t;
	int minX = r->getCenterX() - r->getWidth() / 2;
	int maxX = r->getWidth() / 2 + r->getCenterX();
	int minY = r->getCenterY() - r->getHeight() / 2;
	int maxY = r->getHeight() / 2 + r->getCenterY();
	int cx, cy;
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = ARMOURBEARER;
	ab = new ArmourBearer(cx, cy, t);
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = SOLDIER;
	s1 = new Soldier(cx, cy, t);
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = SOLDIER;
	s2 = new Soldier(cx, cy, t);
}

void Team::drawTeam()
{
	s1->DrawMe("s1");
	s2->DrawMe("s2");
	ab->DrawMe();
}

void Team::setTeamInfo(int cx, int cy)
{
	x = cx;
	y = cy;
	s1->setInfoXandY(cx, cy);
	s2->setInfoXandY(cx, cy - 15);
	ab->setInfoXandY(cx, cy - 30);
}

void Team::drawInfo()
{
	// Team text
	glColor3d(0, 0, 0);
	unsigned char string[] = "Team ";
	int w;
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string);
	glRasterPos2f(x, y + 4);
	for (int i = 0; i < 5; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
	
	if (team_num == 1) {
		glColor3d(1, 0, 0);
		unsigned char string1[] = "Red ";
		w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string1);
		glRasterPos2f(x + 10, y + 4);
		for (int i = 0; i < 4; i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
		}
	}
	else {
		glColor3d(0, 0, 1);
		unsigned char string1[] = "Blue";
		w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string1);
		glRasterPos2f(x + 10, y + 4);
		for (int i = 0; i < 4; i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string1[i]);
		}
	}
	glColor3d(0, 0, 0);
	unsigned char string2[] = "Soldier1-";
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string2);
	glRasterPos2f(s1->getInfoX() - 19, s1->getInfoY() - 1);
	for (int i = 0; i < 9; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string2[i]);
	}
	unsigned char string3[] = "Soldier2-";
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string3);
	glRasterPos2f(s2->getInfoX() - 19, s2->getInfoY() - 1);
	for (int i = 0; i < 9; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
	}
	unsigned char string4[] = "ArmourB-";
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string4);
	glRasterPos2f(ab->getInfoX() - 17, ab->getInfoY() - 1);
	for (int i = 0; i < 8; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
	}
	s1->DrawMyHp();
	s2->DrawMyHp();
	ab->DrawMyHp();
}

std::vector<Bullet*> Team::checkMoveBullets(int maze[MSZ][MSZ])
{
	std::vector<Bullet*> hittingBullets;
	Bullet* hit1 = s1->MoveBullets(maze);
	if (hit1)
		hittingBullets.push_back(hit1);
	Bullet* hit2 = s2->MoveBullets(maze);
	if (hit2)
		hittingBullets.push_back(hit2);
	//s1->Move(maze);
	//s2->Move(maze);
	//ab->Move(maze);
	return hittingBullets;
}

void Team::gotHit(int cx, int cy)
{
	if (s1->isThisXandYisNPC(cx, cy))
		s1->setHp(s1->getHp() - 50);
	if (s2->isThisXandYisNPC(cx, cy))
		s2->setHp(s2->getHp() - 50);
	if (ab->isThisXandYisNPC(cx, cy))
		ab->setHp(ab->getHp() - 50);
}

void Team::checkShowBullets()
{
	s1->showBullets();
	s2->showBullets();
}
