#ifndef __BWAS_HPP
#define __BWAS_HPP

#include "colony.hpp"

class BWColony: public Colony {

	private:
		double p0;

		void evaporatePheromones() override;
		void updatePheromones(const std::vector<int>& worstSolution);
		void mutatePheromones();

	public:
		BWColony(Instance* inst, int size, double initial_pheromone, double seed, double r);
		virtual ~BWColony() = default;

		void resetPheromones() override;
		void iterate() override;


};

#endif /* __BWAS_HPP */