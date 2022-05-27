#include "Room.h"
#include <string>

Room::Room()
{
}

Room::Room(int num)
{
	room_num = num;
}


Room::~Room()
{
}

void Room::AddMeToMaze(int maze[MSZ][MSZ])
{
	int i, j;

	for (i = centerY - height / 2; i <= centerY + height / 2; i++)
		for (j = centerX - width / 2; j <= centerX + width / 2; j++)
			maze[i][j] = SPACE;
}

void Room::DrawMe()
{
	// room text
	glColor3d(0, 0, 0);
	char c[10];
	std::string tmp = std::to_string(room_num);
	char const* num_char = tmp.c_str();
	char string[] = "room";

	int w;
	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)string);
	glRasterPos2f(centerX - 1, centerY + height / 2 + 2);
	for (int i = 0; i < 4; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}

	w = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)num_char);
	glRasterPos2f(centerX + 2, centerY + height / 2 + 2);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num_char[0]);
}
