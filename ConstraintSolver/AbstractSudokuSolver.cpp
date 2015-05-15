#include "AbstractSudokuSolver.h"
#include <stdlib.h>
#include <time.h>

AbstractSudokuSolver::AbstractSudokuSolver() {
	srand(time(NULL));

	//init grid
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			grid[i][j] = Variable();
		}
	}
}

AbstractSudokuSolver::~AbstractSudokuSolver() {
}

bool AbstractSudokuSolver::isAssignComplete() {
	return assignedCount == TOTAL_ENTRIES;
}

bool AbstractSudokuSolver::checkConstraints() {
	return false;
}