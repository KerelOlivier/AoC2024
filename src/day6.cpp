#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>

#include <solutions.h>

bool CreatesLoop(std::vector<std::vector<bool>>& map, int r, int c, int row, int col, int dir){
	//int r = row + (dir == 0 ? -1 : dir == 2 ? 1 : 0);
	//int c = col + (dir == 3 ? -1 : dir == 1 ? 1 : 0);

	int height = map.size();
	int width = map[0].size();

	if(r == row && c == col) return false;
	if(c >= width || c < 0 || r >= height || r < 0 || !map[r][c]) return false;
	map[r][c] = false;

	int l = width * height * 5;
	int steps = 0;
	
	int start_dir = dir;
	int rs = row;
	int cs = col;
	int ds = dir;
	//dir = (dir + 1) % 4;

	while(steps < l && row < height && row >= 0 && col < width && col >= 0){
		//std::cout << "POS: [" << row << "," << col << "]" << std::endl;

		//Simulate
		if(dir == 0){ // N
			if(row - 1 < 0){
				map[r][c] = true;
				return false;
			}
			if(map[row-1][col])
				--row;
			else
				dir = 1;
		}else if(dir == 1){ // E
			if(col + 1 >= width){
				map[r][c] = true;
				return false;
			}
			if(map[row][col+1])
				++col;
			else
				dir = 2;

		}else if(dir == 2){ // S
			if(row + 1 >= height){
				map[r][c] = true;
				return false;
			}
			if(map[row+1][col])
				++row;
			else
				dir = 3;

		}else{ // W
			if(col - 1 < 0){
				map[r][c] = true;
				return false;
			}
			if(map[row][col-1])
				--col;
			else
				dir = 0;

		}
		steps++;
	}

	map[r][c] = true;
	return steps >= l;
}

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
		if(r.size() > 0) map.push_back(r);
	}

	int rs = row;
	int cs = col;
	int ds = 0;
	std::cout << "Guard at: [" << row << "," << col << "]" << std::endl;
	int width = map[0].size();
	int height = map.size();
	int l = width*height;
	std::cout << "DIM: " << width << " " << height << std::endl;

	int dir = 0;

	int loop_blocks = 0;
	std::vector<bool> visited(l);
	std::unordered_set<int> blocked;
	while(row < height && row >= 0 && col < width && col >= 0){
		//std::cout << "POS: [" << row << "," << col << "]" << std::endl;
		//Check if placing an obstacle in front would cause a loop

		//Simulate
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
	for(int r = 0; r < height; ++r){
		for(int c = 0; c < height; ++c){
			if(CreatesLoop(map, r, c, rs, cs, ds)){
				loop_blocks++;
			}
		}
	}
			
	std::cout << "SOLUTION 2: " << loop_blocks << std::endl;

}
