#pragma once
const int NUM_ROOMS = 6;
const int W = 1200;
const int H = 1200;
const int MSZ = 100; // maze size

const int WALL = 0;
const int SPACE = 1;
const int PASS = 2;
const int ARSENAL = 3;
const int PHARMACY = 4;
const int BEGIN_COUNT_TEAM_A = 5;
const int BEGIN_COUNT_TEAM_B = 8;

const int NUM_BULLETS_PER_MAGAZINE = 5;
const int NUM_BULLETS_PER_GRENADE = 32;

// for soldier
const double SPEED_SOLDIER = 0.01;
const int MAX_HP_SOLDIER = 500;
const int MAX_MAGAZINE_SOLDIER = 3;
const int MAX_GRENADES_SOLDIER = 3;
const int HP_UP_SOLDIER = 200;
const int GRENADE_THROW_RANGE = 5;
const int FIGHTING_RANGE = 5;
const int STOP_NEAR_ENEMY_RANGE = 2;

// for armour bearer
const double SPEED_AB = 0.02;
const int MAX_HP_AB = 300;
const int MAX_MAGAZINE_AB = 5;
const int MAX_GRENADES_AB = 3;
const int HP_POTIONS_AB = 3;

// teams
const int TEAM_RED = 1;
const int TEAM_BLUE = 2;
const int NUM_PLAYERS = 6;

// Pharmacy
const int MAX_STOCK_PHARMACY = 10;

// Arsenal
const int MAX_STOCK_MAGAZINES = 15;
const int MAX_STOCK_GRENADES = 15;

// Bullet
const double HIT_RATE = 100;
const double SPEED_BULLET = 0.1;
