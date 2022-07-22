#include "GoToForest.h"
#include "GettingWood.h"
#include "GoHome.h"



GoToForest::GoToForest()
{
}


GoToForest::~GoToForest()
{
}

// what will be the NEXT state after GoToForest
void GoToForest::Transform(NPC * pn)
{
	OnExit(pn); // from GoToForest
	if (pn->getHP() <= 0.2*MAX_HP)
	{
		pn->setInterruptedState(this);
		pn->setCurrentState(new GoHome());
	}
	else
		pn->setCurrentState(new GettingWood());
	pn->getCurrentState()->OnEnter(pn);
}

void GoToForest::OnEnter(NPC * pn)
{
	pn->setIsMoving(true);
	pn->setDestination(fx, fy);
}

void GoToForest::OnExit(NPC * pn)
{
	pn->setIsMoving(false);

}
