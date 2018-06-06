#ifndef __TABU_SEARCH_HPP
#define __TABU_SEARCH_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include "matrix.hpp"
#include "instance.hpp"

/*
* Robust Tabu Search based on paper published in 1990 by E. Talliard. deltaCost corresponds to Eq. 1 and fastDelta cost to Eq. 2 in said paper.
*/

typedef unsigned int uint;
typedef std::shared_ptr<std::mt19937> RandomGenerator;

struct Move{
	uint r;
	uint s;
};	


class RobustTabu{

	private:

		static Matrix<long> moveCost;
		static Matrix<long> previousCost;
		static Matrix<int> tabuList;
		static Instance* instance;

		static void deltaCost(uint r, uint s, std::vector<int> solution);
		static void fastDeltaCost(uint u, uint v, uint r, uint s, std::vector<int> solution);
		static void computeInitCosts(std::vector<int> solution);
		static void initMatrices();
		static bool isTaboo(int r, int s, int tt);
		static Move getBestMove(int iter, int tt);


	public:

		static std::vector<int> search(std::vector<int> solution, Instance* inst, RandomGenerator gen);



};



#endif /*  __TABU_SEARCH_HPP */
