#pragma once
#include "State.h"

class IdleAB :
    public State
{
public:
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

