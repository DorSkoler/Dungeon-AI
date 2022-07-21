#pragma once
#include "Definitions.h"
#include "NPC.h"
#include "Room.h"

double getDirectionAngle(NPC* source, NPC* target);
void getMyTarget(NPC* pn, NPC* pTarget);
int whichRoom(NPC* pn, Room rooms[NUM_ROOMS]);
double getDistance(NPC* source, NPC* target);

