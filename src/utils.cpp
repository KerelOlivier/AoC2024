#include <utils.h>

std::vector<std::string> aoc::utils::split(std::string s, std::string delimiter){
	std::vector<std::string> res;

	std::size_t last = 0; 
	std::size_t next = 0;
	while ((next = s.find(delimiter, last)) != std::string::npos){
		res.push_back(s.substr(last, next-last)); 
		last = next + 1; 
	}
	return res;
}
