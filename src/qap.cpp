#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
#include "instance.hpp"
#include "utils.hpp"

int main(int argc, char** argv){

	Instance instance("example.dat");
	instance.distance.print();
	instance.flow.print();

	std::vector<int> assignment = {0,1,2,3,4};
	long score = instance.evaluateSolution(assignment);

	printVec(assignment);
	std::cout << "Assignment score: " << score << std::endl;
	
	return EXIT_SUCCESS;
}