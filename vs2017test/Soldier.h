#pragma once
#include "glut.h"
#include <math.h>
#include <string>
#include "Team.h"
#include "Functions.h"



class Soldier : 
    public NPC
{
private:
    
    Grenade *currentGrenade = nullptr;
public:
    Soldier();
    Soldier(double cx, double cy, int t);
    void init();
    void DrawMe(const char* string);
    bool getIsShooting() { return isShooting; };
    void DrawMyHp();
    

    Bullet* MoveBullets(int maze[MSZ][MSZ], int hits[NUM_PLAYERS]);
    void showBullets();
    void shootBullet();
    void throwGrenade(int maze[MSZ][MSZ]);
    void doSomething(Team* enemy, int maze[MSZ][MSZ], Room rooms[NUM_ROOMS]);
};

