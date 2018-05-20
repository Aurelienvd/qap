#ifndef __INSTANCE_HPP
#define __INSTANCE_HPP

#include <fstream>
#include <string>
#include <unordered_map>

#include "matrix.hpp"
#include "constants.hpp"

typedef std::unordered_map<int, int> Table;

class Instance{
	
	private:
		void initMatrix(std::ifstream& in, Matrix& mat, std::size_t n);
		void readMatricesFromFile(std::string filename);
		Table tableFromVector(std::vector<int> assignment) const;

	public:
		Matrix distance;
		Matrix flow;

		Instance() = default;
		Instance(std::string filename);

		long evaluateSolution(std::vector<int> assignment) const;
};


#endif /* __INSTANCE_HPP */