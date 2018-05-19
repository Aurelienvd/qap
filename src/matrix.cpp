#include "matrix.hpp"

Matrix::Matrix(std::size_t n): size(n), mat(std::vector<int>(n*n, 0)){}


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
}