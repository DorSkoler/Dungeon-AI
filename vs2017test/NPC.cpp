#include "NPC.h"
#include "glut.h"
#include "GoToForest.h"
#include <math.h>



NPC::NPC(double x, double y)
{
	this->x = x;
	this->y = y;
//	isMoving = true;
//	dx = 0.5;
//	dy = 0.5;
//	isGettingWood = false;
	numWood = 0;
	hp = MAX_HP;
	atHome = false;
	goingHome = false;
	pCurrentState = new GoToForest();
	pCurrentState->OnEnter(this);
}

NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::DoSomeThing()
{
	if (atHome)
	{
		hp += 0.5;
		// check if the NPC should do something else
		if (hp >= MAX_HP)
			pCurrentState->Transform(this);
	}
	else // not at home
	{
		hp -= 0.1;
		// check if the NPC should do something else
		if (hp <= MAX_HP*0.2 && !goingHome) // 20% of full HP
			pCurrentState->Transform(this);

	}

	if (isMoving)
	{
		x += dx * SPEED;
		y += dy * SPEED;
		// check if the NPC should do something else
		if (fabs(x - targetX) < 1 && fabs(y - targetY) < 1)
			pCurrentState->Transform(this);
	}
	else if(!atHome)// not moving
	{
		if (isGettingWood)
		{
			numWood++;
			// check if the NPC should do something else
			if(numWood>=MAX_WOOD)
				pCurrentState->Transform(this);
		}
		else
		{
			numWood--;
			// check if the NPC should do something else
			if (numWood <= MIN_WOOD)
				pCurrentState->Transform(this);
		}
	}
}

void NPC::setDestination(double destX, double destY)
{
	double distance;
	targetX = destX; 
	targetY = destY; 
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	// [dx,dy] must be vector of length 1 to the direction to target
	dx = (targetX - x) / distance;
	dy = (targetY - y) / distance;

}

void NPC::DrawMe()
{
	// body
	glColor3d(1, 0.8, 0.6);
	glBegin(GL_POLYGON);
	glVertex2d(x - 1, y);
	glVertex2d(x , y+2);
	glVertex2d(x + 1, y);
	glVertex2d(x , y-2);
	glEnd();
	// frame
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 1, y);
	glVertex2d(x, y + 2);
	glVertex2d(x + 1, y);
	glVertex2d(x, y - 2);
	glEnd();
	// cart
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(x - 3, y);
	glVertex2d(x - 3, y-2);
	glVertex2d(x - 1, y - 2);
	glVertex2d(x - 1, y );
	glEnd();
	// draw woods
	for (int i = 0; i < numWood / 100; i++)
	{
		glColor3d(0.6, 0.4, 0);
		glBegin(GL_LINES);
		glVertex2d(x - 3, y - 2 + (i)*0.2);
		glVertex2d(x - 1, y - 2 + (i)*0.2);
		glEnd();
	}
	// hp
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(x - 1, y + 2.5);
	glVertex2d(x - 1 + 2*hp/MAX_HP, y + 2.5);
	glEnd();

}
