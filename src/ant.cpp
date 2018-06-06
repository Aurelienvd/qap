#include "ant.hpp"

Ant::Ant(Instance* inst, RandomGenerator rg, Matrix<double>* proba, Matrix<double>* h): instance(inst), gen(rg), probabilities(proba), heuristic(h){
	solution.resize(instance->getSize());
}

void Ant::clearSolution(){
	std::fill(solution.begin(), solution.end(), -1);
}

const std::vector<int>& Ant::getSolution() const{
	return solution;
}

void Ant::assignBestLocation(int facility, std::vector<bool>& locationFree) {
	int index = 0;
	double minimum = DBL_MAX;
	auto weights = heuristic->getLine(facility);

	for (unsigned int i = 0; i < instance->getSize(); i++){
		if (locationFree[i] && weights[i] < minimum){
			minimum = weights[i];
			index = i;
		}
	}
	locationFree[index] = false;
	solution[index] = facility;
}

/*
* scanl function defined in "utils.hpp".
*/
void Ant::assignFacility(int facility, std::vector<bool>& locationFree){
	auto proba = probabilities->getLine(facility);
	double sumProb, p = 0.0;
	int i = -1;

	auto selectionProbability = scanl(proba.begin(), proba.end(), 0.0, [&i, &locationFree, &sumProb](double acc, double val){
		++i;
		if (locationFree[i]){
			sumProb = acc+val;
			return sumProb;
		} else{
			return 0.0;
		}
	});

	if (sumProb == 0.0){
		assignBestLocation(facility, locationFree);
	} else{
		p = std::uniform_real_distribution<>()(*gen)*sumProb;
		i = 0;
		while (p > selectionProbability[i]){
			i++;
		}
		locationFree[i] = false;
		solution[i] = facility;
	}
}

void Ant::constructSolution(long bestScore){
	clearSolution();
	std::vector<int> unassignedFacilities(instance->getSize(), -1);
	std::vector<bool> locationFree(instance->getSize(), true);
	std::iota(unassignedFacilities.begin(), unassignedFacilities.end(), 0);
	int facility, index;

	for (unsigned int i = 0; i < instance->getSize(); i++){
		index = std::uniform_int_distribution<>(0, unassignedFacilities.size()-1)(*gen);
		facility = unassignedFacilities[index];

		assignFacility(facility, locationFree);
		unassignedFacilities.erase(unassignedFacilities.begin()+index);
	}
	solution = RobustTabu::search(solution, instance, gen, bestScore);
}