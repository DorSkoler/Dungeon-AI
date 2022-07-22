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
	ab = new ArmourBearer(cx, cy, t, r);
	ab->setMazeNum(begin);
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = begin+1;
	s1 = new Soldier(cx, cy, t, r);
	s1->setMazeNum(begin+1);
	findXandY(maze, &cx, &cy, minX, minY, maxX, maxY);
	maze[cy][cx] = begin+2;
	s2 = new Soldier(cx, cy, t, r);
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
		s1->setInfoXandY(cx, cy - 15);
	if (s2)
		s2->setInfoXandY(cx, cy - 30);
	if (ab)
		ab->setInfoXandY(cx, cy);
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
	if (s1) {
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


void Team::checkMoveBullets(int maze[MSZ][MSZ], int hits[NUM_PLAYERS])
{
	Bullet* hit1 = nullptr, *hit2 = nullptr;
	std::vector<Bullet*> hittingBullets;
	if (s1) {
		s1->MoveBullets(maze, hits);
	}
	if (s2) {
		s2->MoveBullets(maze, hits);
	}
}

void Team::gotHit(int hits[NUM_PLAYERS])
{
	if (s1 && hits[(team_num - 1) * 3 + 1] > 0)
		{
			s1->setHp(HIT_RATE / hits[(team_num - 1) * 3 + 1]);
			std::cout << "s1 got hit in team " << team_num << ", -" << HIT_RATE / hits[(team_num - 1) * 3 + 1] << "hp\n";
			hits[(team_num - 1) * 3 + 1] = 0;
		}
	if (s2 && hits[(team_num - 1) * 3 + 2] > 0)
		{
			s2->setHp(HIT_RATE / hits[(team_num - 1) * 3 + 2]);
			std::cout << "s2 got hit in team " << team_num << ", -" << HIT_RATE / hits[(team_num - 1) * 3 + 2] << "hp\n";
			hits[(team_num - 1) * 3 + 2] = 0;
		}

	if (ab && hits[(team_num - 1) * 3] > 0)
		{
			ab->setHp(HIT_RATE / hits[(team_num - 1) * 3]);
			std::cout << "ab got hit in team " << team_num << ", -" << HIT_RATE / hits[(team_num - 1) * 3] << "hp\n";
			hits[(team_num - 1) * 3] = 0;
		}
}

bool Team::checkAlive(int maze[MSZ][MSZ])
{
	int cx, cy;
	if (s1 && s1->getHp() == 0) {
		cy = (int)(s1->getY());
		cx = (int)(s1->getX());
		maze[cy][cx] = SPACE;
		s1 = nullptr;
	}
	if (s2 && s2->getHp() == 0) {
		cy = (int)(s2->getY());
		cx = (int)(s2->getX());
		maze[cy][cx] = SPACE;
		s2 = nullptr;
	}
	if (ab && ab->getHp() == 0) {
		cy = (int)(ab->getY());
		cx = (int)(ab->getX());
		maze[cy][cx] = SPACE;
		ab = nullptr;
	}
	allDead = !(ab || s1 || s2);
	return allDead;
}

void Team::doSomething(Team* enemy ,int maze[MSZ][MSZ], Room rooms[NUM_ROOMS])
{
	if (s1)
		s1->doSomething(enemy ,maze, rooms);
	if (s2)
		s2->doSomething(enemy, maze, rooms);
	//if (ab)
	//	ab->doSomething(maze);
}

NPC* Team::getNpcByIndex(int index)
{
	if (index == 0)
		return ab;
	if (index == 1)
		return s1;
	if (index == 2)
		return s2;
}

void Team::checkLocation(Room rooms[NUM_ROOMS])
{
	if (s1)
		s1->checkPassOrRoom(rooms);
	if (s2)
		s2->checkPassOrRoom(rooms);
	if (ab)
		ab->checkPassOrRoom(rooms);
}

void Team::checkShowBullets()
{
	if (s1)
		s1->showBullets();
	if (s2)
		s2->showBullets();
}


