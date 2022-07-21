#include "Functions.h"

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
	pn->setDestination(pTarget->getX(), pTarget->getY());
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

