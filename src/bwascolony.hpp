#ifndef __BWAS_HPP
#define __BWAS_HPP

#include "colony.hpp"

class BWColony: public Colony {

	private:
		double p0;
		int nt;
		double sigma;
		double mu;

		void evaporatePheromones() override;
		void updatePheromones(const std::vector<int>& worstSolution);

		double computePheromoneThreshold() const;
		double computeMutationDelta(int iter, int iterRestart, double threshold) const;
		void mutatePheromones(int iter, int iterRestart);

	public:
		BWColony(Instance* inst, int size, double initial_pheromone, double seed, double r, int nt, double s, double mu);
		virtual ~BWColony() = default;

		void resetPheromones() override;
		bool iterate(int iter = 0, int iterRestart = 0) override;


};

#endif /* __BWAS_HPP */