#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <solutions.h>
std::vector<std::vector<int>> parse(std::string path){
	std::ifstream stream(path, std::ios::in);

	std::vector<std::vector<int>> res = {std::vector<int>(), std::vector<int>()};

	if(!stream.is_open()) std::cerr << "ERROR | Failed to open input file" << std::endl;
	else{
		std::string a, b;

		while(stream >> a >> b){
			res[0].push_back(std::stoi(a.c_str()));
			res[1].push_back(std::stoi(b.c_str()));
		}
	}

	stream.close();

	return res;

}

void aoc::solutions::day1(char* path){
	std::cout <<"TEST" <<std::endl;

	std::vector<std::vector<int>> l = parse(std::string(path));

	std::sort(l[0].begin(), l[0].end());
	std::sort(l[1].begin(), l[1].end());

	int ttl_dist = 0;
	for(std::size_t i = 0; i < l[0].size(); ++i){
		ttl_dist+=std::abs(l[0][i] - l[1][i]);
	}

	std::cout << "SOLUTION 1: " << ttl_dist << std::endl;

	std::unordered_map<int, int> frequency;
	for(std::size_t i = 0; i < l[1].size(); ++i){
		if(frequency.contains(l[1][i]))
			frequency[l[1][i]] += 1;	
		else
			frequency[l[1][i]] = 1;
	}

	int score = 0;
	for(std::size_t i = 0; i < l[0].size(); ++i){
		if(frequency.contains(l[0][i]))
			score += l[0][i] * frequency[l[0][i]];
	}
	std::cout << "SOLUTION 2: " << score << std::endl;
}
