#pragma once
#include "Soldier.h"
#include "Definitions.h"
#include "Room.h"
#include "ArmourBearer.h"

class Team
{
private:
	Soldier *s1;
	Soldier *s2;
	ArmourBearer *ab;
	int team_num;
public:
	Team(int t, Room* r, int maze[MSZ][MSZ]);
	void drawTeam();
};

