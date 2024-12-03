#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <solutions.h>

void aoc::solutions::day3(char* path){
	std::ifstream fs(path, std::ios::in);
	
	std::string line;
	std::regex reggy("mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)");


	int ttl = 0;
	int ttl2 = 0;

	bool toggle = true;

	while(std::getline(fs, line)){
		auto iter = 
			std::sregex_iterator(line.begin(), line.end(), reggy);

		for(; iter != std::sregex_iterator(); ++iter){
			std::smatch m = *iter;
			
			if(m.str() == "do()") toggle = true;
			else if(m.str() == "don't()") toggle = false;
			else{
				int res = std::stoi((*(m.begin()+1)).str()) *
				       std::stoi((*(m.begin()+2)).str());
				ttl += res;
				if(toggle) ttl2 += res;
			}
		}
	}

	std::cout << "SOLUTION 1: " << ttl << std::endl;
	std::cout << "SOLUTION 2: " << ttl2 << std::endl;

}
