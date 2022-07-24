#include "IdleAB.h"
#include "ArmourBearer.h"
#include "Soldier.h"
#include "GoToSoldier.h"

void IdleAB::Transform(NPC* pn)
{
	if (pn->getSoldier1()) {
		if (pn->getSoldier1()->getHp() < 0.5 * MAX_HP_SOLDIER) {
			pn->setInterruptedState(this);
			pn->setCurrentState(new GoToSoldier());
			pn->getCurrentState()->OnEnter(pn);
		}
	}
	else if (pn->getSoldier2()) {
		if (pn->getSoldier2()->getHp() < 0.5 * MAX_HP_SOLDIER) {
			pn->setInterruptedState(this);
			pn->setCurrentState(new GoToSoldier());
			pn->getCurrentState()->OnEnter(pn);
		}
	}

}

void IdleAB::OnEnter(NPC* pn)
{
	pn->setIsMoving(true);
	pn->setIdle(true);
}

void IdleAB::OnExit(NPC* pn)
{
	pn->setIdle(false);
}