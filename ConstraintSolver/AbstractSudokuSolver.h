#pragma once
#include "ConstraintProblem.h"
#include <vector>
#include <utility>
#include <array>
#include <map>

class AbstractSudokuSolver : virtual public ConstraintProblem<std::pair<int, int>, int> {
public:
	AbstractSudokuSolver();
	virtual ~AbstractSudokuSolver();
	friend std::ostream &operator<<(std::ostream &out, const AbstractSudokuSolver &puzzle);

protected:
	static const int GRID_WIDTH = 9, GRID_HEIGHT = 9, MAX_VAL = 9;
	static const int SQUARE_SIZE = 3;
	static const int MAX_BIT_MASK = 0x000001ff;
	static const int TOTAL_ENTRIES = 81;

	std::array<std::array<Variable, GRID_HEIGHT>, GRID_WIDTH> grid;
	std::array<std::array<std::vector<std::pair<int, int>>, GRID_HEIGHT>, GRID_WIDTH> neighbours;
	
	int assignedCount;

	//constraint checking
	virtual bool isAssignComplete();
	virtual bool checkConstraints(const std::pair<int, int> &idx, const int &value);

	virtual void assignValue(const std::pair<int, int> &idx, const int &value) = 0;
	virtual void removeAssign(const std::pair<int, int> &idx) = 0;
	virtual const std::pair<int, int> selectNextVariable() = 0;
	virtual const std::vector<int> getValueOrder(const std::pair<int, int> &idx) = 0;

	//utility
	int getNeighbourMask(const std::pair<int, int> &idx);

private:
	//helper
	const std::vector<std::pair<int, int>> getNeighbours(const std::pair<int, int> &idx);
};