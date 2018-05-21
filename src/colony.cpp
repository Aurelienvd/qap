#include "colony.hpp"

Colony::Colony(Instance* inst, int size, double initial_pheromone): instance(inst){
	for (int i = 0; i < size; i++){
		ants.push_back(Ant(inst));
	}
	pheromones.resize(size);
	heuristic.resize(size);

	pheromones.setAllElem(initial_pheromone);
}