#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

#include <solutions.h>

enum Operation {ADD, MUL, CAT};

struct Step{
	std::size_t pos;
	unsigned long int prev;
	Operation op;
};


bool CanSolve2(unsigned long int target, std::vector<unsigned long int>& vals){

	std::stack<Step> steps;
	steps.push({1, vals[0], ADD});
	steps.push({1, vals[0], MUL});
	steps.push({1, vals[0], CAT});
	std::vector<Operation> ops(vals.size()-1);

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
			case CAT:
				std::string tmp = std::to_string(res) + 
								  std::to_string(vals[step.pos]);
				res = std::stoul(tmp);
				//std::cout << res << "||" << vals[step.pos] << "=" << tmp << std::endl;
		}
		ops[step.pos - 1] = step.op;
		
		if(step.pos + 1 < vals.size()){
			steps.push({step.pos + 1, res, MUL});
			steps.push({step.pos + 1, res, ADD});
			steps.push({step.pos + 1, res, CAT});
		}else{
			if(res == target) return true;
		}
	}
	return false;
}

bool CanSolve(unsigned long int target, std::vector<unsigned long int>& vals){

	std::stack<Step> steps;
	steps.push({1, vals[0], ADD});
	steps.push({1, vals[0], MUL});
	std::vector<Operation> ops(vals.size()-1);

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
			default:
				break;
		}
		ops[step.pos - 1] = step.op;
		
		if(step.pos + 1 < vals.size()){
			steps.push({step.pos + 1, res, MUL});
			steps.push({step.pos + 1, res, ADD});
		}else{
			if(res == target) return true;
		}
	}
	return false;
}

void aoc::solutions::day7(char* path){
	std::ifstream fs(path, std::ios::in);
	std::string line;
	
	unsigned long int sum = 0;
	unsigned long int sum2 = 0;

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
			std::cout << right;
		}else{
			std::cout << wrong;
		}

		if(CanSolve2(target, vals)){
			sum2+=target;
			std::cout << right;
		}else{
			std::cout << wrong;
		}

		std::cout << line << std::endl;
	}
	std::cout << "SOLUTION 1: " << sum << std::endl;
	std::cout << "SOLUTION 2: " << sum2 << std::endl;
}

