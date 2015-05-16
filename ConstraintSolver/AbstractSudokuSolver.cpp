#include "AbstractSudokuSolver.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

AbstractSudokuSolver::AbstractSudokuSolver(const std::map<std::pair<int, int>, int> &initialState) : ConstraintProblem(), assignedCount(0) {
	//init grid
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			grid[i][j] = Variable();
		}
	}

	for (auto it = initialState.begin(); it != initialState.end(); ++it) {
		grid[it->first.first][it->first.second].assignValue(it->second);
	}
}

AbstractSudokuSolver::~AbstractSudokuSolver() {
}

bool AbstractSudokuSolver::isAssignComplete() {
	return assignedCount == TOTAL_ENTRIES;
}

bool AbstractSudokuSolver::checkConstraints() {
	//check rows
	for (int i = 0; i < GRID_WIDTH; i++) {
		int unique9 = 0;
		for (int j = 0; j < GRID_HEIGHT; j++) {
			int mask = 0x1 << (grid[i][j].getValue() - 1);
			if (grid[i][j].isAssigned() && (unique9 & mask)) return false;
			else unique9 |= mask;
		}
	}
	
	//check cols
	for (int j = 0; j < GRID_HEIGHT; j++) {
		int unique9 = 0;
		for (int i = 0; i < GRID_WIDTH; i++) {
			int mask = 0x1 << (grid[i][j].getValue() - 1);
			if (grid[i][j].isAssigned() && (unique9 & mask)) return false;
			else unique9 |= mask;
		}
	}

	//check squares
	for (int outeri = 0; outeri < GRID_WIDTH; outeri += SQUARE_SIZE) {
		for (int outerj = 0; outerj < GRID_HEIGHT; outerj += SQUARE_SIZE) {
			int unique9 = 0;
			for (int i = 0; i < SQUARE_SIZE; i++) {
				for (int j = 0; j < SQUARE_SIZE; j++) {
					int mask = 0x1 << (grid[outeri + i][outerj + j].getValue() - 1);
					if (grid[outeri + i][outerj + j].isAssigned() && (unique9 & mask)) return false;
					else unique9 |= mask;
				}
			}
		}
	}
	return true;
}

std::ostream &operator<<(std::ostream &out, const AbstractSudokuSolver &puzzle) {
	for (int i = 0; i < AbstractSudokuSolver::GRID_WIDTH; i++) {
		for (int j = 0; j < AbstractSudokuSolver::GRID_HEIGHT; j++) {
			std::cout << puzzle.grid[i][j].getValue() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "The backtracking algorithm visited " << puzzle.nodesVisited << " nodes in " << puzzle.elapsedTime << "ns.";
	return out;
}