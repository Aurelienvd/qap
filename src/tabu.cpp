#include "tabu.hpp"

// define static member variables.
Instance* RobustTabu::instance = nullptr;
Matrix<long> RobustTabu::moveCost = Matrix<long>();
Matrix<int> RobustTabu::tabuList = Matrix<int>();

void RobustTabu::initMatrices(){
	moveCost.resize(instance->getSize());
	tabuList.resize(instance->getSize());
	tabuList.setAllElem(0);
	moveCost.setAllElem(0);
}

void RobustTabu::deltaCost(uint r, uint s, std::vector<int> solution){
	Matrix<int>* b = &instance->flow;
	Matrix<int>* a = &instance->distance;

	long cost = (a->getElem(s,s)-a->getElem(r,r))*(b->getElem(solution[r], solution[r])-b->getElem(solution[s], solution[s]))+
	            (a->getElem(s,r)-a->getElem(r,s))*(b->getElem(solution[r], solution[s])-b->getElem(solution[s], solution[r]));

	for (uint k = 0; k < instance->getSize(); k++){
		if (k != r and k != s){
			cost += ((a->getElem(s,k)-a->getElem(r,k))*(b->getElem(solution[r], solution[k])-b->getElem(solution[s], solution[k]))+
				     (a->getElem(k,s)-a->getElem(k,r))*(b->getElem(solution[k], solution[r])-b->getElem(solution[k], solution[s])));
		}
	}
	moveCost.setElem(r, s, cost);
}

void RobustTabu::fastDeltaCost(uint u, uint v, uint r, uint s, std::vector<int> solution){
	Matrix<int>* b = &instance->flow;
	Matrix<int>* a = &instance->distance;

	long cost = moveCost.getElem(u, v);

	cost += (b->getElem(solution[r], solution[u])-b->getElem(solution[r], solution[v])+b->getElem(solution[s], solution[v])-b->getElem(solution[s], solution[u])) *
	        (a->getElem(s,u)-a->getElem(s,v)+a->getElem(r,v)-a->getElem(r,u)) + 
	        (b->getElem(solution[u], solution[r])-b->getElem(solution[v], solution[r])+b->getElem(solution[v], solution[s])-b->getElem(solution[u], solution[s])) *
	        (a->getElem(u,s)-a->getElem(v,s)+a->getElem(v,r)-a->getElem(u,r));

	moveCost.setElem(u,v, cost);
}

void RobustTabu::computeInitCosts(std::vector<int> solution){
	for (uint r = 0; r < instance->getSize(); r++){
		for (uint s = 0; s < instance->getSize(); s++){
			deltaCost(r, s, solution);
		}
	}
}

void RobustTabu::computeCosts(std::vector<int> solution, Move lastMove){
	for (uint u = 0; u < instance->getSize(); u++){
		for (uint v = 0; v < instance->getSize(); v++){
			if (u != lastMove.r and u != lastMove.s and v != lastMove.r and v != lastMove.s){
				fastDeltaCost(u, v, lastMove.r, lastMove.s, solution);
			} else{
				deltaCost(u, v, solution);
			}
		}
	}
}

// Returns True if the facilities at solution[r] and solution[s] have been placed to location r and s in the last tt iterations.
bool RobustTabu::isTabu(uint r, uint s, int tt, int iter, std::vector<int> solution){
	int tabuThresholdR = iter - tabuList.getElem(solution[r], r);
	int tabuThresholdS = iter - tabuList.getElem(solution[s], s);

	if (tabuThresholdR >= tt &&  tabuThresholdS >= tt){
		return false;
	}
	return true;
}

Move RobustTabu::getBestMove(int iter, int tt, std::vector<int> solution, long bestScore, long currentScore){
	Move bestMove = Move(0,0);
	long bestCost = LONG_MAX;

	for (uint r = 0; r < instance->getSize(); r++){
		for (uint s = r+1; s < instance->getSize(); s++){
			if (!isTabu(r, s, tt, iter, solution) or (currentScore + moveCost.getElem(r, s) < bestScore)){
				if (moveCost.getElem(r, s) < bestCost){
					bestMove = Move(r, s);
					bestCost = moveCost.getElem(r, s);
				} 
			}
		}
	}

	return bestMove;
}

void RobustTabu::updateTabuList(Move move, std::vector<int> solution, int iter){
	tabuList.setElem(solution[move.r], move.r, iter);
	tabuList.setElem(solution[move.s], move.s, iter);
}


std::vector<int> RobustTabu::search(std::vector<int> solution, Instance* inst, RandomGenerator gen, long bestScore){
	instance = inst;
	long currentScore = instance->evaluateSolution(solution);
	initMatrices();
	computeInitCosts(solution);
	int iter = 0;
	auto dis = std::uniform_int_distribution<>((int)std::floor(inst->getSize()*0.9), (int)std::ceil(inst->getSize()*1.1));
	int tt = dis(*gen);
	bool stopped = false;
	std::vector<int> bestSolution = solution;

	while (iter < 500 and !stopped){
		auto move = getBestMove(iter, tt, solution, bestScore, currentScore);
		std::iter_swap(solution.begin()+move.r, solution.begin()+move.s);

		currentScore = currentScore + moveCost.getElem(move.r, move.s);
		if (currentScore < bestScore){
			bestScore = currentScore;
			bestSolution = solution;
		}

		updateTabuList(move, solution, iter);
		computeCosts(solution, move);
		++iter;
		tt = iter % (2*(int)(inst->getSize()*1.1)) ? dis(*gen) : tt;
		stopped = move.r == move.s;		// Check if no bestMove was found in getBestMove.
	}

	return bestSolution;

}
