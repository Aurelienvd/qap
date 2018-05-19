#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
#include "instance.hpp"

int main(int argc, char** argv){

	Instance instance("had14.dat");
	instance.distance.print();
	instance.flow.print();
	
	return EXIT_SUCCESS;
}