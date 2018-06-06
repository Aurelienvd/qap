#ifndef __TABU_SEARCH_HPP
#define __TABU_SEARCH_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include <climits>
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

	Move(uint a, uint b): r(a), s(b) {}
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
		static bool isTabu(uint r, uint s, int tt, int iter, std::vector<int> solution);
		static Move getBestMove(int iter, int tt, std::vector<int> solution, long bestScore, long currentScore);
		static void updateTabuList(Move move, std::vector<int> solution, int iter);


	public:

		static std::vector<int> search(std::vector<int> solution, Instance* inst, RandomGenerator gen, long bestScore);



};



#endif /*  __TABU_SEARCH_HPP */
