#include "FightMode.h"
#include "Run.h"

void FightMode::Transform(NPC* pn)
{
	OnExit(pn);
	if (pn->getHp() <= 0.2 * MAX_HP_SOLDIER) {
		pn->setInterruptedState(this);
		pn->setCurrentState(new Run());
	}
	else {
		if (fabs(pn->getX() - pn->getTargetX()) < FIRE_RANGE)
			pn->setIsShooting(true);
		else
			pn->setIsShooting(false);
	}
}

void FightMode::OnEnter(NPC* pn)
{
	pn->setFighting(true);
}

void FightMode::OnExit(NPC* pn)
{
	pn->setFighting(false);
	pn->setDestination(-1, -1);
}