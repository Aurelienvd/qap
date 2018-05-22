#include "colony.hpp"
#include <iostream>

Colony::Colony(Instance* inst, int size, double initial_pheromone, double seed, double r): instance(inst), rho(r), bestScore(LONG_MAX), 
                                                                                           bestSolution(std::vector<int>(inst->getSize(), -1)){
	auto rg = std::make_shared<std::mt19937>(seed);
	for (int i = 0; i < size; i++){
		ants.push_back(Ant(inst, rg, &probabilities, &heuristic));
	}
	pheromones.resize(instance->getSize());
	heuristic.resize(instance->getSize());
	probabilities.resize(instance->getSize());

	pheromones.setAllElem(initial_pheromone);
}

const Matrix<double>& Colony::getHeuristicMatrix() const{
	return heuristic;
}

const Matrix<double>& Colony::getProbabilitiesMatrix() const{
	return probabilities;
}

const Matrix<double>& Colony::getPheromonesMatrix() const{
	return pheromones;
}

void Colony::initializeHeuristic(){
	std::vector<int> total_flows(instance->getSize(), 0);
	std::vector<int> total_distances(instance->getSize(), 0);

	for (unsigned int i = 0; i < instance->getSize(); i++){
		auto flowline = instance->flow.getLine(i);
		auto distanceline = instance->distance.getLine(i);

		total_flows[i] = std::accumulate(flowline.begin(), flowline.end(), 0);
		total_distances[i] = std::accumulate(distanceline.begin(), distanceline.end(), 0);
	}

	for (unsigned int i = 0; i < instance->getSize(); i++){
		for (unsigned int j = 0; j < instance->getSize(); j++){
			heuristic.setElem(i, j, 1.0/(total_flows[i]*total_distances[j]));
		}
	}
}

void Colony::evaporatePheromones(){
	for (unsigned int i = 0; i < instance->getSize(); i++){
		for (unsigned int j = 0; j < instance->getSize(); j++){
			pheromones.setElem(i,j,std::clamp((1.0-rho)*pheromones.getElem(i,j), lowerLimit, upperLimit));
		}
	}
}

void Colony::updateTrailLimits(){
	upperLimit = (1.0/rho)*(1.0/bestScore);
	lowerLimit = upperLimit/(2.0*instance->getSize());
}

void Colony::depositPheromones(long iterScore, const std::vector<int>& solution){
	double delta = 1.0/iterScore;
	int j = -1;
	std::for_each(solution.begin(), solution.end(), [&j, this, &delta](const int &facility){
		++j;
		pheromones.setElem(facility, j, std::clamp(pheromones.getElem(facility, j)+delta, lowerLimit, upperLimit));
	});
}

void Colony::computeProbabilities(double alpha, double beta){
	for (unsigned int i = 0; i < instance->getSize(); i++){
		for (unsigned int j = 0; j < instance->getSize(); j++){
			probabilities.setElem(i,j, std::pow(pheromones.getElem(i,j), alpha)*std::pow(heuristic.getElem(i,j), beta));
		}
	}
}

void Colony::iterate(){
	Ant* bestAnt = nullptr;
	long iterScore, currentScore = LONG_MAX;

	for (auto ant = ants.begin(); ant != ants.end(); ++ant){
		ant->constructSolution();
		currentScore = instance->evaluateSolution(ant->getSolution());
		if (currentScore < iterScore){
			bestAnt = &(*ant);
			iterScore = currentScore;
		}
	}

	if (iterScore < bestScore){
		bestScore = iterScore;
		bestSolution = bestAnt->getSolution();
	}

	updateTrailLimits();
	evaporatePheromones();
	depositPheromones(iterScore, bestAnt->getSolution());
}