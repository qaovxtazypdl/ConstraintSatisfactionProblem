#include "SudokuSolver_FC_Heuristics.h"
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <list>

SudokuSolver_FC_Heuristics::SudokuSolver_FC_Heuristics(const std::map<PairIndex, int> &initialState) : AbstractSudokuSolver() {
	for (auto it = initialState.begin(); it != initialState.end(); ++it) {
		if (it->second > 0 && it->second <= MAX_VAL)
		{
			assignValue(it->first, it->second);
		}
	}

	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			legalValues[i][j] = MAX_BIT_MASK;
		}
	}
}

SudokuSolver_FC_Heuristics::~SudokuSolver_FC_Heuristics() {
}

//RANDOMLY selects a variable out of the remaining unassigned ones.
const PairIndex SudokuSolver_FC_Heuristics::selectNextVariable() {
	//H: most constrained variable heuristic
	int fewestLegals = INT_MAX;
	std::vector<PairIndex> mostConstrained;
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			PairIndex curIdx = PairIndex(i, j);
			if (!grid[curIdx.first][curIdx.second].isAssigned()) {
				int legals = numberOfSetBits(legalValues[curIdx.first][curIdx.second]);
				if (legals == fewestLegals) {
					mostConstrained.push_back(curIdx);
				} else if (legals < fewestLegals) {
					fewestLegals = legals;
					mostConstrained.clear();
					mostConstrained.push_back(curIdx);
				}
			}
		}
	}
	if (mostConstrained.size() == 1) return mostConstrained[0];
	//something has gone horribly wrong.
	else if (mostConstrained.size() == 0) return PairIndex(-1, -1);

	//H: most constraining variable heuristic to break ties.
	int mostConstraints = INT_MIN;
	std::vector<PairIndex> mostConstraining;
	for (auto it = mostConstrained.begin(); it != mostConstrained.end(); ++it) {
		int numConstraints = neighbours[it->first][it->second].size();
		if (numConstraints == mostConstraints) {
			mostConstraining.push_back(*it);
		} else {
			mostConstraints = numConstraints;
			mostConstraining.clear();
			mostConstraining.push_back(*it);
		}
	}

	//something has gone horribly wrong.
	if (mostConstraining.size() == 0) return PairIndex(-1, -1);
	else {
		//return an index at random.
		return mostConstraining[rand() % mostConstraining.size()];
	}
}

const std::vector<int> SudokuSolver_FC_Heuristics::getValueOrder(const PairIndex &idx) {
	std::vector<int> validValues;
	for (int i = 1; i <= MAX_VAL; i++) {
		if (legalValues[idx.first][idx.second] & (0x1 << (i - 1))) {
			validValues.push_back(i);
		}
	}
	//randomize the order of checking to randomly break any ties at the end.
	shuffle(validValues.begin(), validValues.end(), std::default_random_engine(getTimeInMicroseconds()));

	//H: least constraining value heuristic
	int seen = 0;
	std::list<PairIndex> minPriorityList;
	for (auto validValueIt = validValues.begin(); validValueIt != validValues.end(); ++validValueIt) {
		seen++;
		int i = *validValueIt;
		int mask = 0x1 << (i - 1);
		int ruledOut = 0;

		auto neighboring = neighbours[idx.first][idx.second];
		for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
			if (!grid[it->first][it->second].isAssigned() && (legalValues[it->first][it->second] & mask)) {
				ruledOut++;
			}
		}

		//insert values into a linked list in stable order (same ruledOut values are sorted by order in validValues, which is random)
		int priority = ruledOut * 10 + seen;

		auto listIt = minPriorityList.begin();
		for (; listIt != minPriorityList.end(); ++listIt) {
			if (listIt->first > priority) break;
		}
		minPriorityList.insert(listIt, PairIndex(priority, i));
	}

	std::vector<int> returnOrder;
	for (auto listIt = minPriorityList.begin(); listIt != minPriorityList.end(); ++listIt) {
		returnOrder.push_back(listIt->second);
	}
	return returnOrder;
}

bool SudokuSolver_FC_Heuristics::checkConstraints(const PairIndex &idx, const int &value) {
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
void SudokuSolver_FC_Heuristics::assignValue(const PairIndex &idx, const int &value) {
	grid[idx.first][idx.second].assignValue(value);
	assignedCount++;

	int mask = 0x1 << (value - 1);
	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		legalValues[it->first][it->second] &= ~mask;
	}
}

void SudokuSolver_FC_Heuristics::removeAssign(const PairIndex &idx) {
	grid[idx.first][idx.second].removeAssign();
	assignedCount--;

	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		int neighbourMask = getNeighbourMask(*it);
		legalValues[it->first][it->second] = ~neighbourMask & MAX_BIT_MASK;
	}
}

