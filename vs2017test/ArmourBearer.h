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
    ArmourBearer();
    ArmourBearer(double cx, double cy, int t);
    ~ArmourBearer();

    void init();
    void DrawMe();
    void DrawMyHp();

    bool Move(int maze[MSZ][MSZ]);
    bool getSupplies(int g, int m);
};

