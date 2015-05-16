#include "SudokuSolver_FC_Heuristics.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <random>

SudokuSolver_FC_Heuristics::SudokuSolver_FC_Heuristics(const std::map<std::pair<int, int>, int> &initialState) : AbstractSudokuSolver() {
	for (auto it = initialState.begin(); it != initialState.end(); ++it) {
		assignValue(it->first, it->second);
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			for (int k = 0; k < MAX_VAL; k++) {
				legalValues[i][j] = MAX_BIT_MASK;
			}
		}
	}
}

SudokuSolver_FC_Heuristics::~SudokuSolver_FC_Heuristics() {
}

//RANDOMLY selects a variable out of the remaining unassigned ones.
const std::pair<int, int> SudokuSolver_FC_Heuristics::selectNextVariable() {
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
const std::vector<int> SudokuSolver_FC_Heuristics::getValueOrder(const std::pair<int, int> &idx) {
	std::vector<int> validValues;
	for (int i = 1; i <= MAX_VAL; i++) {
		if (legalValues[idx.first][idx.second] & (0x1 << (i - 1))) {
			validValues.push_back(i);
		}
	}

	shuffle(validValues.begin(), validValues.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
	return validValues;
}

bool SudokuSolver_FC_Heuristics::checkConstraints(const std::pair<int, int> &idx, const int &value) {
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
void SudokuSolver_FC_Heuristics::assignValue(const std::pair<int, int> &idx, const int &value) {
	if (value > 0 && value <= MAX_VAL) {
		grid[idx.first][idx.second].assignValue(value);
		assignedCount++;

		int mask = 0x1 << (value - 1);
		auto neighboring = neighbours[idx.first][idx.second];
		for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
			legalValues[it->first][it->second] &= ~mask;
		}

	}
}

void SudokuSolver_FC_Heuristics::removeAssign(const std::pair<int, int> &idx) {
	grid[idx.first][idx.second].removeAssign();
	assignedCount--;

	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		int mask = getNeighbourMask(*it);
		legalValues[it->first][it->second] = ~mask & MAX_BIT_MASK;
	}
}

