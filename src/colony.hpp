#ifndef __COLONY_HPP
#define __COLONY_HPP

#include <vector>
#include <numeric>
#include <cmath>
#include <climits>
#include <algorithm>
#include <random>
#include "ant.hpp"
#include "instance.hpp"
#include "utils.hpp"

/*
* Class implementing a MINMAX Ant System.
*/

class Colony {

	protected:

		Instance* instance;
		std::vector<Ant> ants;
		Matrix<double> pheromones;
		Matrix<double> heuristic;
		Matrix<double> probabilities;

		RandomGenerator gen;

		double rho;
		double lowerLimit;
		double upperLimit;

		long bestScore;
		std::vector<int> bestSolution;

		virtual void evaporatePheromones();
		void updateTrailLimits();
		void depositPheromones(long iterScore, const std::vector<int>& solution);

	public:

		Colony(Instance* inst, int size, double initial_pheromone, double seed, double r, bool ls);
		virtual ~Colony() = default;

		const Matrix<double>& getHeuristicMatrix() const;
		const Matrix<double>& getProbabilitiesMatrix() const;
		const Matrix<double>& getPheromonesMatrix() const;
		const long getBestScore() const;
		const std::vector<int>& getBestSolution() const;

		void initializeHeuristic();
		void computeProbabilities(double alpha, double beta);
		virtual void resetPheromones();
		virtual bool iterate(int iter = 0, int iterRestart = 0);
};

#endif /* __COLONY_HPP */