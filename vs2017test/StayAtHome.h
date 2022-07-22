#pragma once
#include "State.h"
class StayAtHome :
	public State
{
public:
	StayAtHome();
	~StayAtHome();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

