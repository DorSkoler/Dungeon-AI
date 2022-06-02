#include "Team.h"
#include <iostream>

void findXandY(int maze[MSZ][MSZ], int* cx, int* cy, int minX, int minY, int maxX, int maxY)
{
	do {
		*cx = rand() % (maxX - minX) + minX;
		*cy = rand() % (maxY - minY) + minY;
	} while (maze[*cy][*cx] != SPACE);
}

Team::Team(int t, Room* r, int maze[MSZ][MSZ], int begin)
{
	x = 0, y = 0;
	team_num = t;
	int minX = r->getCenterX() - r->getWidth() / 2;
	int maxX = r->getWidth() / 2 + r->getCenterX();
	int minY = r->getCenterY() - r->getHeight() / 2;
	int maxY = r->getHeight() / 2 + r->getCenterY();
	int cx, cy;
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = begin;
	ab = new ArmourBearer(cx, cy, t);
	ab->setMazeNum(begin);
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = begin+1;
	s1 = new Soldier(cx, cy, t);
	s1->setMazeNum(begin+1);
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = begin+2;
	s2 = new Soldier(cx, cy, t);
	s2->setMazeNum(begin+2);
}

void Team::drawTeam()
{
	if (s1)
		s1->DrawMe("s1");
	if (s2)
		s2->DrawMe("s2");
	if (ab)
		ab->DrawMe();
}

void Team::setTeamInfo(int cx, int cy)
{
	x = cx;
	y = cy;
	if (s1)
		s1->setInfoXandY(cx, cy);
	if (s2)
		s2->setInfoXandY(cx, cy - 15);
	if (ab)
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
	if (s1) {
		glColor3d(0, 0, 0);
		unsigned char string2[] = "Soldier1-";
		w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string2);
		glRasterPos2f(s1->getInfoX() - 19, s1->getInfoY() - 1);
		for (int i = 0; i < 9; i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string2[i]);
		}
		s1->DrawMyHp();
	}
	if (s2) {
		unsigned char string3[] = "Soldier2-";
		w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string3);
		glRasterPos2f(s2->getInfoX() - 19, s2->getInfoY() - 1);
		for (int i = 0; i < 9; i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string3[i]);
		}
		s2->DrawMyHp();
	}
	if (ab) {
		unsigned char string4[] = "ArmourB-";
		w = glutBitmapLength(GLUT_BITMAP_8_BY_13, string4);
		glRasterPos2f(ab->getInfoX() - 17, ab->getInfoY() - 1);
		for (int i = 0; i < 8; i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string4[i]);
		}
		ab->DrawMyHp();
	}
	
}


std::vector<Bullet*> Team::checkMoveBullets(int maze[MSZ][MSZ])
{
	Bullet* hit1 = nullptr, *hit2 = nullptr;
	std::vector<Bullet*> hittingBullets;
	if (s1) {
		hit1 = s1->MoveBullets(maze);
		if (hit1)
			hittingBullets.push_back(hit1);
		s1->Move(maze);
	}
	if (s2) {
		hit2 = s2->MoveBullets(maze);
		if (hit2)
			hittingBullets.push_back(hit2);
	}
	
	//s2->Move(maze);
	//ab->Move(maze);
	return hittingBullets;
}

void Team::gotHit(int cx, int cy)
{
	if (s1 && s1->isThisXandYisNPC(cx, cy))
		s1->setHp(50);
	if (s2 && s2->isThisXandYisNPC(cx, cy))
		s2->setHp(50);
	if (ab && ab->isThisXandYisNPC(cx, cy))
		ab->setHp(50);
}

bool Team::checkAlive()
{
	if (s1 && s1->getHp() == 0)
		s1 = nullptr;
	if (s2 && s2->getHp() == 0)
		s2 = nullptr;
	if (ab && ab->getHp() == 0)
		ab = nullptr;
	allDead = !(ab || s1 || s2);
	return allDead;
}

void Team::checkShowBullets()
{
	if (s1)
		s1->showBullets();
	if (s2)
		s2->showBullets();
}


