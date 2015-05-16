#include "SudokuSolver_ForwardChecking.h"
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <random>

SudokuSolver_ForwardChecking::SudokuSolver_ForwardChecking(const std::map<PairIndex, int> &initialState) : AbstractSudokuSolver() {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			legalValues[i][j] = MAX_BIT_MASK;
		}
	}

	for (auto it = initialState.begin(); it != initialState.end(); ++it) {
		if (it->second > 0 && it->second <= MAX_VAL)
		{
			assignValue(it->first, it->second);
		}
	}
}

SudokuSolver_ForwardChecking::~SudokuSolver_ForwardChecking() {
}

//RANDOMLY selects a variable out of the remaining unassigned ones.
const PairIndex SudokuSolver_ForwardChecking::selectNextVariable() {
	int select = rand() % (TOTAL_ENTRIES - assignedCount);
	int curCount = 0;

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			PairIndex curIdx = PairIndex(i, j);
			if (!grid[curIdx.first][curIdx.second].isAssigned()) {
				if (curCount == select)
				{
					return curIdx;
				}
				curCount++;
			}
		}
	}

	//something has gone horribly wrong
	return PairIndex(-1, -1);
}

//RANDOMLY order the array 1-9.
const std::vector<int> SudokuSolver_ForwardChecking::getValueOrder(const PairIndex &idx) {
	std::vector<int> validValues;
	for (int i = 1; i <= MAX_VAL; i++) {
		if (legalValues[idx.first][idx.second] & (0x1 << (i - 1))) {
			validValues.push_back(i);
		}
	}
	shuffle(validValues.begin(), validValues.end(), std::default_random_engine(getTimeInMicroseconds()));

	return validValues;
}

bool SudokuSolver_ForwardChecking::checkConstraints(const PairIndex &idx, const int &value) {
	bool checkBase = AbstractSudokuSolver::checkConstraints(idx, value);
	if (checkBase == false) return false;

	//check the forward checking condition - check the variables that potentially are updated only.
	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		if (!grid[it->first][it->second].isAssigned() && legalValues[it->first][it->second] == (0x1 << (value - 1))) {
			return false;
		}
	}

	return true;
}

//selection of variable and value
void SudokuSolver_ForwardChecking::assignValue(const PairIndex &idx, const int &value) {

	grid[idx.first][idx.second].assignValue(value);
	assignedCount++;

	int mask = 0x1 << (value - 1);
	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		legalValues[it->first][it->second] &= ~mask;
	}
}

void SudokuSolver_ForwardChecking::removeAssign(const PairIndex &idx) {
	grid[idx.first][idx.second].removeAssign();
	assignedCount--;

	//recompute neighbouring masks.
	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		int neighbourMask = getNeighbourMask(*it);
		legalValues[it->first][it->second] = ~neighbourMask & MAX_BIT_MASK;
	}
}

