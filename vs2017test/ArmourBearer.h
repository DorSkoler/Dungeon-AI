#pragma once
#include "NPC.h"

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
    void doSomething(int maze[MSZ][MSZ]);

    bool getSupplies(int g, int m);
};

