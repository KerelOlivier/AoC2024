#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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

	size_t ptr = 0;

	// part 1;
	size_t a = regA;
	size_t b = regB;
	size_t c = regC;

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
	std::cout << out.size() << std::endl;

	std::cout << "A: " << a << std::endl;   
	std::cout << "B: " << b << std::endl;   
	std::cout << "C: " << c << std::endl;  

	std::cout << "SOLUTION 1: ";
	for(size_t i = 0; i < out.size(); ++i){
		std::cout << out[i] <<"," << std::flush;
	}
	std::cout << std::endl;




}

