#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include "matrix.hpp"
#include "instance.hpp"
#include "utils.hpp"
#include "constants.hpp"


struct Parameters{
	int numAnts = 10;
	double beta = 0.8;
	double alpha = 1.0;
	double rho = 0.2;
	int maxIter = 0;
	int maxTours = 10000;
	std::string filename = "had14.dat";
	int seed = 1337;

	void print(){
		std::cout << "ants: " << numAnts << std::endl;;
	}
};

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

int main(int argc, char** argv){
	auto params = parseArgs(argc, argv);

	return EXIT_SUCCESS;
}