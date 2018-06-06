#include <iostream>
#include <cstdlib>
#include <random>
#include <memory>
#include <algorithm>
#include "matrix.hpp"
#include "instance.hpp"
#include "utils.hpp"
#include "colony.hpp"
#include "tabu.hpp"

void testMatrix(){
	Matrix<int> mat(3);
	mat.print();

	mat.setElem(1,1, 5);
	if (mat.getElem(1,1) == 5){
		std::cout << "Matrix setElem: OK" << std::endl;
	} else{
		std::cout << "Matrix setElem: NOK" << std::endl;
	}

	printVec(mat.getLine(1));

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

void testUtils(){
	std::vector<int> v1 = {1,2,3,4,5,6,7,8,9,10};

	inplace_scanl(v1.begin(), v1.end(), 0, [](int acc, int val){
		if (val%2 == 0){
			return acc+val;
		}
		return 0;
	});
	if (*(v1.end()-1) == 30){
		std::cout << "inplace_scanl: OK" << std::endl;
	} else{
		std::cout << "inplace_scanl: NOK" << std::endl;
	}
	
}

void testInstance(){
	Instance instance("example.dat");
	instance.distance.print();
	instance.flow.print();

	std::vector<int> assignment = {0,1,2,3,4};
	std::vector<int> bestAssignment = {1,3,4,2,0};
	long score = instance.evaluateSolution(assignment);
	long bestScore = instance.evaluateSolution(bestAssignment);

	printVec(assignment);
	std::cout << "Assignment score: " << score << std::endl;

	if (score == 374 and bestScore == 258){
		std::cout << "Solution objective score: OK" << std::endl;
	} else{
		std::cout << "Solution objective score: NOK" << std::endl;
	}
}

void testColony(){
	Instance instance("example.dat");
	Colony colony(&instance, 10, 0.8, 1337, 0.2);
	colony.initializeHeuristic();
	colony.computeProbabilities(1.0, 1.0);

	colony.getHeuristicMatrix().print();
	std::cout<<std::endl;
	colony.getProbabilitiesMatrix().print();

	colony.iterate();
}

void testTabu(){
	Instance instance("example.dat");
	std::vector<int> solution = {0,1,2,3,4};
	long bestScore = instance.evaluateSolution(solution);
	auto gen = std::make_shared<std::mt19937>(1337);

	std::cout << "Initial solution, score: " << bestScore << std::endl;
	printVec(solution);
	solution = RobustTabu::search(solution, &instance, gen, bestScore);
	std::cout << "Post tabu solution, score: " << instance.evaluateSolution(solution) << std::endl;
	printVec(solution);

	for (unsigned int i = 0; i < instance.getSize(); i++){
		for (unsigned int j = i+1; j < instance.getSize(); j++){
			std::cout << "Move: " << i << "," << j << std::endl;
			std::iter_swap(solution.begin()+i, solution.begin()+j);
			std::cout << "Final cost: " << instance.evaluateSolution(solution) << std::endl;
			std::iter_swap(solution.begin()+i, solution.begin()+j);
			std::cout << std::endl;
		}
	}


}

int main(int argc, char** argv){
	std::cout << "\nTest Unit: Matrix class\n" << std::endl;
	testMatrix();
	std::cout << "\nTest Unit: Utils module\n" << std::endl;
	testUtils();
	std::cout << "\nTest Unit: Instance class\n" << std::endl;
	testInstance();
	std::cout << "\nTest Unit: Colony class\n" << std::endl;
	testColony();
	std::cout << "\nTest Unit: Tabu search\n" << std::endl;
	testTabu();
	
	return EXIT_SUCCESS;
}