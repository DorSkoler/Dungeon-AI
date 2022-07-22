#include "Functions.h"
#include "Team.h"
#include "Cell.h"
#include <queue>
#include <thread>

double getDirectionAngle(NPC* source, NPC* target) {
	double distance;
	double targetX = target->getX();
	double targetY = target->getY();
	double x = source->getX();
	double y = source->getY();
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	// [dx,dy] must be vector of length 1 to the direction to target
	double dx = (targetX - x) / distance;
	return acos(dx);
}

double getDistance(NPC* source, NPC* target) {
	double distance;
	double targetX = target->getX();
	double targetY = target->getY();
	double x = source->getX();
	double y = source->getY();
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	return distance;
}

void getMyTarget(NPC* pn, NPC* pTarget)
{
	pn->setDestination(pTarget->getX(), pTarget->getY(), pTarget);
	pn->setDirectionAngle(getDirectionAngle(pn, pTarget));
}

int whichRoom(NPC* pn, Room rooms[NUM_ROOMS]) {
	for (int i = 0; i < NUM_ROOMS; i++) {
		if (pn->getX() <= (rooms[i].getCenterX() + rooms[i].getWidth() / 2) && pn->getX() >= (rooms[i].getCenterX() - rooms[i].getWidth() / 2)) {
			if (pn->getY() <= (rooms[i].getCenterY() + rooms[i].getHeight() / 2) && pn->getY() >= (rooms[i].getCenterY() - rooms[i].getHeight() / 2)) {
				return i;
			}
		}
	}
	return -1;
}

NPC* getTarget(Room rooms[NUM_ROOMS], Team* enemy, NPC* me) {
	double targetToChase = MAXINT;
	int myRoom = whichRoom(me, rooms);
	NPC* target = nullptr;

	for (int i = 0; i < 3; i++) {
		int room = whichRoom(enemy->getNpcByIndex(i), rooms);
		if (myRoom == room && room > -1) {
			double current = getDistance(me, enemy->getNpcByIndex(i));
			if (targetToChase > current) {
				targetToChase = current;
				target = enemy->getNpcByIndex(i);
			}
		}
	}
	return target;
}

void CreateSecurityMap(Room* room, double security_map[MSZ][MSZ], int maze[MSZ][MSZ])
{
	int num_simulations = 500;
	double damage = 0.001;
	int i;
	Grenade* g;

	for (i = 0; i < num_simulations; i++)
	{
		g = new Grenade(rand() % MSZ, rand() % MSZ, 0, 0, 0);
		g->SimulateExplosion(maze, security_map, damage);
	}
}

void CreateVisibilityMap(NPC* pn, int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ])
{
	int num_simulations = 500;
	int i;
	std::vector<Bullet*> bullets;
	double teta = 2 * 3.14 / num_simulations;

	for (int i = 0; i < num_simulations; i++) {
		bullets.push_back(new Bullet(pn->getX(), pn->getY(), i * teta, 0, 0, 0));
		bullets.at(i)->SimulateVisibility(maze, visibility_map);
	}
}