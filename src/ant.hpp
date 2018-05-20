#ifndef __ANT_HPP
#define __ANT_HPP

#include <vector>
#include "matrix.hpp"
#include "instance.hpp"

typedef std::vector<int> Assignment;

class Ant{

	private:
		
		Assignment solution;
		Instance* instance;

	public:

		Ant(Instance* inst);


};

#endif /* __ANT_HPP */