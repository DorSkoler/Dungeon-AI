#include "IdleSoldier.h"
#include "FillMyHpBar.h"
#include "Run.h"
#include "FightMode.h"

void IdleSoldier::Transform(NPC* pn)
{
	OnExit(pn);
	if (pn->getHp() < MAX_HP_SOLDIER) {
		pn->setInterruptedState(this);
		pn->setCurrentState(new FillMyHpBar());
	}
	else if(pn->getTargetX() > -1) {
		pn->setInterruptedState(this);
		pn->setCurrentState(new FightMode());
		if (fabs(pn->getX() - pn->getTargetX()) < STOP_NEAR_ENEMY_RANGE)
			pn->setIsMoving(false);
		if (fabs(pn->getX() - pn->getTargetX()) < FIRE_RANGE)
			pn->setIsShooting(true);
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
