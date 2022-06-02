#include "Soldier.h"

Soldier::Soldier()
{
}

Soldier::Soldier(double cx, double cy, int t)
{
	init();
	x = cx;
	y = cy;
	team = t;
}

void Soldier::init()
{
	hp = MAX_HP_SOLDIER;
	grenade_count = MAX_GRENADES_SOLDIER;
	for (int i = 0; i < MAX_MAGAZINE_SOLDIER; i++)
		magazines.push_back(new Magazine());
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

Bullet* Soldier::MoveBullets(int maze[MSZ][MSZ])
{
	if (isShooting && !currentGrenade) {
		Magazine* pm = *(magazines.begin());
		isShooting = pm->Move(maze);
		if (pm->getHit() != nullptr)
			return pm->getHit();
	}
	else if (currentGrenade) {
		if (currentGrenade->getHit() != nullptr)
			return currentGrenade->getHit();
		if (currentGrenade->Exploding(maze))
			currentGrenade = nullptr;
	}
}

void Soldier::showBullets()
{
	if (isShooting && !currentGrenade) {
		Magazine* pm = *(magazines.begin());
		pm->show();
	}
	else if (currentGrenade) {
		currentGrenade->show();
	}
}

void Soldier::shootBullet()
{
	if (!isShooting && !currentGrenade) {
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
		pm->fire(x, y, direction_angle, team);
	}
}

void Soldier::throwGrenade(int maze[MSZ][MSZ])
{
	if (currentGrenade == nullptr && !isShooting) {
		if (grenade_count == 0)
			return;
		int min = -GRENADE_THROW_RANGE;
		int rangeX, rangeY;
		do {
			rangeX = rand() % (GRENADE_THROW_RANGE - min) + min;
			rangeY = rand() % (GRENADE_THROW_RANGE - min) + min;
		} while (maze[(int)y + rangeY][(int)x + rangeX] == WALL);
		currentGrenade = new Grenade(x + rangeX, y + rangeY, team);
		currentGrenade->Explode();
		grenade_count--;
	}
}
