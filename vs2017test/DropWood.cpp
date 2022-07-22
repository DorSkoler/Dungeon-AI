#include "DropWood.h"
#include "GoToForest.h"
#include "GoHome.h"
#include "GoToWarehouse.h"


DropWood::DropWood()
{
}


DropWood::~DropWood()
{
}

void DropWood::Transform(NPC * pn)
{
	OnExit(pn);
	if (pn->getHP() <= 0.2*MAX_HP)
	{
		pn->setInterruptedState(new GoToWarehouse());
		pn->setCurrentState(new GoHome());
	}
	else
		pn->setCurrentState(new GoToForest());

	pn->getCurrentState()->OnEnter(pn);
}

void DropWood::OnEnter(NPC * pn)
{
	pn->setIsGettingWood(false);
}

void DropWood::OnExit(NPC * pn)
{
}
