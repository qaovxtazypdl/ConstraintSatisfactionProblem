#pragma once
#include <vector>

template<class VarIndex, class VarType>
class ConstraintProblem {
public:
	//main search algorithm
	virtual bool backtrackingSearch() {
		if (isAssignComplete()) return true;

		VarIndex idx = selectNextVariable();
		std::vector<VarType> valueOrder = getValueOrder(idx);
		for (std::vector<VarType>::const_iterator it = valueOrder.begin(); it != valueOrder.end(); ++it)
		{
			assignValue(idx, *it);
			if (checkConstraints()) {
				if (backtrackingSearch()) return true;
				removeAssign(idx);
			} else {
				removeAssign(idx);
			}
		}
		return false;
	};

protected:
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
	};

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

