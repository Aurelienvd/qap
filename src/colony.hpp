#ifndef __COLONY_HPP
#define __COLONY_HPP

#include <vector>
#include "ant.hpp"
#include "instance.hpp"

typedef std::vector<std::vector<double>> DoubleMatrix;

class Colony {

	private:

		Instance* instance;
		std::vector<Ant> ants;

	public:

		Colony(Instance* inst, int size);
};

#endif /* __COLONY_HPP */