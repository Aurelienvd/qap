#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <vector>
#include <iostream>

template <typename T>
void printVec(std::vector<T> vec){
	for (auto elem : vec){
		std::cout << elem << ",";
	}
	std::cout << std::endl;
}


#endif /* __UTILS_HPP */