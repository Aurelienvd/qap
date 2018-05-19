#ifndef __INSTANCE_HPP
#define __INSTANCE_HPP

#include <fstream>
#include <string>

#include "matrix.hpp"
#include "constants.hpp"

class Instance{
	
	private:
		void initMatrix(std::ifstream& in, Matrix& mat, std::size_t n);
		void readMatricesFromFile(std::string filename);

	public:
		Matrix distance;
		Matrix flow;

		Instance() = default;
		Instance(std::string filename);
};


#endif /* __INSTANCE_HPP */