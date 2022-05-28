#pragma once
#include "NPC.h"
#include "glut.h"
#include <math.h>
#include <string>



class Soldier : 
    public NPC
{
private:
    bool isShooting = false;
    Grenade *currentGrenade = nullptr;
public:
    Soldier();
    Soldier(double cx, double cy, int t);
    void init();
    void DrawMe(const char* string);
    bool getIsShooting() { return isShooting; };
    void DrawMyHp();

    bool Move(int maze[MSZ][MSZ]);
    Bullet* MoveBullets(int maze[MSZ][MSZ]);
    void showBullets();
    void shootBullet();
    void throwGrenade(int maze[MSZ][MSZ]);
    //void relodeMagazine();
};

