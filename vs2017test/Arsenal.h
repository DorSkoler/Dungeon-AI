#pragma once
#include "Definitions.h"

class Arsenal
{
private:
	double x, y;
	int magazine_stock = MAX_STOCK_MAGAZINES;
	int grenade_stock = MAX_STOCK_GRENADES;
public:
	Arsenal(double cx, double cy);
	int getMagStock() { return magazine_stock; };
	int getNadeStock() { return grenade_stock; };
	void updateStock(int m, int g) { magazine_stock -= m; grenade_stock -= g; };
	void DrawMe();
};

