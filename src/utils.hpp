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

/*
* inplace version of scanl.
*/
template <class InputIt, class T, class BinaryOperation>
void inplace_scanl(InputIt first, InputIt last, T init, BinaryOperation op){
	auto val = init;
	for(auto current = first; current != last; ++current){
		*current = op(val, *current);
		val = *current == 0 ? val : *current;		
	}
}

/*
* scanl behaves like a left fold, only it returns a vector of intermediate values.
*/
template <class InputIt, class T, class BinaryOperation>
std::vector<T> scanl(InputIt first, InputIt last, T init, BinaryOperation op){
	std::vector<T> res = std::vector<T>(first, last);
	inplace_scanl(res.begin(), res.end(), init, op);
	return res;
}



#endif /* __UTILS_HPP */