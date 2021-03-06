#include "glut.h"
#include <time.h>
#include <vector>
#include <queue>
#include <iostream>
#include "Cell.h"
#include "CompareCells.h"
#include "Bullet.h"
#include "Grenade.h"
#include "ArmourBearer.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include "Soldier.h"
#include "Pharmacy.h"
#include "Arsenal.h"
#include "Team.h"
#include "Functions.h"

using namespace std;

int windowInfo;
int windowMain;

int maze[MSZ][MSZ] = { 0 };
int hits[NUM_PLAYERS] = { 0 };
double security_map[MSZ][MSZ] = { 0 };
double visibility_map[MSZ][MSZ] = { 0 };

Room rooms[NUM_ROOMS];
bool underConstruction = true;
bool gameOver = false;
int r1=0, r2=1; // rooms indices

Team* teamA = nullptr;
Team* teamB = nullptr;
vector <Arsenal*> arsenals;
vector <Pharmacy*> pharmacies;

vector<Bullet*> hittingBulletsTeamA;
vector<Bullet*> hittingBulletsTeamB;

void SetupRooms();
void DigPassages();
void AddObstacles();
void SetUpTeams();
void SetUpSupplies();

void init()
{	//          Red Green Blue 
	glClearColor(0, 0, 0.4, 0);// color of window background
	
	// set the main axes
	glOrtho(0, MSZ, 0, MSZ ,- 1, 1); 

	srand(time(0));

	SetupRooms();

	AddObstacles();

	SetUpSupplies();

	SetUpTeams();
}

void findXandY(int* x, int* y, int r)
{
	int minX = rooms[r].getCenterX() - rooms[r].getWidth() / 2;
	int maxX = rooms[r].getWidth() / 2 + rooms[r].getCenterX();
	int minY = rooms[r].getCenterY() - rooms[r].getHeight() / 2;
	int maxY = rooms[r].getHeight() / 2 + rooms[r].getCenterY();
	do {
		*x = rand() % (maxX - minX) + minX;
		*y = rand() % (maxY - minY) + minY;
	} while (maze[*y][*x] != SPACE);
}

void SetUpSupplies() {
	for (int i = 0; i < 4; i++)
	{
		int r = rand() % NUM_ROOMS;
		int x, y;
		findXandY(&x, &y, r);
		if (i < 2) {
			maze[y][x] = ARSENAL;
			arsenals.push_back(new Arsenal(x, y));
		}
		else {
			maze[y][x] = PHARMACY;
			pharmacies.push_back(new Pharmacy(x, y));
		}
	}

}

void SetUpTeams() {
	int room_teamA = rand() % NUM_ROOMS;
	cout << "room number " << room_teamA << " for team red\n"; 
	teamA = new Team(TEAM_RED, &rooms[room_teamA], maze, BEGIN_COUNT_TEAM_A);
	teamA->setTeamInfo(20, 90);
	int room_teamB;
	do {
		room_teamB = rand() % NUM_ROOMS;
	} while (room_teamA == room_teamB);
	cout << "room number " << room_teamB << " for team blue\n";
	teamB = new Team(TEAM_BLUE, &rooms[room_teamB], maze, BEGIN_COUNT_TEAM_B);
	teamB->setTeamInfo(20, 40);
}

void AddObstacles()
{
	int num_obstacles = 100;
	for (int i = 0; i < num_obstacles; i++)
		maze[rand() % MSZ][rand() % MSZ] = WALL;
}

// checks for overlapping with rooms of lower indices
bool HasOverlap(int w, int h, int x, int y, int index)
{
	bool overlaps = false;
	int i;
	int dx, dy,gap=4;

	for (i = 0; i < index && !overlaps; i++)
	{
		dx = abs(rooms[i].getCenterX() - x);
		dy = abs(rooms[i].getCenterY() - y);
		if (dx < w / 2 + rooms[i].getWidth() / 2 + gap && dy < h / 2 + rooms[i].getHeight() / 2 + gap)
			overlaps = true;
	}
	return overlaps;
}

