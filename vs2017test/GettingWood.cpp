#include "GettingWood.h"
#include "GoToWarehouse.h"
#include "GoHome.h"
#include "GettingWood.h"
#include "GoToForest.h"



GettingWood::GettingWood()
{
}


GettingWood::~GettingWood()
{
}

void GettingWood::Transform(NPC * pn)
{
	OnExit(pn);
	if (pn->getHP() <= 0.2*MAX_HP)
	{
		pn->setInterruptedState(new GoToForest());
		pn->setCurrentState(new GoHome());
	}
	else
		pn->setCurrentState(new GoToWarehouse());
	pn->getCurrentState()->OnEnter(pn);
}

void GettingWood::OnEnter(NPC * pn)
{
	pn->setIsGettingWood(true);
}

void GettingWood::OnExit(NPC * pn)
{
	pn->setIsGettingWood(false);
}
