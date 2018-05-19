#ifndef __INSTANCE_HPP
#define __INSTANCE_HPP

#include <iostream>
#include <string>

#include "matrix.hpp"

class Instance{

	private:
		Matrix distance;
		Matrix flow;

		void readMatricesFromFile(std::string filename);

	public:
		Instance(std::string filename);
};


#endif /* __INSTANCE_HPP */