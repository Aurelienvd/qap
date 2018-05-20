#include "colony.hpp"

Colony::Colony(Instance* inst, int size): instance(inst){
	for (int i = 0; i < size; i++){
		ants.push_back(Ant(inst));
	}
}