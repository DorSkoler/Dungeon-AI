#pragma once
#include "State.h"
class GoToArsenal :
    public State
{
public:
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

