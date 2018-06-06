#include "bwascolony.hpp"

BWColony::BWColony(Instance* inst, int size, double initial_pheromone, double seed, double r, int nt, double s, double mu): 
                   Colony(inst, size, initial_pheromone, seed, r), p0(initial_pheromone), nt(nt), sigma(s), mu(mu) {}

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

double BWColony::computePheromoneThreshold() const{
	double threshold = 0.0;
	for (unsigned int i = 0; i < instance->getSize(); i++){
		threshold += pheromones.getElem(bestSolution[i], i);
	}
	return threshold/instance->getSize();
}

double BWColony::computeMutationDelta(int iter, int iterRestart, double threshold) const{
	double delta = ((double)(iter-iterRestart))/(nt-iterRestart);
	delta = delta*sigma*threshold;
	return delta;
}

// mapping01 defined in utils.cpp
void BWColony::mutatePheromones(int iter, int iterRestart){
	double delta = computeMutationDelta(iter, iterRestart, computePheromoneThreshold());
	auto signDis = std::uniform_int_distribution<>();
	auto mutDis = std::uniform_real_distribution<>();

	for (unsigned int i = 0; i < instance->getSize(); i++){
		for (unsigned int j = 0; j < instance->getSize(); j++){
			double p = mutDis(*gen);
			if (p <= mu){
				int a = signDis(*gen);
				pheromones.setElem(i, j, pheromones.getElem(i, j) + delta*mapping01<int>(a));
			}
		}
	}
}

bool BWColony::iterate(int iter, int iterRestart){
	Ant* bestAnt = nullptr;
	Ant* worstAnt = nullptr;
	long iterScore, currentScore = LONG_MAX;
	long worstScore = LONG_MIN;
	bool improved = false;

	for (auto ant = ants.begin(); ant != ants.end(); ++ant){
		ant->constructSolution(bestScore);
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
		improved = true;
	}

	evaporatePheromones();
	updatePheromones(worstAnt->getSolution());
	mutatePheromones(iter, iterRestart);

	return improved;
}