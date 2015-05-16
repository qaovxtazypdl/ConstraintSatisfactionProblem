#pragma once
#include <vector>
#include <time.h>
#include <iostream>
#include <chrono>

template<class VarIndex, class VarType>
class ConstraintProblem {
public:
	ConstraintProblem() : nodesVisited(0), elapsedTime(0), isSolved(false) {
		srand((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	}

	//main search algorithm
	virtual bool backtrackingSearch() {
		auto startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		bool result = backtrackingSearch_Recursive();
		elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - startTime;
		isSolved = result;
		return result;
	};

protected:
	virtual bool backtrackingSearch_Recursive() {
		nodesVisited++;
		if (isAssignComplete()) return true;

		VarIndex idx = selectNextVariable();
		std::vector<VarType> valueOrder = getValueOrder(idx);
		for (auto it = valueOrder.begin(); it != valueOrder.end(); ++it)
		{
			if (checkConstraints(idx, *it)) {
				assignValue(idx, *it);
				if (backtrackingSearch_Recursive()) return true;
				else removeAssign(idx);
			}
		}
		return false;
	};

	class Variable {
		VarType value;
		bool assigned;

	public:
		Variable() : assigned(false) {
			value = VarType();
		}

		void assignValue(const VarType &val) {
			value = val;
			assigned = true;
		}

		void removeAssign() {
			value = VarType();
			assigned = false;
		}

		bool isAssigned() {
			return assigned;
		}

		VarType getValue() const {
			return value;
		}
	};

	unsigned long nodesVisited;
	unsigned long elapsedTime;
	bool isSolved;

	//constraint checking
	virtual bool isAssignComplete() = 0;
	virtual bool checkConstraints(const VarIndex &selectedVar, const VarType &value) = 0;

	//selection of variable and value
	virtual void assignValue(const VarIndex &selectedVar, const VarType &value) = 0;
	virtual void removeAssign(const VarIndex &selectedVar) = 0;
	virtual const VarIndex selectNextVariable() = 0;
	virtual const std::vector<VarType> getValueOrder(const VarIndex &idx) = 0;
};

