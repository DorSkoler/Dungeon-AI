#include "StayAtHome.h"



StayAtHome::StayAtHome()
{
}


StayAtHome::~StayAtHome()
{
}

void StayAtHome::Transform(NPC * pn)
{
	OnExit(pn);
	pn->setCurrentState(pn->getInterruptedState());
	pn->getCurrentState()->OnEnter(pn);
}

void StayAtHome::OnEnter(NPC * pn)
{
	pn->setAtHome(true);
}

void StayAtHome::OnExit(NPC * pn)
{
	pn->setAtHome(false);


}
