#include <iostream>
#include <utility>
#include "AbstractSudokuSolver.h"
#include "SudokuSolver_Basic.h"
#include <chrono>

using namespace std;
//todo: implement getvar again or
//check inputs on load
//random numbers on fail state
//randomly failing...

map<pair<int, int>, int> list2map(vector<int> v) {
	map<pair<int, int>, int> sudoMap;
	int count = 0;
	for each(int i in v) {
		sudoMap[pair<int, int>(count / 9, count % 9)] = i;
		count++;
	}
	return sudoMap;
}


int main() {
	map<pair<int, int>, int> initialState;



	vector<int> easy, medium, hard, evil;
	easy   = { 3, 0, 9, 0, 0, 0, 0, 4, 2, 0, 1, 8, 9, 4, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 0, 0, 0, 3, 0, 9, 0, 0, 6, 0, 4, 2, 7, 0, 0, 0, 5, 8, 9, 0, 6, 0, 0, 8, 0, 2, 0, 0, 0, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 7, 6, 3, 2, 0, 6, 3, 0, 0, 0, 0, 7, 0, 4 };
	medium = { 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 0, 3, 0, 8, 0, 0, 1, 6, 4, 0, 0, 5, 3, 0, 0, 9, 0, 0, 1, 0, 8, 0, 0, 5, 2, 0, 0, 4, 0, 0, 0, 0, 0, 6, 0, 0, 6, 8, 0, 0, 2, 0, 7, 0, 0, 8, 0, 0, 9, 3, 0, 0, 2, 6, 9, 0, 0, 5, 0, 3, 0, 0, 0, 3, 0, 0, 4, 8, 0, 0, 0 };
	hard   = { 6, 0, 0, 8, 0, 9, 0, 0, 0, 0, 0, 5, 0, 0, 7, 0, 8, 6, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1, 3, 0, 7, 8, 0, 1, 0, 0, 0, 5, 0, 4, 7, 0, 9, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1, 8, 0, 5, 0, 0, 6, 0, 0, 0, 0, 0, 3, 0, 4, 0, 0, 5 };
	evil   = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 8, 1, 0, 2, 0, 6, 3, 0, 5, 0, 0, 0, 0, 0, 7, 0, 3, 9, 0, 0, 0, 0, 0, 0, 5, 8, 0, 4, 6, 0, 0, 0, 0, 0, 0, 2, 5, 0, 4, 0, 0, 0, 0, 0, 1, 0, 8, 7, 0, 2, 0, 8, 9, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 6 };

	initialState = list2map(easy);

	SudokuSolver_Basic solver(initialState);

	bool success = solver.backtrackingSearch();
	cout << solver << endl;
	cout << success << endl;
}
