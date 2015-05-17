#pragma once
#include "ConstraintProblem.h"
#include <utility>
#include <array>
#include <map>
#include <iostream>

typedef std::pair<int, int> PairIndex;

class AbstractSudokuSolver : virtual public ConstraintProblem<PairIndex, int> {
public:
	AbstractSudokuSolver();
	virtual ~AbstractSudokuSolver();
	virtual void printResult() {
		std::cout << *this << std::endl;
	}
	friend std::ostream &operator<<(std::ostream &out, const AbstractSudokuSolver &puzzle);

protected:
	static const int GRID_WIDTH = 9, GRID_HEIGHT = 9, MAX_VAL = 9;
	static const int SQUARE_SIZE = 3;
	static const int MAX_BIT_MASK = 0x000001ff;
	static const int TOTAL_ENTRIES = 81;

	std::array<std::array<Variable, GRID_HEIGHT>, GRID_WIDTH> grid;
	std::array<std::array<std::vector<PairIndex>, GRID_HEIGHT>, GRID_WIDTH> neighbours;
	
	int assignedCount;

	//pure virtuals / expect to be overwritten
	virtual bool checkConstraints(const PairIndex &idx, const int &value);
	virtual void assignValue(const PairIndex &idx, const int &value) = 0;
	virtual void removeAssign(const PairIndex &idx) = 0;
	virtual const PairIndex selectNextVariable() = 0;
	virtual const std::vector<int> getValueOrder(const PairIndex &idx) = 0;

	//utility / expect not to be overwritten
	virtual bool isAssignComplete();
	int getNeighbourMask(const PairIndex &idx);
	int numberOfSetBits(int i);
	void shuffle(std::vector<int> &vect);

private:
	//helper
	const std::vector<PairIndex> getNeighbours(const PairIndex &idx);
};