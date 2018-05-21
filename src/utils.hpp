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

template <class InputIt, class T, class BinaryOperation>
void inplace_scanl(InputIt first, InputIt last, T init, BinaryOperation op){
	auto val = init;
	for(auto current = first; current != last; ++current){
		*current = op(val, *current);
		val = *current == 0 ? val : *current;		
	}
}



#endif /* __UTILS_HPP */