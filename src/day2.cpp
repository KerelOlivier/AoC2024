#include <day2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

void aoc::day2::solve(char* path){
	 // Parse input
	std::ifstream stream(std::string(path), std::ios::in);

	std::string line;
	int safe_cnt = 0;
	while(std::getline(stream, line)){
		std::stringstream sstream(line);
		int curr, prev, last;
		bool safe = true;

		// Initialize the orientation
		sstream >> prev;
		sstream >> curr;

		int dir = curr - prev;

		//verify first step
		if(std::abs(dir) < 1 || std::abs(dir) > 3){
			safe = false;
		}

		// Move sliding window
		last = prev;
		prev = curr;


		while(sstream >> curr){
			int d = curr - prev;
			if(std::signbit(d) != std::signbit(dir) || std::abs(d) > 3 ||
					std::abs(d) < 1){
				// Not a safe sequence
				safe  = false;
			}

			//Move sliding window
			last = prev;
			prev = curr;	
		}

		if(safe) ++safe_cnt;
	}

	std::cout << "SOLUTION 1: " << safe_cnt << std::endl;
}
