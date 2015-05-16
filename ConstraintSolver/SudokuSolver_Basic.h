#pragma once
#include "AbstractSudokuSolver.h"
#include "ConstraintProblem.h"
#include <utility>

class SudokuSolver_Basic : virtual public AbstractSudokuSolver {
public:
	SudokuSolver_Basic(const std::map<PairIndex, int> &initialState);
	virtual ~SudokuSolver_Basic();
protected:
	virtual const PairIndex selectNextVariable();
	virtual const std::vector<int> getValueOrder(const PairIndex &idx);
	virtual void assignValue(const PairIndex &idx, const int &value);
	virtual void removeAssign(const PairIndex &idx);
};