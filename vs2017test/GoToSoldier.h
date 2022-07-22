#pragma once
#include "State.h"
class GoToSoldier :
    public State
{
public:
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