void SetupRooms()
{
	int w, h, x, y;
	for (int r = 0; r < NUM_ROOMS; r++)
	{
		do
		{
			w = 15 + rand() % 35;
			h = 15 + rand() % 35;
			x = 2 + w / 2 + rand() % (MSZ - 4 - w);
			y = 2 + h / 2 + rand() % (MSZ - 4 - h);
		} while (HasOverlap(w,h,x,y,r));
		rooms[r] = *new Room(r);
		rooms[r].setWidth(w);
		rooms[r].setHeight(h);
		rooms[r].setCenterX(x);
		rooms[r].setCenterY(y);

		rooms[r].AddMeToMaze(maze);
	}
}

// if the neighbor cell is white  (including target as wll) then add it to pq and paint it gray
// if it is black then do nothing
// if it is gray (it can be target as wll) check 2 cases:
//         1: if F of the new found neghbor isn't better (>=) then of the previously found cell then do notheing
//         2: if  F of the new found neghbor IS better (<) then we have to update the cell parameters!!!

void CheckNeighbor(int row, int col, Cell* pcurrent, priority_queue <Cell, vector<Cell>, CompareCells>&pq,
	vector <Cell> &grays, vector <Cell>&blacks)
{
	double cost,cheap = 0.1, expensive = 0.4;
	vector <Cell>::iterator itrb;
	vector <Cell>::iterator itrg;


	if (maze[row][col] == SPACE || maze[row][col] == PASS) cost = cheap;
	else cost = expensive;

	// create neighbor cell
	Cell* pn = new Cell(row, col, pcurrent, pcurrent->getG() + cost, pcurrent->getTargetRow(), pcurrent->getTargetCol());
	// check color of theis cell
	itrb = find(blacks.begin(), blacks.end(), *pn);
	itrg = find(grays.begin(), grays.end(), *pn);

	// if it is white
	if (itrb == blacks.end() && itrg == grays.end())
	{
		pq.push(*pn);
		grays.push_back(*pn);
	}
	else  // it must be either gray or black 
		if (itrg != grays.end())
	{
		if (pn->getF() < itrg->getF()) // we have to update it
		{
			grays.erase(itrg);
			grays.push_back(*pn);
			// to update (find) pn in pq we need manually to extract all the cells that stand bfore pn in pq including pn
			// to update it and then to push all of them back to pq
			vector <Cell> tmp;
			while(!pq.empty() && !((*pn)== pq.top()))
			{
				tmp.push_back(pq.top());
				pq.pop();
			}
			if (pq.empty())
				cout << " neighbor wasn't found in pq \n";
			else // *pn is now at top of pq
			{
				pq.pop();
				pq.push(*pn);
				// move back to pq all the cells from tmp
				while (!tmp.empty())
				{
					pq.push(tmp.back());
					tmp.pop_back();
				}
			}
		}
	}

}

void RestorePath(Cell* ps)
{
	while (ps->getParent() != nullptr)
	{
		if (maze[ps->getRow()][ps->getCol()] == WALL)
			maze[ps->getRow()][ps->getCol()] = PASS;
		ps = ps->getParent();
	}
}

