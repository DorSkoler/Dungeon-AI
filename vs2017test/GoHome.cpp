#include "GoHome.h"
#include "StayAtHome.h"



GoHome::GoHome()
{
}


GoHome::~GoHome()
{
}

void GoHome::Transform(NPC * pn)
{
	OnExit(pn);
	pn->setCurrentState(new StayAtHome());
	pn->getCurrentState()->OnEnter(pn);
}

void GoHome::OnEnter(NPC * pn)
{
	pn->setIsMoving(true);
	pn->setGoingHome(true);
	pn->setDestination(HX, HY);
}

void GoHome::OnExit(NPC * pn)
{
	pn->setIsMoving(false);
	pn->setGoingHome(false);

}
