#pragma once
#include "NPC.h"
#include "Definitions.h"
#include "Bullet.h"
#include "Magazine.h"

class ArmourBearer :
    public NPC
{
private:
    
public:
    ArmourBearer(double x, double y, int t);
    ~ArmourBearer();

    void init();
    void DrawMe();

};

