#pragma once
#include "ConstraintProblem.h"
#include <vector>
#include <utility>

class AbstractSudokuSolver : virtual public ConstraintProblem<std::pair<int, int>, int> {
public:
	AbstractSudokuSolver();
	virtual ~AbstractSudokuSolver();

protected:
	static const int GRID_WIDTH = 9, GRID_HEIGHT = 9, MAX_VAL = 9;
	static const int TOTAL_ENTRIES = GRID_WIDTH * GRID_HEIGHT;
	Variable grid[GRID_WIDTH][GRID_WIDTH];
	
	int assignedCount = 0;

	//constraint checking
	virtual bool isAssignComplete();
	virtual bool checkConstraints();
};