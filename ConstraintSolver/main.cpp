#include <iostream>
#include <utility>
#include "AbstractSudokuSolver.h"
#include "SudokuSolver_Basic.h"

using namespace std;

int main() {
	map<pair<int, int>, int> initialState;
	AbstractSudokuSolver *solver = new SudokuSolver_Basic(initialState);

	bool success = solver->backtrackingSearch();
	cout << *solver << endl;
	cout << success << endl;
}