#pragma once
class Cell
{
private:
	int row, col;
	int targetRow, targetCol;
	Cell* parent;
	Cell* child;
	double f, g, h;
public:
	Cell();
	Cell(int r, int c, Cell* p,double g,int tr, int tc);
	
	~Cell();
	int getRow() { return row; }
	int getCol() { return col; }
	int getTargetRow() { return row; }
	int getTargetCol() { return col; }
	Cell* getParent() { return parent; }
	Cell* getChild() { return child; }
	void setChild(Cell* c) { child = c; }
	void ComputeH();
	void ComputeF() { f = g + h; }
	double getF() { return f; }
	double getG() { return g; }
	bool operator == (const Cell& other) { return row == other.row && col == other.col; }
	void setG(double newG) { g = newG; }
};

