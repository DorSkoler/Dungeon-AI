#pragma once
#include "Definitions.h"
#include "glut.h"
#include <iostream>

class Room
{
private:
	int centerX, centerY;
	int width, height;
	int room_num = -1;
public:
	Room();
	Room(int num);
	~Room();

	void AddMeToMaze(int maze[MSZ][MSZ]);
	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }
	void setCenterX(int x) { centerX = x; }
	void setCenterY(int y) { centerY = y; }

	int getWidth() { return width; }
	int getHeight() { return height; }
	int getCenterX() { return centerX; }
	int getCenterY() { return centerY; }
	int getNumRoom() { return room_num; }

	void DrawMe();
};

