#pragma once
#include "AbstractSudokuSolver.h"
#include "ConstraintProblem.h"
#include <vector>
#include <utility>

class SudokuSolver_ForwardChecking : virtual public AbstractSudokuSolver {
public:
	SudokuSolver_ForwardChecking(const std::map<PairIndex, int> &initialState);
	virtual ~SudokuSolver_ForwardChecking();
protected:
	std::array<std::array<int, GRID_HEIGHT>, GRID_WIDTH> legalValues;

	//selection of variable and value
	virtual const PairIndex selectNextVariable();
	virtual const std::vector<int> getValueOrder(const PairIndex &idx);
	virtual bool checkConstraints(const PairIndex &idx, const int &value);

	virtual void assignValue(const PairIndex &idx, const int &value);
	virtual void removeAssign(const PairIndex &idx);
};