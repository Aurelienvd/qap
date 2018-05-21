#include "ant.hpp"

Ant::Ant(Instance* inst, RandomGenerator rg, Matrix<double>& proba): instance(inst), gen(rg), probabilities(proba){
	solution.resize(instance->getSize());
}

void Ant::clearSolution(){
	std::fill(solution.begin(), solution.end(), -1);
}

void Ant::assignFacility(int facility, std::vector<bool>& locationFree){
	std::vector<double> selectionProbability(instance->getSize(), 0.0);
	double sumProb, p = 0.0;


}

void Ant::constructSolution(){
	clearSolution();
	
	std::vector<int> unassignedFacilities(instance->getSize(), -1);
	std::vector<bool> locationFree(instance->getSize(), true);
	std::iota(unassignedFacilities.begin(), unassignedFacilities.end(), 0);
	int facility, index;

	for (unsigned int i = 0; i < instance->getSize(); i++){
		index = std::uniform_int_distribution<>(0, unassignedFacilities.size())(*gen);
		facility = unassignedFacilities[index];

		assignFacility(facility, locationFree);

		unassignedFacilities.erase(unassignedFacilities.begin()+index);
	}
}