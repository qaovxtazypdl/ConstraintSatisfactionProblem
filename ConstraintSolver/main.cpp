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



	vector<int> test;
	test = { 1, 4, 5, 3, 2, 7, 6, 9, 8, 8, 3, 9, 6, 5, 4, 1, 2, 7, 6, 7, 2, 9, 1, 8, 5, 4, 3, 4, 9, 6, 1, 8, 5, 3, 7, 2, 2, 1, 8, 4, 7, 3, 9, 5, 6};
	initialState = list2map(test);

	SudokuSolver_Basic solver(initialState);

	bool success = solver.backtrackingSearch();
	cout << solver << endl;
	cout << success << endl;
}