// creates path from rooms[index1] to rooms[index2] using A*
void DigPath(int index1, int index2)
{
	Cell* startingCell = new Cell(rooms[index1].getCenterY(), rooms[index1].getCenterX(),
		nullptr, 0, rooms[index2].getCenterY(), rooms[index2].getCenterX());

	Cell* pcurrent = nullptr;
	int currentRow, currentCol;

	priority_queue <Cell, vector<Cell>, CompareCells> pq;
	vector <Cell> grays;
	vector <Cell> blacks;

	vector <Cell>::iterator itr;


	// add Start Cell to pq and paint it gray
	pq.push(*startingCell);
	grays.push_back(*startingCell);

	// start A* . In our case pq shouldn't be empty because we should find the target before all the 
	// cells are over
	while (!pq.empty())
	{
		// pq is not empty so pick the top Cell
		pcurrent = new Cell(pq.top());
		// check if current is target
		if (pcurrent->getRow() == rooms[index2].getCenterY() && pcurrent->getCol() == rooms[index2].getCenterX())
		{
			RestorePath(pcurrent);
			cout << "The path from room " << index1 << " to room " << index2 << " has been found\n";
			return;
		}
		// remove current from pq and paint it black (remove it from grays)
		pq.pop();
		blacks.push_back(*pcurrent);
		// remove it from grays
		itr = find(grays.begin(), grays.end(), *pcurrent); // Cell must have operator ==
		if (itr == grays.end()) // current cell wasn't found: ERROR
		{
			cout << "Error: current wasn't found in grays for room " << index1 << " to room " << index2 << endl;
			return;
		}
		grays.erase(itr);

		// now check the neighbor cells
		currentRow = pcurrent->getRow();
		currentCol = pcurrent->getCol();
		if (currentRow > 0) // UP
			CheckNeighbor(currentRow - 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentRow < MSZ-1) // DOWN
			CheckNeighbor(currentRow + 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentCol > 0) // LEFT
			CheckNeighbor(currentRow , currentCol-1, pcurrent, pq, grays, blacks);
		if (currentCol < MSZ-1) // RIGHT
			CheckNeighbor(currentRow , currentCol+1, pcurrent, pq, grays, blacks);
	} // while
	// We shouldn't reach this point normally
	cout << "Error: PQ is empty for room " << index1 << " to room " << index2 << endl;
}

void DigPassages()
{
	int i, j;

	for (i = 0; i < NUM_ROOMS; i++)
		for (j = i + 1; j < NUM_ROOMS; j++)
			DigPath(i, j);
}

void CreateVisibilityMap(NPC* pn)
{
	int num_simulations = 500;
	int i;
	vector<Bullet*> bullets;
	double teta = 2 * 3.14 / num_simulations;

	for (int i = 0; i < num_simulations; i++)
		bullets.push_back(new Bullet(pn->getX(), pn->getY(), i * teta, 0, 0, 0));
}

void CreateSecurityMap()
{
	int num_simulations = 500;
	double damage = 0.001;
	int i;
	Grenade* g;

	for (i = 0; i < num_simulations; i++)
	{
		g = new Grenade(rand() % MSZ, rand() % MSZ, 0, 0, 0);
		g->SimulateExplosion(maze, security_map, damage);
	}

}

void resetVisual() {
	for (int i = 0; i < MSZ; i++)
		for (int j = 0; j < MSZ; j++)
			security_map[j][i] = 0;
}


void ShowMaze() 
{
	int i, j;

	for(i=0;i<MSZ;i++)
		for (j = 0; j < MSZ; j++)
		{
			// set color for cell (i,j)
			switch (maze[i][j]) 
			{
			case WALL:
				glColor3d(0.5, 0.55, 0.5); // grey
				break;
			case BEGIN_COUNT_TEAM_A:
			case BEGIN_COUNT_TEAM_A+1:
			case BEGIN_COUNT_TEAM_A+2:
				glColor3d(1, 0, 0);
				break;
			case BEGIN_COUNT_TEAM_B:
			case BEGIN_COUNT_TEAM_B+1:
			case BEGIN_COUNT_TEAM_B+2:
				glColor3d(0, 0, 1);
				break;
			case PASS:
				glColor3d(0.5, 0.7, 0.5);
				break;
			case SPACE:
				double d = security_map[i][j];
				double v = visibility_map[i][j];
				glColor3d(1-d-0.5*v, 1-d, 1-d-0.5*v); // white - security map value - visibility map value
				break;
			}// switch
			// now show the cell as plygon (square)
			glBegin(GL_POLYGON);
			glVertex2d(j, i); // left-bottom corner
			glVertex2d(j, i+1); // left-top corner
			glVertex2d(j+1, i+1); // right-top corner
			glVertex2d(j+1, i); // right-bottom corner
			glEnd();
		}// for
}


void ShowStartAndTarget()
{
	int i, j;
	// start
	i = rooms[r1].getCenterY();
	j = rooms[r1].getCenterX();
	glColor3d(0, 0, 1); // blue
	glBegin(GL_POLYGON);
	glVertex2d(j, i); // left-bottom corner
	glVertex2d(j, i + 1); // left-top corner
	glVertex2d(j + 1, i + 1); // right-top corner
	glVertex2d(j + 1, i); // right-bottom corner
	glEnd();

	// target
	i = rooms[r2].getCenterY();
	j = rooms[r2].getCenterX();
	glColor3d(1, 0.7, 0); // orange
	glBegin(GL_POLYGON);
	glVertex2d(j, i); // left-bottom corner
	glVertex2d(j, i + 1); // left-top corner
	glVertex2d(j + 1, i + 1); // right-top corner
	glVertex2d(j + 1, i); // right-bottom corner
	glEnd();

}

