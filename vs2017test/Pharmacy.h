#pragma once
#include "Definitions.h"

class Pharmacy
{
private:
	double x, y;
	int stock = MAX_STOCK_PHARMACY;
public:
	Pharmacy(double cx, double cy);
	int getStock() { return stock; };
	int updateStock(int s);
	void DrawMe();
};

