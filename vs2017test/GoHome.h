#pragma once
#include "State.h"

const int HX = 20;
const int HY = 70;

class GoHome :
	public State
{
public:
	GoHome();
	~GoHome();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

