#include "IdleSoldier.h"
#include "FillMyHpBar.h"
#include "Run.h"
#include "FightMode.h"
#include <iostream>

void IdleSoldier::Transform(NPC* pn)
{
	OnExit(pn);
	if (pn->getHp() < MAX_HP_SOLDIER) {
		pn->setInterruptedState(this);
		pn->setCurrentState(new FillMyHpBar());
		pn->getCurrentState()->OnEnter(pn);
	}
	else if(pn->getPTarget()) {
		if (fabs(pn->getX() - pn->getTargetX()) < FIGHTING_RANGE) {
			pn->setInterruptedState(this);
			pn->setCurrentState(new FightMode());
			pn->getCurrentState()->OnEnter(pn);
		}
	}
}

void IdleSoldier::OnEnter(NPC* pn)
{
	pn->setIsMoving(true);
	pn->setIdle(true);
}

void IdleSoldier::OnExit(NPC* pn)
{
	pn->setIsMoving(false);
	pn->setIdle(false);
}
