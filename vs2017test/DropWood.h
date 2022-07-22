#pragma once
#include "State.h"
class DropWood :
	public State
{
public:
	DropWood();
	~DropWood();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

