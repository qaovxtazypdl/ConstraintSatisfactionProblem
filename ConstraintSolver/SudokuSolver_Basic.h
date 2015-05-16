#pragma once
#include "AbstractSudokuSolver.h"
#include "ConstraintProblem.h"
#include <vector>
#include <utility>

class SudokuSolver_Basic : virtual public AbstractSudokuSolver {
public:
	SudokuSolver_Basic(const std::map<std::pair<int, int>, int> &initialState);
	virtual ~SudokuSolver_Basic();
protected:
	virtual const std::pair<int, int> selectNextVariable();
	virtual const std::vector<int> getValueOrder(const std::pair<int, int> &idx);
	virtual void assignValue(const std::pair<int, int> &idx, const int &value);
	virtual void removeAssign(const std::pair<int, int> &idx);
};