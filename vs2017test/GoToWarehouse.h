#pragma once
#include "State.h"

const int WX = 20;
const int WY = 10;

class GoToWarehouse :
	public State
{
public:
	GoToWarehouse();
	~GoToWarehouse();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

