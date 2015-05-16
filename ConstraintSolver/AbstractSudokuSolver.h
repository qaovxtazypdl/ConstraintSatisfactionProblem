#pragma once
#include "ConstraintProblem.h"
#include <vector>
#include <utility>
#include <array>
#include <map>

class AbstractSudokuSolver : virtual public ConstraintProblem<std::pair<int, int>, int> {
public:
	AbstractSudokuSolver(const std::map<std::pair<int, int>, int> &initialState);
	virtual ~AbstractSudokuSolver();
	friend std::ostream &operator<<(std::ostream &out, const AbstractSudokuSolver &puzzle);

protected:
	static const int GRID_WIDTH = 9, GRID_HEIGHT = 9, MAX_VAL = 9;
	static const int SQUARE_SIZE = 3;
	static const int TOTAL_ENTRIES = GRID_WIDTH * GRID_HEIGHT;

	std::array<std::array<Variable, GRID_HEIGHT>, GRID_WIDTH> grid;
	
	int assignedCount;

	//constraint checking
	virtual bool isAssignComplete();
	virtual bool checkConstraints();
};