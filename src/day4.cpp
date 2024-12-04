#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <solutions.h>

void aoc::solutions::day4(char* path){
	std::ifstream fs(path, std::ios::in);
	std::vector<std::string> ws;

	// Read word search grid
	std::string line;
	while(std::getline(fs, line)){
		ws.push_back(line);
	}


	// Cursed kernel convolution
	int cols = ws[0].length();
	int rows = ws.size();

	int occ = 0;
	for(int r = 0; r < rows; ++r){
		for(int c = 0; c < cols; ++c){
			if(ws[r][c] != 'X') continue;
			// check horizontal
			if(c < cols - 3 && ws[r].substr(c, 4) == "XMAS") ++occ;
			if(c >= 3 && ws[r].substr(c-3, 4) == "SAMX") ++occ;

			// Check vertical
			if(r < rows - 3 && 
			   ws[r+1][c] == 'M' && ws[r+2][c] == 'A' && ws[r+3][c] == 'S') ++occ;	
			if(r >= 3 &&
			   ws[r-1][c] == 'M' && ws[r-2][c] == 'A' && ws[r-3][c] == 'S') ++occ;	

			// Check Diagonal
			if(r < rows - 3 && c < cols - 3 &&
			   ws[r+1][c+1] == 'M' && ws[r+2][c+2] == 'A' && ws[r+3][c+3] == 'S') ++occ;	
			if(r < rows - 3 && c >= 3 &&
			   ws[r+1][c-1] == 'M' && ws[r+2][c-2] == 'A' && ws[r+3][c-3] == 'S') ++occ;	
			if(r >= 3 && c < cols - 3 &&
			   ws[r-1][c+1] == 'M' && ws[r-2][c+2] == 'A' && ws[r-3][c+3] == 'S') ++occ;	
			if(r >= 3 && c >= 3 &&
			   ws[r-1][c-1] == 'M' && ws[r-2][c-2] == 'A' && ws[r-3][c-3] == 'S') ++occ;	
		}
	}

	std::cout << "SOLUTION 1: " << occ << std::endl;
	
	int crosses = 0;

	for(int r = 1; r < rows - 1; ++r){
		for(int c = 1; c < cols - 1; ++c){
			bool flag = true;
			if(ws[r][c] != 'A') continue;

			if(!((ws[r+1][c+1] == 'M' && ws[r-1][c-1] == 'S') ||
				 (ws[r+1][c+1] == 'S' && ws[r-1][c-1] == 'M'))) flag = false;
			if(!((ws[r-1][c+1] == 'M' && ws[r+1][c-1] == 'S') ||
				 (ws[r-1][c+1] == 'S' && ws[r+1][c-1] == 'M'))) flag = false;

			if(flag) ++crosses;
		}
	}

	std::cout << "SOLUTION 2: " << crosses << std::endl;

}

