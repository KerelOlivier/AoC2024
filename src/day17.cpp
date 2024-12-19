#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <stack>

#include <solutions.h>

size_t GetCombo(char code, size_t a, size_t b, size_t c){
	switch(code){
		case 0:
		case 1:
		case 2:
		case 3:
			return code;
			break;
		case 4:
			return a;
			break;
		case 5:
			return b;
			break;
		case 6:
			return c;
			break;
	}
	return UINT64_MAX;
}

void PerformOperant(char code, size_t literal, size_t combo, 
		            size_t& a, size_t& b, size_t& c, size_t& ptr, std::vector<size_t>& out){
	switch(code){
		case 0: // adv
			a = a/(1 << combo);
			break;
		case 1: // bxl
			b ^= literal; 
			break;
		case 2: // bst
			b = combo % 8;
			break;
		case 3: // jnz
			if(a != 0){
				ptr = literal;
			}
			break;
		case 4: // bxc
			b = b ^ c;
			break;
		case 5: // out
			out.push_back(combo % 8);
			break;
		case 6: // bdv
			b = a/(1<<combo);
			break;
		case 7: // cdv
			c = a/(1<<combo);
			break;
	}
}

std::string Part1(std::vector<char>& instructions, size_t a, size_t b, size_t c){
	size_t ptr = 0;

	// part 1;
	std::vector<size_t> out;

	while(ptr < instructions.size()){
		size_t prev_ptr = ptr;
		char instruction = instructions[ptr];
		char literal = instructions[ptr+1];

		size_t combo = GetCombo(literal, a, b, c); 
		PerformOperant(instruction, literal, combo, a, b, c, ptr, out);	
		
		if(prev_ptr == ptr) ptr+=2;
		//std::cout << a << "," << b << "," << c << ":" << ptr << " " << (int)instruction << std::endl;
	}
	
	std::stringstream ss;
	for(size_t i = 0; i < out.size(); ++i){
		ss << out[i] <<"," << std::flush;
	}
	
	return ss.str().substr(0, ss.str().length()-1);
}

struct SearchBlock{
	size_t lower;
	size_t upper;
	size_t depth;
};

size_t Part2(std::vector<char>& instructions, size_t regA, size_t regB, size_t regC,
		std::string line){ 
	std::stack<SearchBlock> s;

	size_t a = std::pow(8, line.size()/2); 
	size_t b = std::pow(8, line.size()/2+1);
	std::cout << a << ", " << b << std::endl;
	
	s.emplace(a, b, 0);
	bool found = false;
	
	while(!found && !s.empty()){
		SearchBlock b = s.top();
		s.pop();

		// Calculate the stepsize
		size_t step = std::pow(8, line.size()/2-b.depth);
		size_t l = b.lower;

		//std::cout << b.lower << " " << b.upper << " " << b.depth << std::endl;

		char trgt = *(line.end()-1-(b.depth)*2);
		//std::cout << trgt << "::" << 1-(b.depth)*2 << std::endl;
		while(l < b.upper){
			std::string tmp = Part1(instructions, l, regB, regC);
			char lastc = *(tmp.end()-1-(b.depth)*2);
			if(tmp == line){
				std::cout << "found" << std::endl;
				return l;
			}
			//std::cout << l << ": [" << lastc << "] "<< tmp << std::endl;

			if(lastc == trgt){
				s.emplace(l, l+step, b.depth + 1);
			}
			l+=step;
		}
	}
}

void aoc::solutions::day17(char* path){
	std::ifstream fs(path);
	
	std::string line;

	size_t regA = 0;
	size_t regB = 0;
	size_t regC = 0;

	fs >> line >> line >> regA;
	fs >> line >> line >> regB;
	fs >> line >> line >> regC;
	fs >> line >> line;

	std::vector<char> instructions;
	std::stringstream ss(line);
	std::string instr;
	while(getline(ss, instr, ',')){
		instructions.push_back(instr[0]-'0');
	}

	std::string res1 = Part1(instructions, regA, regB, regC);
	
	std::cout << "SOLUTION 1: " << res1 << std::endl;
	
	std::string output = "";

	size_t res2 = Part2(instructions, regA, regB, regC, line);
	std::cout << "SOLUTION 1: " << res2 << std::endl;


	

}

