#ifndef __COLONY_HPP
#define __COLONY_HPP

#include <vector>
#include "ant.hpp"
#include "instance.hpp"

class Colony {

	private:

		Instance* instance;
		std::vector<Ant> ants;
		Matrix<double> pheromones;
		Matrix<double> heuristic;

	public:

		Colony(Instance* inst, int size, double initial_pheromone);

		void initializeHeuristic();
};

#endif /* __COLONY_HPP */