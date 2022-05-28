#pragma once
#include "State.h"

class GoToArsenal :
    public State
{
private:
	int x, y;

public:
	GoToArsenal();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
	void setXandY(int cx, int cy) { x = cx; y = cy; };
};

