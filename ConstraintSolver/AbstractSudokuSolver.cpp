#include "AbstractSudokuSolver.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

AbstractSudokuSolver::AbstractSudokuSolver() : ConstraintProblem(), assignedCount(0) {
	for (int i = 0; i < GRID_WIDTH; i++) {
		for (int j = 0; j < GRID_HEIGHT; j++) {
			neighbours[i][j] = getNeighbours(std::pair<int, int>(i, j));
		}
	}
}

AbstractSudokuSolver::~AbstractSudokuSolver() {
}

const std::vector<std::pair<int, int>> AbstractSudokuSolver::getNeighbours(const std::pair<int, int> &idx) {
	std::vector<std::pair<int, int>> neighbours;

	for (int j = 0; j < GRID_HEIGHT; j++) {
		if (idx.second != j) {
			neighbours.push_back(std::pair<int, int>(idx.first, j));
		}
	}

	//get rid of values in the verticals
	for (int i = 0; i < GRID_WIDTH; i++) {
		if (idx.first != i) {
			neighbours.push_back(std::pair<int, int>(i, idx.second));
		}
	}

	int outeri = idx.first / SQUARE_SIZE * SQUARE_SIZE;
	int outerj = idx.second / SQUARE_SIZE * SQUARE_SIZE;
	for (int i = 0; i < SQUARE_SIZE; i++) {
		for (int j = 0; j < SQUARE_SIZE; j++) {
			if (outeri + i != idx.first && outerj + j != idx.second)
				neighbours.push_back(std::pair<int, int>(outeri + i, outerj + j));
		}
	}
	return neighbours;
}

bool AbstractSudokuSolver::isAssignComplete() {
	return assignedCount == TOTAL_ENTRIES;
}

int AbstractSudokuSolver::getNeighbourMask(const std::pair<int, int> &idx) {
	int returnMask = 0;
	auto neighboring = neighbours[idx.first][idx.second];
	for (auto it = neighboring.begin(); it != neighboring.end(); ++it) {
		if (grid[it->first][it->second].isAssigned())
		{
			returnMask |= (0x1 << (grid[it->first][it->second].getValue() - 1));
		}
	}
	return returnMask;
}

bool AbstractSudokuSolver::checkConstraints(const std::pair<int, int> &idx, const int &value) {
	int mask = 0x1 << (value - 1);
	return (getNeighbourMask(idx) & mask) == 0;
}

std::ostream &operator<<(std::ostream &out, const AbstractSudokuSolver &puzzle) {
	for (int i = 0; i < AbstractSudokuSolver::GRID_WIDTH; i++) {
		for (int j = 0; j < AbstractSudokuSolver::GRID_HEIGHT; j++) {
			out << puzzle.grid[i][j].getValue() << " ";
		}
		out << std::endl;
	}

	out << (puzzle.isSolved ? "Solved. " : "No Solution. ") << "Visited " << puzzle.nodesVisited << " nodes in " << puzzle.elapsedTime << " microseconds.";
	return out;
}