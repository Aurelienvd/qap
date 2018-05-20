#include "ant.hpp"

Ant::Ant(Instance* inst): instance(inst){
	solution.resize(instance->getSize());
}