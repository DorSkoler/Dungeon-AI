#include "FightMode.h"
#include "Run.h"
#include "FillMyHpBar.h"
#include "IdleSoldier.h"
#include <iostream>

void FightMode::Transform(NPC* pn)
{
	//NPC* target = pn->getPTarget();
	OnExit(pn);
	if (pn->getHp() <= 0.2 * MAX_HP_SOLDIER) {
		pn->setInterruptedState(this);
		pn->setCurrentState(new IdleSoldier());
		pn->getCurrentState()->OnEnter(pn);
	}
	else {
		pn->setInterruptedState(this);
		pn->setCurrentState(new IdleSoldier());
		pn->getCurrentState()->OnEnter(pn);
	}
}

void FightMode::OnEnter(NPC* pn)
{
	std::cout << "enter fight mode\n";
	pn->setFighting(true);
	pn->setIsShooting(true);
}

void FightMode::OnExit(NPC* pn)
{
	std::cout << "exit fight mode\n";
	pn->setFighting(false);
	pn->setIsShooting(false);
	pn->setPTarget(nullptr);
	pn->setCurrentGrenade(nullptr);
	//pn->setCurrentBullet();
}