#include "AbstractSudokuSolver.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

AbstractSudokuSolver::AbstractSudokuSolver(const std::map<std::pair<int, int>, int> &initialState) : ConstraintProblem() {
	srand((unsigned int)time(NULL));

	//init grid
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			grid[i][j] = Variable();
		}
	}

	for (auto it = initialState.begin(); it != initialState.end(); ++it) {
		getVariable(it->first).assignValue(it->second);
	}
}

AbstractSudokuSolver::~AbstractSudokuSolver() {
}

bool AbstractSudokuSolver::isAssignComplete() {
	return assignedCount == TOTAL_ENTRIES;
}

bool AbstractSudokuSolver::checkConstraints() {
	return true;
}

std::ostream &operator<<(std::ostream &out, const AbstractSudokuSolver &puzzle) {
	for (int i = 0; i < AbstractSudokuSolver::GRID_WIDTH; i++) {
		for (int j = 0; j < AbstractSudokuSolver::GRID_HEIGHT; j++) {
			std::cout << puzzle.grid[i][j].getValue() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "The backtracking algorithm visited " << puzzle.nodesVisited << " nodes in " << puzzle.elapsedTime << "ms." << std::endl;
	return out;
}