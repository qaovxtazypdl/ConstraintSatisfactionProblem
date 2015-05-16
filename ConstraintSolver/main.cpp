#include <iostream>
#include <utility>
#include "AbstractSudokuSolver.h"
#include "ConstraintProblem.h"
#include "SudokuSolver_Basic.h"
#include "SudokuSolver_ForwardChecking.h"
#include "SudokuSolver_FC_Heuristics.h"

using namespace std;
//zero valids not detected

map<PairIndex, int> list2map(vector<int> v) {
	map<PairIndex, int> sudokuMap;
	int count = 0;
	for each(int i in v) {
		sudokuMap[PairIndex(count / 9, count % 9)] = i;
		count++;
	}
	return sudokuMap;
}


int main() {
	map<PairIndex, int> initialState;

	vector<int> trivial, simple, easy, medium, hard, evil;
	trivial= { 1, 4, 5, 3, 2, 7, 6, 9, 8, 8, 3, 9, 6, 5, 4, 1, 2, 7, 6, 7, 2, 9, 1, 8, 5, 4, 3, 4, 9, 6, 1, 8, 5, 3, 7, 2, 2, 1, 8, 4, 7, 3, 9, 5, 6, 7, 5, 3, 2, 9, 6, 4, 8, 1, 3, 6, 7, 5, 4, 2, 8, 1, 9, 9, 8, 4, 7, 6, 1, 2, 3, 5, 5, 2, 1, 8, 3, 9, 7, 5 };
	simple = { 1, 4, 5, 3, 2, 7, 6, 9, 8, 8, 3, 9, 6, 5, 4, 1, 2, 7, 6, 7, 2, 9, 1, 8, 5, 4, 3, 4, 9, 6, 1, 8, 5, 3, 7, 2, 2, 1, 8, 4, 7, 3, 9, 5, 6, 7, 5, 3, 2, 9, 6, 4, 8, 1, 3, 6, 7, 5, 4, 2, 8, 1, 9, 9, 8, 4, 7, 6, 1, 2, 3, 5 };
	easy   = { 3, 0, 9, 0, 0, 0, 0, 4, 2, 0, 1, 8, 9, 4, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 0, 0, 0, 3, 0, 9, 0, 0, 6, 0, 4, 2, 7, 0, 0, 0, 5, 8, 9, 0, 6, 0, 0, 8, 0, 2, 0, 0, 0, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 7, 6, 3, 2, 0, 6, 3, 0, 0, 0, 0, 7, 0, 4 };
	medium = { 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 0, 3, 0, 8, 0, 0, 1, 6, 4, 0, 0, 5, 3, 0, 0, 9, 0, 0, 1, 0, 8, 0, 0, 5, 2, 0, 0, 4, 0, 0, 0, 0, 0, 6, 0, 0, 6, 8, 0, 0, 2, 0, 7, 0, 0, 8, 0, 0, 9, 3, 0, 0, 2, 6, 9, 0, 0, 5, 0, 3, 0, 0, 0, 3, 0, 0, 4, 8, 0, 0, 0 };
	hard   = { 6, 0, 0, 8, 0, 9, 0, 0, 0, 0, 0, 5, 0, 0, 7, 0, 8, 6, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1, 3, 0, 7, 8, 0, 1, 0, 0, 0, 5, 0, 4, 7, 0, 9, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1, 8, 0, 5, 0, 0, 6, 0, 0, 0, 0, 0, 3, 0, 4, 0, 0, 5 };
	evil   = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 8, 1, 0, 2, 0, 6, 3, 0, 5, 0, 0, 0, 0, 0, 7, 0, 3, 9, 0, 0, 0, 0, 0, 0, 5, 8, 0, 4, 6, 0, 0, 0, 0, 0, 0, 2, 5, 0, 4, 0, 0, 0, 0, 0, 1, 0, 8, 7, 0, 2, 0, 8, 9, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 6 };

	initialState = list2map(evil);
	/*
	SudokuSolver_Basic solver(initialState);
	solver.backtrackingSearch();
	cout << solver << endl;*/

	/*
	SudokuSolver_ForwardChecking solverFC(initialState);
	solverFC.backtrackingSearch();
	cout << solverFC << endl;*/

	ConstraintProblem<PairIndex, int> *solverFCH = new SudokuSolver_FC_Heuristics(initialState);
	solverFCH->backtrackingSearch();
	solverFCH->printResult();
	delete solverFCH;
}
