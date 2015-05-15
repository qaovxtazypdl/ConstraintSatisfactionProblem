#pragma once
#include "AbstractSudokuSolver.h"
#include "ConstraintProblem.h"
#include <vector>
#include <utility>

class SudokuSolver_Basic : virtual public AbstractSudokuSolver {
public:
	SudokuSolver_Basic();
	virtual ~SudokuSolver_Basic();
protected:
	//selection of variable and value
	virtual void assignValue(const std::pair<int, int> &idx, const int &value);
	virtual void removeAssign(const std::pair<int, int> &idx);
	virtual const std::pair<int, int> selectNextVariable();
	virtual Variable& getVariable(const std::pair<int, int> &idx);
	virtual const std::vector<int> getValueOrder(const std::pair<int, int> &idx);
};