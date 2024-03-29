#ifndef __ANT_HPP
#define __ANT_HPP

#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include <numeric>
#include <cfloat>
#include "matrix.hpp"
#include "instance.hpp"
#include "utils.hpp"
#include "tabu.hpp"

typedef std::vector<int> Assignment;
typedef std::shared_ptr<std::mt19937> RandomGenerator;

class Ant{

	private:
		
		Assignment solution;
		Instance* instance;
		RandomGenerator gen;
		Matrix<double>* probabilities;
		Matrix<double>* heuristic;

		bool locals;

		void clearSolution();
		void assignBestLocation(int facility, std::vector<bool>& locationFree);
		void assignFacility(int facility, std::vector<bool>& locationFree);

	public:

		Ant(Instance* inst, RandomGenerator rg, Matrix<double>* proba, Matrix<double>* h, bool ls);

		void constructSolution(long bestScore);
		const Assignment& getSolution() const;
};

#endif /* __ANT_HPP */