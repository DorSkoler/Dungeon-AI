#pragma once
#include "Definitions.h"
#include "NPC.h"
#include "Room.h"

class Team;

double getDirectionAngle(NPC* source, NPC* target);
void getMyTarget(NPC* pn, NPC* pTarget);
int whichRoom(NPC* pn, Room rooms[NUM_ROOMS]);
double getDistance(NPC* source, NPC* target);
NPC* getTarget(Room rooms[NUM_ROOMS], Team* enemy, NPC* me);
void CreateSecurityMap(double security_map[MSZ][MSZ], int maze[MSZ][MSZ]);
void CreateVisibilityMap(NPC* pn, int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ]);
Cell* findRoute(NPC* pn, int maze[MSZ][MSZ], bool use_security);
void RestorePath(Cell* ps, int maze[MSZ][MSZ]);