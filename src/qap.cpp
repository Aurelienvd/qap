#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cmath>
#include <cfloat>
#include "matrix.hpp"
#include "instance.hpp"
#include "utils.hpp"
#include "constants.hpp"
#include "colony.hpp"
#include "bwascolony.hpp"


struct Parameters{
	int numAnts = 10;
	double beta = 0.8;
	double alpha = 1.0;
	double rho = 0.2;
	double sigma = 4;
	double mu = 0.05;
	int maxIter = 0;
	int maxTours = 2000;
	std::string filename = "had14.dat";
	int seed = 1337;
	bool ls = false;
	bool mmas = true;

	void print(){
		std::cout << "ants: " << numAnts << std::endl;
		std::cout << "beta: " << beta << std::endl;
		std::cout << "alpha: " << alpha << std::endl;
		std::cout << "filename: " << filename << std::endl;
		std::cout << "seed: " << seed << std::endl;
	}
};

// This function comes from the first practical session of the swarm intelligence course at ULB.
Parameters parseArgs(int argc, char** argv){
	Parameters params;
    for(int i=1; i< argc ; i++){
       if(strcmp(argv[i], args::ANTS) == 0){
           params.numAnts = atol(argv[i+1]);
           i++;
       } else if(strcmp(argv[i], args::ALPHA) == 0){
           params.alpha = atof(argv[i+1]);
           i++;
       } else if(strcmp(argv[i], args::BETA) == 0){
           params.beta = atof(argv[i+1]);
           i++;
       } else if(strcmp(argv[i], args::RHO) == 0) {
           params.rho = atof(argv[i+1]);
           i++;
       } else if(strcmp(argv[i], args::SIGMA) == 0){
       	   params.sigma = atof(argv[i+1]);
       	   i++;
       } else if(strcmp(argv[i], args::MU) == 0){
       	   params.mu = atof(argv[i+1]);
       	   i++;
       } else if(strcmp(argv[i], args::MAXITER) == 0) {
           params.maxIter = atol(argv[i+1]);
           i++;
       } else if(strcmp(argv[i], args::MAXTOUR) == 0) {
           params.maxTours = atol(argv[i+1]);
           i++;
       } else if(strcmp(argv[i], args::SEED) == 0) {
           params.seed = atol(argv[i+1]);
           i++;
       }else if(strcmp(argv[i], args::FILENAME) == 0) {
           params.filename = argv[i+1];
           i++;
       } else if(strcmp(argv[i], args::LS) == 0){
       	   params.ls = true;
       	   i++;
       } else if(strcmp(argv[i], args::BWAS) == 0){
       	   params.mmas = false;
       	   i++;
       }
   }
   return params;
}

bool terminationCondition(Parameters params, int tour, int iter){
	if (params.maxTours != 0 && tour >= params.maxTours){
  		return(true);
	}
	if (params.maxIter !=0 && iter >= params.maxIter){
		return(true);
	}
	return(false);
}

void runMMAS(Parameters params){
	Instance instance(params.filename);
	Colony colony(&instance, params.numAnts, 1.0, params.seed, params.rho, params.ls);
	int tour = 0;
	int iter = 0;
	int iterLastRestart = 0;
	int noImprovement = 0;

	colony.initializeHeuristic();
	colony.computeProbabilities(params.alpha, params.beta);
	while(!terminationCondition(params, tour, iter)){
		bool improved = colony.iterate(iter, iterLastRestart);
		if (improved){
			noImprovement = 0;
		} else{
			noImprovement += 1;
			if (noImprovement == run::RESTART){
				colony.resetPheromones();
			}
		}

		tour += params.numAnts;

		colony.computeProbabilities(params.alpha, params.beta);
	}

	std::cout << "Best solution, cost: " << colony.getBestScore() << std::endl;
	printVec(colony.getBestSolution());
}

void runBWAS(Parameters params){
	Instance instance(params.filename);
	int maxIter = params.maxIter == 0 ? params.maxTours/params.numAnts : params.maxIter;
	BWColony colony(&instance, params.numAnts, 1.0, params.seed, params.rho, maxIter, params.sigma, params.mu);
	int tour = 0;
	int iter = 0;
	int iterLastRestart = 0;
	int noImprovement = 0;

	colony.initializeHeuristic();
	colony.computeProbabilities(params.alpha, params.beta);
	while(!terminationCondition(params, tour, iter)){
		bool improved = colony.iterate(iter, iterLastRestart);
		if (improved){
			noImprovement = 0;
		} else{
			noImprovement += 1;
			if (noImprovement == run::RESTART){
				colony.resetPheromones();
			}
		}

		tour += params.numAnts;

		colony.computeProbabilities(params.alpha, params.beta);
	}

	std::cout << "Best solution, cost: " << colony.getBestScore() << std::endl;
	printVec(colony.getBestSolution());
}


int main(int argc, char** argv){
	auto params = parseArgs(argc, argv);

	if(params.mmas){
		runMMAS(params);
	} else{
		runBWAS(params);
	}

	return EXIT_SUCCESS;
}