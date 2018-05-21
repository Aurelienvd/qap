#include "colony.hpp"
#include <iostream>

Colony::Colony(Instance* inst, int size, double initial_pheromone, double seed): instance(inst){
	auto rg = std::make_shared<std::mt19937>(seed);
	for (int i = 0; i < size; i++){
		ants.push_back(Ant(inst, rg, probabilities, heuristic));
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

void Colony::computeProbabilities(double alpha, double beta){
	for (unsigned int i = 0; i < instance->getSize(); i++){
		for (unsigned int j = 0; j < instance->getSize(); j++){
			probabilities.setElem(i,j, std::pow(pheromones.getElem(i,j), alpha)*std::pow(heuristic.getElem(i,j), beta));
		}
	}
}