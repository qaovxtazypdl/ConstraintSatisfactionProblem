#pragma once
#include "AbstractSudokuSolver.h"
#include "ConstraintProblem.h"
#include <utility>

class SudokuSolver_FC_Heuristics : virtual public AbstractSudokuSolver {
public:
	SudokuSolver_FC_Heuristics(const std::map<PairIndex, int> &initialState);
	virtual ~SudokuSolver_FC_Heuristics();
protected:
	std::array<std::array<int, GRID_HEIGHT>, GRID_WIDTH> legalValues;
	std::array<std::array<std::array<int, MAX_VAL>, GRID_HEIGHT>, GRID_WIDTH> constraintsApplied;

	//selection of variable and value
	virtual const PairIndex selectNextVariable();
	virtual const std::vector<int> getValueOrder(const PairIndex &idx);
	virtual bool checkConstraints(const PairIndex &idx, const int &value);

	virtual void assignValue(const PairIndex &idx, const int &value);
	virtual void removeAssign(const PairIndex &idx);
};