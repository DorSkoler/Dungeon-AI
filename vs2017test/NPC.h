#pragma once
#include "State.h"

const double SPEED = 0.1;
const double MAX_WOOD = 1000;
const double MIN_WOOD = 0;
const double MAX_HP = 500;

class State;
class NPC
{
private:
	double x, y;
	double targetX, targetY;
	double dx, dy; // vector to the target
	double numWood;
	double hp;
	bool isMoving, isGettingWood, atHome, goingHome;
	State* pCurrentState;
	State* pInterruptedState;
public:
	NPC(double x, double y);
	NPC();
	~NPC();
	void DoSomeThing(); // kind of MAIN function
	void setIsMoving(bool value) { isMoving = value; }
	void setDestination(double destX, double destY);
	void setIsGettingWood(bool value) { isGettingWood = value; }
	void setCurrentState(State* ps) { pCurrentState = ps; }
	State* getCurrentState() { return pCurrentState; }
	double getHP() { return hp; }
	void setAtHome(bool value) { atHome = value; }
	void setGoingHome(bool value) { goingHome = value; }
	void setInterruptedState(State* ps) { pInterruptedState = ps; }
	State* getInterruptedState() { return pInterruptedState; }

	void DrawMe();
};

