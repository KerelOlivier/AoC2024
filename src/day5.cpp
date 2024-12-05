#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
#include <solutions.h>

bool IsValid(std::string line, std::vector<std::vector<int>>& order){
	bool res = true;
	std::string token;
	std::istringstream ss(line);
	std::unordered_set<int> prev_tokens;

	while(std::getline(ss, token, ',')){
		int val = std::stoi(token);
		
		for(const int v : order[val]){
			if(prev_tokens.contains(v)){
				return false;
			}
		}

		prev_tokens.insert(val);	
	}
	return res;
}

void aoc::solutions::day5(char* path){
	std::ifstream fs(path, std::ios::in);

	std::vector<std::vector<int>> order(100);

	std::string line = "";
	int sum = 0;
	while(std::getline(fs, line)){
		if(line.length() == 0) continue;
		if(line.length() == 5){
			int a = std::stoi(line.substr(0, 2));
			int b = std::stoi(line.substr(3, 2)); 
			std::cout << a << " ≻ " << b << std::endl;
			order[a].push_back(b);
		}else{
			bool valid = IsValid(line, order);
			if(valid){
				sum += std::stoi(line.substr((line.length()/2-1),2));
			}
			std::cout << (valid ? "\u001b[32m✓\u001b[0m " : "\u001b[31m✗\u001b[0m ") 
				      << line << std::endl;	
		}
	}



	std::cout << "SOLUTION 1: " << sum << std::endl;
	std::cout << "SOLUTION 2: " << std::endl;
}
