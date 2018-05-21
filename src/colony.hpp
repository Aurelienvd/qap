#ifndef __COLONY_HPP
#define __COLONY_HPP

#include <vector>
#include <numeric>
#include <cmath>
#include <random>
#include "ant.hpp"
#include "instance.hpp"
#include "utils.hpp"

class Colony {

	private:

		Instance* instance;
		std::vector<Ant> ants;
		Matrix<double> pheromones;
		Matrix<double> heuristic;
		Matrix<double> probabilities;

	public:

		Colony(Instance* inst, int size, double initial_pheromone, double seed);

		const Matrix<double>& getHeuristicMatrix() const;
		const Matrix<double>& getProbabilitiesMatrix() const;
		const Matrix<double>& getPheromonesMatrix() const;

		void initializeHeuristic();
		void computeProbabilities(double alpha, double beta);
};

#endif /* __COLONY_HPP */