#include "SudokuSolver_ForwardChecking.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <random>

SudokuSolver_ForwardChecking::SudokuSolver_ForwardChecking(const std::map<std::pair<int, int>, int> &initialState) : AbstractSudokuSolver() {
	for (auto it = initialState.begin(); it != initialState.end(); ++it) {
		if (it->second > 0 && it->second <= MAX_VAL)
		{
			assignValue(it->first, it->second);
		}
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			for (int k = 0; k < MAX_VAL; k++) {
				legalValues[i][j] = MAX_BIT_MASK;
			}
		}
	}
}

SudokuSolver_ForwardChecking::~SudokuSolver_ForwardChecking() {
}

//RANDOMLY selects a variable out of the remaining unassigned ones.
const std::pair<int, int> SudokuSolver_ForwardChecking::selectNextVariable() {
	int select = rand() % (TOTAL_ENTRIES - assignedCount);
	int curCount = 0;

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			std::pair<int, int> curIdx = std::pair<int, int>(i, j);
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
	return std::pair<int, int>(-1, -1);
}

//RANDOMLY order the array 1-9.
const std::vector<int> SudokuSolver_ForwardChecking::getValueOrder(const std::pair<int, int> &idx) {
	std::vector<int> validValues;
	for (int i = 1; i <= MAX_VAL; i++) {
		if (legalValues[idx.first][idx.second] & (0x1 << (i - 1))) {
			validValues.push_back(i);
		}
	}
	shuffle(validValues.begin(), validValues.end(), std::default_random_engine(getTimeInMicroseconds()));

	return validValues;
}

bool SudokuSolver_ForwardChecking::checkConstraints(const std::pair<int, int> &idx, const int &value) {
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
void SudokuSolver_ForwardChecking::assignValue(const std::pair<int, int> &idx, const int &value) {

	grid[idx.first][idx.second].assignValue(value);
	assignedCount++;

	int mask = 0x1 << (value - 1);
	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		legalValues[it->first][it->second] &= ~mask;
	}
}

void SudokuSolver_ForwardChecking::removeAssign(const std::pair<int, int> &idx) {
	grid[idx.first][idx.second].removeAssign();
	assignedCount--;

	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		int mask = getNeighbourMask(*it);
		legalValues[it->first][it->second] = ~mask & MAX_BIT_MASK;
	}
}

