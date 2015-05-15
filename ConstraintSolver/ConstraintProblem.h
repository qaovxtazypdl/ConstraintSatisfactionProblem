#pragma once
#include <vector>
#include <time.h>

template<class VarIndex, class VarType>
class ConstraintProblem {
public:
	ConstraintProblem() : nodesVisited(0), elapsedTime(0) {
	}

	//main search algorithm
	virtual bool backtrackingSearch() {
		unsigned int startTime = (unsigned int)time(NULL);
		bool result = backtrackingSearch_Recursive();
		elapsedTime = (unsigned int)time(NULL) - startTime;
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
			assignValue(idx, *it);
			if (checkConstraints()) {
				if (backtrackingSearch_Recursive()) return true;
				else removeAssign(idx);
			}
			else {
				removeAssign(idx);
			}
		}
		return false;
	};

	class Variable {
		VarType value;
		bool assigned;

	public:
		Variable() : assigned(false) {
		}

		void assignValue(const VarType &val) {
			value = val;
			assigned = true;
		}

		void removeAssign() {
			assigned = false;
		}

		bool isAssigned() {
			return assigned;
		}

		VarType getValue() const {
			return value;
		}
	};

	int nodesVisited;
	unsigned int elapsedTime;

	//constraint checking
	virtual bool isAssignComplete() = 0;
	virtual bool checkConstraints() = 0;

	//selection of variable and value
	virtual void assignValue(const VarIndex &selectedVar, const VarType &value) = 0;
	virtual void removeAssign(const VarIndex &selectedVar) = 0;
	virtual const VarIndex selectNextVariable() = 0;
	virtual const std::vector<VarType> getValueOrder(const VarIndex &idx) = 0;

	virtual Variable& getVariable(const VarIndex &idx) = 0;
};

