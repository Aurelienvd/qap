#include "bwascolony.hpp"

BWColony::BWColony(Instance* inst, int size, double initial_pheromone, double seed, double r): Colony(inst, size, initial_pheromone, seed, r), p0(initial_pheromone) {}

void BWColony::resetPheromones(){
	pheromones.setAllElem(p0);
}

void BWColony::evaporatePheromones(){
	for (unsigned int i = 0; i < instance->getSize(); i++){
		for (unsigned int j = 0; j < instance->getSize(); j++){
			pheromones.setElem(i,j, (1.0-rho)*pheromones.getElem(i,j));
		}
	}
}

void BWColony::updatePheromones(const std::vector<int>& worstSolution){
	double delta = 1.0/bestScore;
	int j = -1;
	
	std::for_each(bestSolution.begin(), bestSolution.end(), [&j, this, &delta](const int &facility){
		++j;
		pheromones.setElem(facility, j, pheromones.getElem(facility, j)+delta);
	});

	j = -1;

	std::for_each(worstSolution.begin(), worstSolution.end(), [&j, this](const int &facility){
		++j;
		if (bestSolution[j] != facility){
			pheromones.setElem(facility, j, (1.0-rho)*pheromones.getElem(facility,j));
		}
	});
}

void BWColony::mutatePheromones(){

}

void BWColony::iterate(){
	Ant* bestAnt = nullptr;
	Ant* worstAnt = nullptr;
	long iterScore, currentScore = LONG_MAX;
	long worstScore = LONG_MIN;

	for (auto ant = ants.begin(); ant != ants.end(); ++ant){
		ant->constructSolution();
		currentScore = instance->evaluateSolution(ant->getSolution());
		if (currentScore < iterScore){
			bestAnt = &(*ant);
			iterScore = currentScore;
		}
		if (currentScore >= worstScore){
			worstAnt = &(*ant);
			worstScore = currentScore;
		}
	}

	if (iterScore < bestScore){
		bestScore = iterScore;
		bestSolution = bestAnt->getSolution();
	}

	evaporatePheromones();
	updatePheromones(worstAnt->getSolution());
}