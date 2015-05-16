#include "SudokuSolver_Basic.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <random>

SudokuSolver_Basic::SudokuSolver_Basic(const std::map<std::pair<int, int>, int> &initialState) : AbstractSudokuSolver() {
	for (auto it = initialState.begin(); it != initialState.end(); ++it) {
		if (it->second > 0 && it->second <= MAX_VAL)
		{
			assignValue(it->first, it->second);
		}
	}
}

SudokuSolver_Basic::~SudokuSolver_Basic() {
}

//RANDOMLY selects a variable out of the remaining unassigned ones.
const std::pair<int, int> SudokuSolver_Basic::selectNextVariable() {
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
const std::vector<int> SudokuSolver_Basic::getValueOrder(const std::pair<int, int> &idx) {
	std::vector<int> validValues;
	for (int i = 1; i <= MAX_VAL; i++) {
		validValues.push_back(i);
	}

	shuffle(validValues.begin(), validValues.end(), std::default_random_engine(getTimeInMicroseconds()));

	return validValues;
}

//selection of variable and value
void SudokuSolver_Basic::assignValue(const std::pair<int, int> &idx, const int &value) {
	grid[idx.first][idx.second].assignValue(value);
	assignedCount++;
}

void SudokuSolver_Basic::removeAssign(const std::pair<int, int> &idx) {
	grid[idx.first][idx.second].removeAssign();
	assignedCount--;
}