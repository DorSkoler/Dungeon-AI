#include "Functions.h"
#include "Team.h"
#include "Cell.h"
#include <queue>
#include <thread>
#include "CompareCells.h"
#include "Room.h"

double getDirectionAngle(NPC* source, NPC* target) {
	double distance;
	double targetX = target->getX();
	double targetY = target->getY();
	double x = source->getX();
	double y = source->getY();
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	// [dx,dy] must be vector of length 1 to the direction to target
	double dx = (targetX - x) / distance;
	return acos(dx);
}

double getDistance(NPC* source, NPC* target) {
	double distance;
	double targetX = target->getX();
	double targetY = target->getY();
	double x = source->getX();
	double y = source->getY();
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	return distance;
}

void getMyTarget(NPC* pn, NPC* pTarget)
{
	pn->setPTarget(pTarget);
	pn->setDirectionAngle(getDirectionAngle(pn, pTarget));
}

int whichRoom(NPC* pn, Room rooms[NUM_ROOMS]) {
	if (!pn)
		return -1;
	for (int i = 0; i < NUM_ROOMS; i++) {
		if (pn->getX() <= (rooms[i].getCenterX() + rooms[i].getWidth() / 2) && pn->getX() >= (rooms[i].getCenterX() - rooms[i].getWidth() / 2)) {
			if (pn->getY() <= (rooms[i].getCenterY() + rooms[i].getHeight() / 2) && pn->getY() >= (rooms[i].getCenterY() - rooms[i].getHeight() / 2)) {
				return i;
			}
		}
	}
	return -1;
}

NPC* getTarget(Room rooms[NUM_ROOMS], Team* enemy, NPC* me) {
	double targetToChase = MAXINT;
	int myRoom = whichRoom(me, rooms);
	NPC* target = nullptr;

	for (int i = 0; i < 3; i++) {
		int room = whichRoom(enemy->getNpcByIndex(i), rooms);
		if (room > -1) {
			double current = getDistance(me, enemy->getNpcByIndex(i));
			if (targetToChase > current) {
				targetToChase = current;
				target = enemy->getNpcByIndex(i);
			}
		}
	}
	return target;
}

bool isSameRoom(Room* room1, Room* room2) {
	return room1->getCenterX() == room2->getCenterX() && room1->getCenterY() == room2->getCenterY();
}

NPC* getRoomTarget(Room rooms[NUM_ROOMS], NPC* me) {
	NPC* target = nullptr;
	int random = 0;
	do {
		random = rand() % NUM_ROOMS;

	} while (isSameRoom(&rooms[random], me->getCurrentRoom()));
	target = new NPC(rooms[random].getCenterX(), rooms[random].getCenterY(), 0);
	return target;
}

void CreateSecurityMap(double security_map[MSZ][MSZ], int maze[MSZ][MSZ])
{
	int num_simulations = 300;
	double damage = 0.01;
	int i;
	Grenade* g;

	for (i = 0; i < num_simulations; i++)
	{
		g = new Grenade(rand() % MSZ, rand() % MSZ, 0, 0, 0);
		g->SimulateExplosion(maze, security_map, damage);
	}
}

void CreateVisibilityMap(NPC* pn, int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ])
{
	int num_simulations = 360;
	int i;
	std::vector<Bullet*> bullets;
	double teta = 2 * 3.14 / num_simulations;

	for (int i = 0; i < num_simulations; i++) {
		bullets.push_back(new Bullet(pn->getX(), pn->getY(), i * teta, 0, 0, 0));
		bullets.at(i)->Fire();
		bullets.at(i)->SimulateVisibility(maze, visibility_map);
	}
}

void CheckNeighbor(int row, int col, Cell* pcurrent, std::priority_queue <Cell, std::vector<Cell>, CompareCells>& pq,
	std::vector <Cell>& grays, std::vector <Cell>& blacks, int maze[MSZ][MSZ], double security_map[MSZ][MSZ], bool use_security)
{
	double cost;
	std::vector <Cell>::iterator itrb;
	std::vector <Cell>::iterator itrg;

	if (use_security) {
		if (!(maze[row][col] == SPACE || maze[row][col] == PASS)) cost = MAXINT;
		else cost = security_map[row][col];
	}
	else {
		if (!(maze[row][col] == SPACE || maze[row][col] == PASS)) cost = MAXINT;
		else cost = 1;
	}
		

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
				std::vector <Cell> tmp;
				while (!pq.empty() && !((*pn) == pq.top()))
				{
					tmp.push_back(pq.top());
					pq.pop();
				}
				if (pq.empty())
					std::cout << " neighbor wasn't found in pq \n";
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

Cell* getStartCell(Cell* ps, int maze[MSZ][MSZ])
{
	Cell* pn = nullptr;
	while (ps->getParent() != nullptr)
	{
		//maze[ps->getRow()][ps->getCol()] = PASS;
		pn = ps;
		ps = ps->getParent();
		ps->setChild(pn);
	}
	return ps->getChild();
}


Cell* findRoute(NPC* pn, int maze[MSZ][MSZ], double security_map[MSZ][MSZ], bool use_security)
{
	Cell* startingCell = new Cell(pn->getY(), pn->getX(),
		nullptr, 0, pn->getPTarget()->getY(), pn->getPTarget()->getX());

	Cell* pcurrent = nullptr;
	int currentRow, currentCol;

	std::priority_queue <Cell, std::vector<Cell>, CompareCells> pq;
	std::vector <Cell> grays;
	std::vector <Cell> blacks;

	std::vector <Cell>::iterator itr;


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
		if (pcurrent->getRow() == pn->getPTarget()->getY() && pcurrent->getCol() == pn->getPTarget()->getX())
		{
			return pcurrent;
		}
		// remove current from pq and paint it black (remove it from grays)
		pq.pop();
		blacks.push_back(*pcurrent);
		// remove it from grays
		itr = find(grays.begin(), grays.end(), *pcurrent); // Cell must have operator ==
		if (itr == grays.end()) // current cell wasn't found: ERROR
		{
			std::cout << "error 1\n";
			return nullptr;
		}
		grays.erase(itr);

		// now check the neighbor cells
		currentRow = pcurrent->getRow();
		currentCol = pcurrent->getCol();
		if (currentRow > 0) // UP
			CheckNeighbor(currentRow - 1, currentCol, pcurrent, pq, grays, blacks, maze, security_map, use_security);
		if (currentRow < MSZ - 1) // DOWN
			CheckNeighbor(currentRow + 1, currentCol, pcurrent, pq, grays, blacks, maze, security_map, use_security);
		if (currentCol > 0) // LEFT
			CheckNeighbor(currentRow, currentCol - 1, pcurrent, pq, grays, blacks, maze, security_map, use_security);
		if (currentCol < MSZ - 1) // RIGHT
			CheckNeighbor(currentRow, currentCol + 1, pcurrent, pq, grays, blacks, maze, security_map, use_security);
	} // while
	// We shouldn't reach this point normally
	std::cout << "error 2\n";
}

