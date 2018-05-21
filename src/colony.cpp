#include "colony.hpp"
#include <iostream>

Colony::Colony(Instance* inst, int size, double initial_pheromone): instance(inst){
	for (int i = 0; i < size; i++){
		ants.push_back(Ant(inst));
	}
	pheromones.resize(instance->getSize());
	heuristic.resize(instance->getSize());

	pheromones.setAllElem(initial_pheromone);
}

const Matrix<double>& Colony::getHeuristicMatrix() const{
	return heuristic;
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