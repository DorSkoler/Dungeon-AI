#include "Soldier.h"
#include "IdleSoldier.h"
#include <iostream>
#include "Team.h"

Soldier::Soldier()
{
	init();
}

Soldier::Soldier(double cx, double cy, int t, Room* r)
{
	init();
	x = cx;
	y = cy;
	team = t;
	currentRoom = r;
}

void Soldier::init()
{
	currentGrenade = nullptr;
	hp = MAX_HP_SOLDIER;
	grenade_count = MAX_GRENADES_SOLDIER;
	for (int i = 0; i < MAX_MAGAZINE_SOLDIER; i++)
		magazines.push_back(new Magazine());
	pCurrentState = new IdleSoldier();
	pCurrentState->OnEnter(this);
}

void Soldier::DrawMe(const char* string)
{
	NPC::DrawMe();

	glColor3d(0, 0, 0);
	int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)string);
	glRasterPos2f(x - 0.2, y + 3);
	for (int i = 0; i < 2; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
}

void Soldier::DrawMyHp()
{
	// hp
	glLineWidth(10);
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(xForInfo, yForInfo);
	glVertex2d(xForInfo + 20 * hp / MAX_HP_SOLDIER, yForInfo);
	glEnd();
	glLineWidth(1);

	NPC::drawInfo();

	std::string tmp = std::to_string(MAX_MAGAZINE_SOLDIER);
	char const* num_char = tmp.c_str();
	int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)num_char);
	glRasterPos2f(xForInfo + 54, yForInfo - 6);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num_char[0]);

	std::string tmp1 = std::to_string(MAX_GRENADES_SOLDIER);
	char const* num_char1 = tmp1.c_str();
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)num_char1);
	glRasterPos2f(xForInfo + 54, yForInfo - 1);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num_char1[0]);

}

Bullet* Soldier::MoveBullets(int maze[MSZ][MSZ], int hits[NUM_PLAYERS])
{
	if (magazines.size() > 0) {
		Magazine* pm = *(magazines.begin());
		isShooting = pm->Move(maze, hits);
	}
	if (currentGrenade) {
		if (currentGrenade->Exploding(maze, hits))
			currentGrenade = nullptr;
	}
	return nullptr;
}

void Soldier::showBullets()
{
	Magazine* pm = *(magazines.begin());
	pm->show();
	if (currentGrenade) {
		std::cout << "here\n";
		currentGrenade->show();
	}
}

void Soldier::shootBullet()
{
	if (magazines.empty())
		return;
	Magazine* pm = *(magazines.begin());
	if (pm->isEmpty()) {
		magazines.erase(magazines.begin());
		if (magazines.empty())
			return;
		pm = *(magazines.begin());
	}
	isShooting = true;
	pm->fire(x, y, dx, dy, team);
}

void Soldier::throwGrenade(int maze[MSZ][MSZ])
{
	if (currentGrenade == nullptr) {
		if (grenade_count == 0)
			return;
		int min = -GRENADE_THROW_RANGE;
		int rangeX, rangeY;
		do {
			rangeX = rand() % (GRENADE_THROW_RANGE - min) + min;
			rangeY = rand() % (GRENADE_THROW_RANGE - min) + min;
		} while (maze[(int)y + rangeY][(int)x + rangeX] == WALL);
		currentGrenade = new Grenade(x + rangeX, y + rangeY, team, (int)x, (int)y);
		currentGrenade->Explode();
		std::cout << "exploded\n";
		grenade_count--;
	}
}

void Soldier::doSomething(Team* enemy, int maze[MSZ][MSZ], Room rooms[NUM_ROOMS])
{
	NPC* target = nullptr;
	int myRoom = whichRoom(this, rooms);
	if (idle) {
		if (movesChased > 50) {
			int roomNum;
			do {
				roomNum = rand() % NUM_ROOMS;
			} while (roomNum != myRoom);
			NPC* roomTarget = new NPC(rooms[roomNum].getCenterX(), rooms[roomNum].getCenterY(), 0);
			setDestination(roomTarget->getX(), roomTarget->getY(), roomTarget);
			movesChased = 0;
		}
		if (isMoving && pTarget) {
			this->Move(maze, false);
			if (fabs(x - pTarget->getX()) < STOP_NEAR_ENEMY_RANGE && fabs(y - pTarget->getY()) < STOP_NEAR_ENEMY_RANGE)
				isMoving = false;
			else
				isMoving = true;

			if (fabs(x - pTarget->getX()) < FIGHTING_RANGE && fabs(y - pTarget->getY()) < FIGHTING_RANGE) {
				std::cout << "change to fight\n";
				pCurrentState->Transform(this);
			}
		}

		target = getTarget(rooms, enemy, this);
		if (target) {
			setDestination(target->getX(), target->getY(), target);
		}

		if (hp < MAX_HP_SOLDIER) {
			pCurrentState->Transform(this);
		}
	}

	if (fighting) {
		
		if (fabs(x - pTarget->getX()) > FIGHTING_RANGE && fabs(y - pTarget->getY()) > FIGHTING_RANGE) {
			std::cout << "stopped fighting\n";
			pCurrentState->Transform(this);
		}

		int numNpcSameRoom = 0;
		for (int i = 0; i < 3; i++) {
			int room = whichRoom(enemy->getNpcByIndex(i), rooms);
			if (myRoom == room && room > -1) {
				numNpcSameRoom++;
			}
		}
		double visibility_map[MSZ][MSZ] = { 0 };
		CreateVisibilityMap(this, maze, visibility_map);
		if (visibility_map[(int)pTarget->getY()][(int)pTarget->getX()] == 0) {
			isShooting = false;
		}
		if (isShooting) {
			if (numNpcSameRoom > 1)
				shootBullet();
			else
				shootBullet();
		}

		// check if target still alive
		target = getTarget(rooms, enemy, this);
		if (!target) {
			pCurrentState->Transform(this);
		}
	}
}
