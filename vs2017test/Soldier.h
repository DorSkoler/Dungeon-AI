#pragma once
#include "NPC.h"
#include "Definitions.h"
#include "Bullet.h"
#include "Magazine.h"



class Soldier :
    public NPC
{
private:


public:
    
    Soldier(double x, double y, int t);
    void init();
    void DrawMe();

};

