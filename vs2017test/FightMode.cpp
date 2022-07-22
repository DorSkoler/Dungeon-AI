#include "FightMode.h"
#include "Run.h"

void FightMode::Transform(NPC* pn)
{
	OnExit(pn);
	if (pn->getHp() <= 0.2 * MAX_HP_SOLDIER) {
		pn->setInterruptedState(this);
		pn->setCurrentState(new Run());
		pn->getCurrentState()->OnEnter(pn);
	}
	else {
		
	}
}

void FightMode::OnEnter(NPC* pn)
{
	pn->setFighting(true);
	pn->setIsShooting(true);
}

void FightMode::OnExit(NPC* pn)
{
	pn->setFighting(false);
	pn->setIsShooting(false);
	pn->setDestination(-1, -1, nullptr);
}