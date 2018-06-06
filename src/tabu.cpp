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
		for (uint s = r; s < instance->getSize(); s++){
			deltaCost(r, s, solution);
			previousCost.setTriangularElem(r, s, moveCost.getElem(r, s));
		}
	}
}

bool RobustTabu::isTaboo(int r, int s, int tt){
	return true;
}

Move RobustTabu::getBestMove(int iter, int tt){
	Move bestMove;
	long bestCost;
	for (uint r = 0; r < instance->getSize(); r++){
		for (uint s = 0; s < instance->getSize(); s++){

		}
	}
	return bestMove;
}


std::vector<int> RobustTabu::search(std::vector<int> solution, Instance* inst, RandomGenerator gen){
	instance = inst;
	initMatrices();
	computeInitCosts(solution);
	int iter = 0;
	auto dis = std::uniform_int_distribution<>((int)(inst->getSize()*0.9), (int)(inst->getSize()*1.1));
	int tt = dis(*gen);

	while (iter < 100){
		auto move = getBestMove(iter, tt);
		++iter;
		tt = iter % (2*(int)(inst->getSize()*1.1)) ? dis(*gen) : tt; 
	}

	return solution;

}
