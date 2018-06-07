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
	int maxTours = 10000;
	std::string filename = "had14.dat";
	int seed = 1337;

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

long runMMAS(Parameters params){
	Instance instance(params.filename);
	int maxIter = params.maxIter == 0 ? params.maxTours/params.numAnts : params.maxIter;
	Colony colony(&instance, params.numAnts, 1.0, params.seed, params.rho);
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

	return colony.getBestScore();
}


int main(int argc, char** argv){
	auto params = parseArgs(argc, argv);
	params.numAnts = 25;
	params.beta = 1.1459;
	params.alpha = 0.315;
	params.rho = 0.4545;

	std::vector<std::string> instances = {"bur26g.dat", "chr15b.dat", "esc16d.dat", "had14.dat", "had20.dat", "nug28.dat", "scr12.dat", "tai17a.dat", "tai35a.dat", "wil50.dat"};
	std::vector<int> seeds = {265019260,692626528,125547936,1832295131,1318811903,170800164,233055788,1568515107,1004082759,119786407};
	std::cout << "Instance, Best, Worst, Mean, SD\n" << std::endl;

	for (unsigned int i = 0; i < instances.size(); i++){
		std::cout << instances[i] << ",";
		params.filename = instances[i];
		double mean = 0.0;
		double sd = 0.0;
		double best = DBL_MAX;
		double worst = DBL_MIN;
		std::vector<long> scores;
		for (unsigned int j = 0; j < seeds.size(); j++){
			params.seed = seeds[j];
			long score = runMMAS(params);
			if (score < best){
				best = score;
			}
			if (score > worst){
				worst = score;
			}
			scores.push_back(score);
			mean += score;
		}
		mean = mean/seeds.size();
		for (unsigned int k = 0; k < seeds.size(); k++){
			sd += pow((scores[k]-mean),2);
		}
		sd = sqrt(sd/(seeds.size()-1));
		std::cout << best << "," << worst << "," << mean << "," << sd << std::endl;
	}

	return EXIT_SUCCESS;
}