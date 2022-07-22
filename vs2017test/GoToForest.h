#pragma once
#include "State.h"

const double fx = 78;
const double fy = 78;

class GoToForest :
	public State
{
public:
	GoToForest();
	~GoToForest();
	void Transform(NPC* pn) ;
	void OnEnter(NPC* pn) ;
	void OnExit(NPC* pn) ;

};

