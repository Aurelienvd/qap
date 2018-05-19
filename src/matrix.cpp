#include "matrix.hpp"

Matrix::Matrix(std::size_t n): size(n), mat(std::vector<int>(n*n, 0)){}

const int& Matrix::getElem(int i, int j) const{
	return mat[i*size+j];
}

void Matrix::setElem(int i, int j, int elem){
	mat[i*size+j] = elem;
}

void Matrix::print() const{
	unsigned int count = 0;
	for (auto elem : mat){
		std::cout << elem << " ";
		count++;
		if (count == size){
			std::cout << std::endl;
			count = 0;
		}
	}
	std::cout << std::endl;
}