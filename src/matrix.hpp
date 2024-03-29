#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <vector>
#include <iostream>

// size*size matrix with numerical values.

template <typename Num>
class Matrix {

	private:
		std::size_t size;
		std::vector<Num> mat;

	public:
		Matrix() = default;
		Matrix(std::size_t n): size(n), mat(std::vector<Num>(n*n, 0)){}

		const Num& getElem(int i, int j) const{
			return mat[i*size+j];
		}

		const std::vector<Num>getLine(int i) const{
			return std::vector<Num>(mat.begin()+(i*size), mat.begin()+(i*size)+size);
		}


		void setElem(int i, int j, Num elem){
			mat[i*size+j] = elem;
		}

		void setTriangularElem(int i, int j, Num elem){
			setElem(i, j, elem);
			setElem(j, i, elem);
		}

		void setAllElem(Num elem){
			mat.assign(mat.size(), elem);
		}

		unsigned int getSize() const{
			return size;
		}

		void resize(std::size_t newsize){
			mat.resize(newsize*newsize);
			size = newsize;
		}
		
		void print() const{
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
};


#endif /* __MATRIX_HPP */