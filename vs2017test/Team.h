#pragma once
#include "Soldier.h"
#include "ArmourBearer.h"
#include "Room.h"
#include "Definitions.h"

class Team
{
private:
	Soldier s1;
	Soldier s2;
	ArmourBearer ab;
	int team_num;

public:
	Team(int t, Room* r, int maze[MSZ][MSZ]);
	Team(int t);
	

};

