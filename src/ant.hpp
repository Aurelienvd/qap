#ifndef __ANT_HPP
#define __ANT_HPP

#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include <numeric>
#include "matrix.hpp"
#include "instance.hpp"

typedef std::vector<int> Assignment;
typedef std::shared_ptr<std::mt19937> RandomGenerator;

class Ant{

	private:
		
		Assignment solution;
		Instance* instance;
		RandomGenerator gen;
		Matrix<double> probabilities;

		void clearSolution();
		void assignFacility(int facility, std::vector<bool>& locationFree);

	public:

		Ant(Instance* inst, RandomGenerator rg, Matrix<double>& proba);

		void constructSolution();
};

#endif /* __ANT_HPP */