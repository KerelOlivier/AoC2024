#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

#include <solutions.h>

enum Operation {ADD, MUL};

struct Step{
	std::size_t pos;
	unsigned long int prev;
	Operation op;
};


bool CanSolve(unsigned long int target, std::vector<unsigned long int>& vals){

	std::stack<Step> steps;
	steps.push({1, vals[0], ADD});
	steps.push({1, vals[0], MUL});
	std::vector<Operation> ops(vals.size()-1);

	int num = 0;

	while(!steps.empty()){	
		Step step = steps.top();
		steps.pop();

		unsigned long int res = step.prev;
		switch(step.op){
			case ADD:
				res += vals[step.pos];
				break;
			case MUL:
				res *= vals[step.pos];
				break;
		}
		ops[step.pos - 1] = step.op;
		
		if(step.pos + 1 < vals.size()){
			steps.push({step.pos + 1, res, MUL});
			steps.push({step.pos + 1, res, ADD});
		}else{
			++num;
			/*
			std::cout << ++num << " | ";
			
			unsigned long int test = vals[0];
			for(int i = 0; i < vals.size() - 1; ++i){
				std::cout << vals[i] << (ops[i] == ADD ? "+" : "*");
				if(ops[i] == ADD) test += vals[i+1];
				else test *= vals[i+1];
			}
			std::cout << vals[vals.size()-1] << "=" << res;
			if(res != test) std::cout << " FUCK " << test;
			std::cout << std::endl;			
*/
			if(res == target) return true;
		}
	}
	int cnt = 1 << (vals.size()-1);
	if(num != cnt) std::cout << "FUCK" << std::endl;
	return false;
}

void aoc::solutions::day7(char* path){
	std::ifstream fs(path, std::ios::in);
	std::string line;
	
	unsigned long int sum = 0;
	while(std::getline(fs, line)){
		std::stringstream ss(line, std::ios::in | std::ios::out);

		std::string val;
		std::vector<unsigned long int> vals;

		std::getline(ss, val, ':'); 
		unsigned long int target = std::stol(val);

		std::getline(ss, val);
		ss.clear();
		ss = std::stringstream(val.substr(1, val.length()- 1));
		
		while(ss >> val){
			vals.push_back(std::stol(val));	

		}
		if(CanSolve(target, vals)){ 
			sum += target;
			std::cout << right << sum << " | " <<  line << std::endl;
		}else{
			std::cout << wrong << line << std::endl;
		}
	}
	std::cout << "SOLUTION 1: " << sum << std::endl;
	std::cout << "SOLUTION 2: " << std::endl;
}

