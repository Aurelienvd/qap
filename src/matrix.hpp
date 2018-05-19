#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <vector>
#include <iostream>

// Square matrix of size `size`.

class Matrix {

	private:
		std::size_t size;
		std::vector<int> mat;

	public:
		Matrix() = default;
		Matrix(std::size_t n);

		const int& getElem(int i, int j) const;
		void setElem(int i, int j, int elem);

		void resize(std::size_t newsize);
		
		void print() const;
};


#endif /* __MATRIX_HPP */