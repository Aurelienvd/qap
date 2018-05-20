#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
#include "instance.hpp"
#include "utils.hpp"

void testMatrix(){
	Matrix mat(3);
	mat.print();

	mat.setElem(1,1, 5);
	if (mat.getElem(1,1) == 5){
		std::cout << "Matrix setElem: OK" << std::endl;
	} else{
		std::cout << "Matrix setElem: NOK" << std::endl;
	}
}

void testInstance(){
	Instance instance("example.dat");
	instance.distance.print();
	instance.flow.print();

	std::vector<int> assignment = {0,1,2,3,4};
	long score = instance.evaluateSolution(assignment);

	printVec(assignment);
	std::cout << "Assignment score: " << score << std::endl;

	if (score == 374){
		std::cout << "Solution objective score: OK" << std::endl;
	} else{
		std::cout << "Solution objective score: NOK" << std::endl;
	}
}

int main(int argc, char** argv){
	testMatrix();
	testInstance();
	
	return EXIT_SUCCESS;
}