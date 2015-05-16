#pragma once
#include "AbstractSudokuSolver.h"
#include "ConstraintProblem.h"
#include <vector>
#include <utility>

class SudokuSolver_ForwardChecking : virtual public AbstractSudokuSolver {
public:
	SudokuSolver_ForwardChecking(const std::map<std::pair<int, int>, int> &initialState);
	virtual ~SudokuSolver_ForwardChecking();
protected:
	std::array<std::array<int, GRID_HEIGHT>, GRID_WIDTH> legalValues;

	//selection of variable and value
	virtual const std::pair<int, int> selectNextVariable();
	virtual const std::vector<int> getValueOrder(const std::pair<int, int> &idx);

	virtual bool checkConstraints(const std::pair<int, int> &idx, const int &value);
	virtual void assignValue(const std::pair<int, int> &idx, const int &value);
	virtual void removeAssign(const std::pair<int, int> &idx);

	int neighbourElimination(const std::pair<int, int> &idx);
};