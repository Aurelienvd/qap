#include <iostream>
#include <cstdlib>
#include "matrix.hpp"

int main(int argc, char** argv){

	Matrix mat(3);
	mat.print();

	mat.setElem(1,1, 5);
	mat.print();
	std::cout << mat.getElem(1,2) << std::endl;
	
	return EXIT_SUCCESS;
}