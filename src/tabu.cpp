#include "tabu.hpp"

// define static member variables.
Instance* RobustTabu::instance = nullptr;
Matrix<long> RobustTabu::moveCost = Matrix<long>();
Matrix<long> RobustTabu::previousCost = Matrix<long>();
Matrix<int> RobustTabu::tabuList = Matrix<int>();

void RobustTabu::initMatrices(){
	moveCost.resize(instance->getSize());
	previousCost.resize(instance->getSize());
	tabuList.resize(instance->getSize());
	tabuList.setAllElem(0);
}

void RobustTabu::deltaCost(uint r, uint s, std::vector<int> solution){
	long cost = 0;
	for (uint k = 0; k < instance->getSize(); k++){
		if (k != r and k != s){
			cost += (instance->distance.getElem(s,k)-instance->distance.getElem(r,k))*(
				     instance->flow.getElem(solution[s], solution[k])-instance->flow.getElem(solution[r], solution[k]));
		}
	}
	moveCost.setTriangularElem(r, s, 2*cost);
}

void RobustTabu::fastDeltaCost(uint u, uint v, uint r, uint s, std::vector<int> solution){
	long cost = previousCost.getElem(u, v);
	cost += 2*(instance->distance.getElem(r,u)-instance->distance.getElem(r,v)+instance->distance.getElem(s,v)-instance->distance.getElem(s,u))*
		      (instance->flow.getElem(solution[s], solution[u])-instance->flow.getElem(solution[s], solution[v]) + 
		       instance->flow.getElem(solution[r], solution[v])-instance->flow.getElem(solution[r], solution[u]));
	moveCost.setTriangularElem(u,v, cost);
}

void RobustTabu::computeInitCosts(std::vector<int> solution){
	for (uint r = 0; r < instance->getSize(); r++){
		for (uint s = r+1; s < instance->getSize(); s++){
			deltaCost(r, s, solution);
			previousCost.setTriangularElem(r, s, moveCost.getElem(r, s));
		}
	}
}

// Returns True if the facilities at solution[r] and solution[s] have not been placed to location r and s in the last tt iterations.
bool RobustTabu::isTabu(uint r, uint s, int tt, int iter, std::vector<int> solution){
	int tabuThreshold = iter - tt;
	if (tabuList.getElem(solution[r], r) < tabuThreshold && tabuList.getElem(solution[s], s) < tabuThreshold){
		return false;
	}
	return true;
}

Move RobustTabu::getBestMove(int iter, int tt, std::vector<int> solution, long bestScore, long currentScore){
	Move bestMove = Move(-1,-1);
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
	auto dis = std::uniform_int_distribution<>((int)(inst->getSize()*0.9), (int)(inst->getSize()*1.1));
	int tt = dis(*gen);

	while (iter < 500){
		auto move = getBestMove(iter, tt, solution, bestScore, currentScore);
		std::iter_swap(solution.begin()+move.r, solution.begin()+move.s);
		currentScore = currentScore + moveCost.getElem(move.r, move.s);
		
		bestScore = currentScore < bestScore ? currentScore : bestScore;
		++iter;

		updateTabuList(move, solution, iter);
		tt = iter % (2*(int)(inst->getSize()*1.1)) ? dis(*gen) : tt; 
	}

	return solution;

}
