#include "instance.hpp"
#include <iostream>

Instance::Instance(std::string filename){
	readMatricesFromFile(filename);
}

void Instance::initMatrix(std::ifstream& in, Matrix<int>& mat, std::size_t n){
	int elem;
	for (unsigned int i = 0; i < n; i++){
		for (unsigned int j = 0; j < n; j++){
			in >> elem;
			mat.setElem(i, j, elem);
		}
	}
}

void Instance::readMatricesFromFile(std::string filename){
	std::ifstream f(std::string(io::DIR)+filename);
	if (f.is_open()){
		unsigned int n;
		f >> n;
		distance.resize(n);
		flow.resize(n);
		initMatrix(f, distance, n);
		initMatrix(f, flow, n);
	}
}

unsigned int Instance::getSize() const{
	return distance.getSize();
}

long Instance::evaluateSolution(const std::vector<int>& assignment) const{
	long score = 0;
	for (unsigned int i = 0; i < assignment.size(); i++){
		for (unsigned int j = 0; j < assignment.size(); j++){
			score += flow.getElem(assignment[i], assignment[j])*distance.getElem(i,j);
		}
	}
	return score;
}