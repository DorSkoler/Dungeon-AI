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
	pn->setDestination(pTarget->getX(), pTarget->getY(), pTarget);
	pn->setDirectionAngle(getDirectionAngle(pn, pTarget));
}

int whichRoom(NPC* pn, Room rooms[NUM_ROOMS]) {
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
		if ( room > -1) {
			double current = getDistance(me, enemy->getNpcByIndex(i));
			if (targetToChase > current) {
				targetToChase = current;
				target = enemy->getNpcByIndex(i);
			}
		}
	}
	return target;
}

void CreateSecurityMap(double security_map[MSZ][MSZ], int maze[MSZ][MSZ])
{
	int num_simulations = 250;
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
	int num_simulations = 100;
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
	std::vector <Cell>& grays, std::vector <Cell>& blacks, int maze[MSZ][MSZ], bool use_security)
{
	double security_map[MSZ][MSZ] = { 0 };
	if (use_security)
		CreateSecurityMap(security_map, maze);
	double cost;
	std::vector <Cell>::iterator itrb;
	std::vector <Cell>::iterator itrg;

	if (!(maze[row][col] == SPACE || maze[row][col] == PASS)) cost = MAXINT;
	cost = security_map[row][col];

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

void RestorePath(Cell* ps, int maze[MSZ][MSZ])
{
	while (ps->getParent() != nullptr)
	{
		if (maze[ps->getRow()][ps->getCol()] == SPACE)
			maze[ps->getRow()][ps->getCol()] = PASS;
		ps = ps->getParent();
	}
}

Cell* findRoute(NPC* pn, int maze[MSZ][MSZ], bool use_security)
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
			return nullptr;
		}
		grays.erase(itr);

		// now check the neighbor cells
		currentRow = pcurrent->getRow();
		currentCol = pcurrent->getCol();
		if (currentRow > 0) // UP
			CheckNeighbor(currentRow - 1, currentCol, pcurrent, pq, grays, blacks, maze, use_security);
		if (currentRow < MSZ - 1) // DOWN
			CheckNeighbor(currentRow + 1, currentCol, pcurrent, pq, grays, blacks, maze, use_security);
		if (currentCol > 0) // LEFT
			CheckNeighbor(currentRow, currentCol - 1, pcurrent, pq, grays, blacks, maze, use_security);
		if (currentCol < MSZ - 1) // RIGHT
			CheckNeighbor(currentRow, currentCol + 1, pcurrent, pq, grays, blacks, maze, use_security);
	} // while
	// We shouldn't reach this point normally
}