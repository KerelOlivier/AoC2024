#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <solutions.h>

void aoc::solutions::day6(char* path){
	std::ifstream fs(path, std::ios::in);
	std::vector<std::vector<bool>> map;

	// Guard position
	int row = 0;
	int col = 0;

	std::string line;
	while(std::getline(fs, line)){
		std::vector<bool> r;
		for(const char& c : line){
			r.push_back(c != '#');
			if(c == '^'){
				row = map.size();
				col = r.size() - 1;
			}
		}
		map.push_back(r);
	}

	std::cout << "Guard at: [" << row << "," << col << "]" << std::endl;
	int width = map[0].size();
	int height = map.size();
	int l = width*height;
	std::cout << "DIM: " << width << " " << height << std::endl;

	int dir = 0;

	std::vector<bool> visited(l);

	while(row < height && row >= 0 && col < width && col >= 0){
		std::cout << "POS: [" << row << "," << col << "]" << std::endl;
		visited[row*width + col] = true;
		if(dir == 0){ // N
			if(row - 1 < 0 || map[row-1][col])
				--row;
			else
				dir = 1;
		}else if(dir == 1){ // E
			if(col + 1 >= width || map[row][col+1])
				++col;
			else
				dir = 2;

		}else if(dir == 2){ // S
			if(row + 1 >= height || map[row+1][col])
				++row;
			else
				dir = 3;

		}else{ // W
			if(col - 1 < 0 || map[row][col-1])
				--col;
			else
				dir = 0;

		}
	}

	int distinct_cnt = 0;
	for(const bool& b : visited){
		if(b) ++distinct_cnt;
	}

	std::cout << "SOLUTION 1: " << distinct_cnt << std::endl;
}
