#include "Team.h"
#include <iostream>

void findXandY(int maze[MSZ][MSZ], int* x, int* y, int minX, int minY, int maxX, int maxY)
{
	do {
		*x = rand() % (maxX - minX) + minX;
		*y = rand() % (maxY - minY) + minY;
	} while (maze[*y][*x] != SPACE);
}

Team::Team(int t, Room* r, int maze[MSZ][MSZ])
{
	team_num = t;
	int minX = r->getCenterX() - r->getWidth() / 2;
	int maxX = r->getWidth() / 2 + r->getCenterX();
	int minY = r->getCenterY() - r->getHeight() / 2;
	int maxY = r->getHeight() / 2 + r->getCenterY();
	int x, y;
	findXandY(maze, &x, &y, minX, minY, maxX, maxY);
	maze[y][x] = ARMOURBEARER;
	ab = new ArmourBearer(x, y, t);
	findXandY(maze, &x, &y, minX, minY, maxX, maxY);
	maze[y][x] = SOLDIER;
	s1 = new Soldier(x, y, t);
	findXandY(maze, &x, &y, minX, minY, maxX, maxY);
	maze[y][x] = SOLDIER;
	s2 = new Soldier(x, y, t);
}

void Team::drawTeam()
{
	s1->DrawMe();
	s2->DrawMe();
	ab->DrawMe();
}


