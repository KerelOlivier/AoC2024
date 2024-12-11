#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <solutions.h>
#include <cmath>
#include <thread>
#include <mutex>
#include <map>
std::vector<unsigned long int> BlinkOnce(unsigned long int stone){
	std::vector<unsigned long int> res;
	unsigned long int digits = std::to_string(stone).length();
	if(stone == 0){
		res.push_back(1);
	}else if (digits % 2 == 0){
		std::string str = std::to_string(stone);
		size_t ptr = str.length()/2;
		std::string a = str.substr(0, ptr);
		std::string b = str.substr(ptr, str.length()-ptr);
		res.push_back(std::stoul(a));
		res.push_back(std::stoul(b));
	}else{
		res.push_back(stone * 2024);
	}
	return res;
}

std::vector<unsigned long int> Blink(std::vector<unsigned long int>& stones){
	std::vector<unsigned long int> res;

	for(unsigned long int stone : stones){
		unsigned long int digits = std::to_string(stone).length();
		if(stone == 0){
			res.push_back(1);
		}else if (digits % 2 == 0){
			std::string str = std::to_string(stone);
			size_t ptr = str.length()/2;
			std::string a = str.substr(0, ptr);
			std::string b = str.substr(ptr, str.length()-ptr);
			res.push_back(std::stoul(a));
			res.push_back(std::stoul(b));
		}else{
			res.push_back(stone * 2024);
		}
	}
	return res;
}

std::vector<unsigned long int> Solver(unsigned long int stone, int steps){
	std::vector<unsigned long int> stones;
	stones.push_back(stone);

	for(int i = 0; i < steps; ++i){
		 stones = Blink(stones);
	}
	return stones;
}


struct Step{
	unsigned long int val;
	int remaining_steps;
};

bool operator<(const Step& lhs, const Step& rhs){
	if(lhs.val == rhs.val) return lhs.remaining_steps < rhs.remaining_steps;
	else return lhs.val < rhs.val;
}

bool operator>(const Step& lhs, const Step& rhs){
	if(lhs.val == rhs.val) return lhs.remaining_steps > rhs.remaining_steps;
	else return lhs.val > rhs.val;
}

bool operator==(const Step& lhs, const Step& rhs){
	return lhs.val == rhs.val && lhs.remaining_steps == rhs.remaining_steps;
}




unsigned long int Solve(std::map<Step, unsigned long int>& mem, 
		unsigned long int stone, int step){
	if(step == 0) return 1;
	if(mem.contains({stone, step})) return mem[{stone, step}];
	
	unsigned long int res = 0;

	signed long int digits = std::to_string(stone).length();
	if(stone == 0) res = Solve(mem, 1, step - 1);
	else if (digits % 2 == 0){
		std::string str = std::to_string(stone);
		size_t ptr = str.length()/2;
		unsigned long int a = std::stoul(str.substr(0, ptr));
		unsigned long int b = std::stoul(str.substr(ptr,str.length()-ptr));
		
		res = Solve(mem, a, step - 1) + Solve(mem, b, step - 1);
	}else{
		res = Solve(mem, stone*2024, step - 1);
	}

	mem[{stone, step}] = res;
	return res;
}
void aoc::solutions::day11(char* path){
	// Initialize
	std::ifstream fs(path);
	std::vector<unsigned long int> stones;
	unsigned long stone;
	while(fs >> stone) stones.push_back(stone);
	
	unsigned long int len = 0;
	unsigned long int len2 = 0;

	std::map<Step, unsigned long int> mem;	
	for(const auto s : stones){
		len += Solve(mem, s, 25);
		len2 += Solve(mem, s, 75);
	}

	std::cout << "SOLUTION 1: " << len << std::endl;
	std::cout << "SOLUTION 2: " << len2 << std::endl;
}
