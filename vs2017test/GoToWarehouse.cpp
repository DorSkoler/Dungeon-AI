#include "GoToWarehouse.h"
#include "DropWood.h"
#include "GoHome.h"



GoToWarehouse::GoToWarehouse()
{
}


GoToWarehouse::~GoToWarehouse()
{
}

void GoToWarehouse::Transform(NPC * pn)
{
	OnExit(pn);
	if (pn->getHP() <= 0.2*MAX_HP)
	{
		pn->setInterruptedState(this);
		pn->setCurrentState(new GoHome());
	}
	else
		pn->setCurrentState(new DropWood());
	pn->getCurrentState()->OnEnter(pn);
}

void GoToWarehouse::OnEnter(NPC * pn)
{
	pn->setIsMoving(true);
	pn->setDestination(WX, WY);

}

void GoToWarehouse::OnExit(NPC * pn)
{
	pn->setIsMoving(false);


}
