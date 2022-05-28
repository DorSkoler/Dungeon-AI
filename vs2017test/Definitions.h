#pragma once
const int NUM_ROOMS = 6;
const int W = 1200;
const int H = 1200;
const int MSZ = 100; // maze size

const int WALL = 0;
const int SPACE = 1;
const int PASS = 2;
const int ARMOURBEARER = 3;
const int SOLDIER = 4;
const int ARSENAL = 5;
const int PHARMACY = 6;

const int NUM_BULLETS_PER_MAGAZINE = 5;
const int NUM_BULLETS_PER_GRENADE = 32;

// for soldier
const double SPEED_SOLDIER = 0.2;
const double MAX_HP_SOLDIER = 500;
const int MAX_MAGAZINE_SOLDIER = 3;
const int MAX_GRENADES_SOLDIER = 2;
const int HP_UP_SOLDIER = 200;
const int GRENADE_THROW_RANGE = 5;

// for armour bearer
const double SPEED_AB = 0.1;
const double MAX_HP_AB = 300;
const int MAX_MAGAZINE_AB = 5;
const int MAX_GRENADES_AB = 3;
const int HP_POTIONS_AB = 3;

// teams
const int TEAM_RED = 1;
const int TEAM_BLUE = 2;

// Pharmacy
const int MAX_STOCK_PHARMACY = 10;

// Arsenal
const int MAX_STOCK_MAGAZINES = 15;
const int MAX_STOCK_GRENADES = 15;
