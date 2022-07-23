#include "FightMode.h"
#include "Run.h"
#include "IdleSoldier.h"

void FightMode::Transform(NPC* pn)
{
	NPC* target = pn->getPTarget();
	OnExit(pn);
	if (pn->getHp() <= 0.2 * MAX_HP_SOLDIER) {
		pn->setInterruptedState(this);
		pn->setCurrentState(new Run());
		pn->getCurrentState()->OnEnter(pn);
	}
	else {
		if (!target) {
			pn->setInterruptedState(this);
			pn->setCurrentState(new IdleSoldier());
			pn->getCurrentState()->OnEnter(pn);
		}
		else if (fabs(pn->getX() - target->getX()) > FIGHTING_RANGE && fabs(pn->getY() - target->getY()) > FIGHTING_RANGE) {
			pn->setInterruptedState(this);
			pn->setCurrentState(new IdleSoldier());
			pn->getCurrentState()->OnEnter(pn);
		}
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
	pn->setPTarget(nullptr);
}