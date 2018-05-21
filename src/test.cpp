#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
#include "instance.hpp"
#include "utils.hpp"

void testMatrix(){
	Matrix<int> mat(3);
	mat.print();

	mat.setElem(1,1, 5);
	if (mat.getElem(1,1) == 5){
		std::cout << "Matrix setElem: OK" << std::endl;
	} else{
		std::cout << "Matrix setElem: NOK" << std::endl;
	}

	mat.setAllElem(7);
	bool valid = true;
	for (unsigned int i = 0; i < mat.getSize() && valid; i++){
		for (unsigned int j = 0; j < mat.getSize() && valid; j++){
			if (mat.getElem(i, j) != 7){
				valid = false;
			}
		}
	}
	if (valid){
		std::cout << "Matrix setAllElem: OK" << std::endl;
	} else{
		std::cout << "Matrix setAllElem: NOK" << std::endl;
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