void infoWindow()
{
	teamA->drawInfo();
	teamB->drawInfo();
}

void displayInfo()
{
	glClear(GL_COLOR_BUFFER_BIT);
	infoWindow();
	glutSwapBuffers();
}

void idleInfo()
{
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	
	ShowMaze();
	if (underConstruction)
		ShowStartAndTarget();

	for (int i = 0; i < arsenals.size(); i++)
		arsenals.at(i)->DrawMe();
	for (int i = 0; i < pharmacies.size(); i++)
		pharmacies.at(i)->DrawMe();

	teamA->checkShowBullets();
	teamB->checkShowBullets();

	if (teamA != nullptr)
		teamA->drawTeam();
	if (teamB != nullptr)
		teamB->drawTeam();

	for (int i = 0; i < NUM_ROOMS; i++)
	{
		if (rooms[i].getNumRoom() > -1)
			rooms[i].DrawMe();
	}

	glutSwapBuffers();
}

void idle()
{
	if (!gameOver) {

		if (underConstruction)
		{
			DigPath(r1, r2);
			// prepare for the next A*
			r2++;
			if (r2 >= NUM_ROOMS)
			{
				r1++;
				r2 = r1 + 1;
				if (r1 + 1 >= NUM_ROOMS)
					underConstruction=false;
			}
		}
		else {
			gameOver = teamA->checkAlive(maze) || teamB->checkAlive(maze);
			if (gameOver) {
				if (teamA->checkAlive(maze))
					cout << "Team B Won The Game!\n";
				else
					cout << "Team A Won The Game!\n";
			}

			//teamA->doSomething(teamB, maze, rooms);
			//teamB->doSomething(teamA, maze, rooms);

			// bullet
			teamA->checkMoveBullets(maze, hits);
			teamA->gotHit(hits);
			teamB->checkMoveBullets(maze, hits);
			teamB->gotHit(hits);
		}
		glutPostRedisplay(); // indirect call to refresh function (display)
	}	
}

void menu(int choice)
{
	if (choice == 1) // fire bullet
	{
		
	}
	else if (choice == 2) // grenade
	{

	}
	else if (choice == 3) // create security map
	{
		CreateSecurityMap();
	}
	else if (choice == 4) // create visibility map
	{
		//CreateVisibilityMap();
	}
	else if (choice == 5) // reset security map
	{
		resetVisual();
	}

	
}

// x and y are in pixels
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if (teamB->getSoldier2())
			teamB->getSoldier2()->throwGrenade(maze);
		
		glutSetWindow(windowInfo);
		displayInfo();
		glutSetWindow(windowMain);
	}
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double buffering for animation
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(300, 900);
	windowInfo = glutCreateWindow("Information");

	glutInitWindowSize(W, H);
	glutInitWindowPosition(700, 100);
	windowMain = glutCreateWindow("Dungeons Example");

	glutSetWindow(windowInfo);
	// set the main axes
	glOrtho(0, MSZ, 0, MSZ, -1, 1);
	srand(time(0));
	glClearColor(0.5, 0.55, 0.5, 0);
	glutDisplayFunc(displayInfo); // sets display function as window refresh function
	glutIdleFunc(idleInfo);

	glutSetWindow(windowMain);
	glutDisplayFunc(display); // sets display function as window refresh function
	glutIdleFunc(idle); // runs all the time when nothing happens
	//glutMouseFunc(mouse);
	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Fire Bullet", 1);
	glutAddMenuEntry("Throw Grenade", 2);
	glutAddMenuEntry("Create Security Map", 3);
	glutAddMenuEntry("Create Visibility Map", 4);
	glutAddMenuEntry("reset Security Map", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop(); // starts window queue of events
}