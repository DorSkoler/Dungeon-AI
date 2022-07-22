#pragma once
#include "State.h"
class GettingWood :
	public State
{
public:
	GettingWood();
	~GettingWood();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

