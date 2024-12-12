#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <solutions.h>

struct Region{
	int area;
	int perimeter;
	char c;
};

Region Floodfill(int id, int width, int height, 
				 std::vector<std::string> map, 
				 std::vector<bool>& visited){
	char c = map[id/width][id%width];
	Region res = {0, 0, c};

	std::queue<int> flood;
	flood.push(id);

	while(!flood.empty()){
		int id = flood.front();
		int row = id / width;
		int col = id % width;
		flood.pop();
		
		if(visited[id]) continue;

		visited[id] = true;

		// Increase area
		++res.area;
		// update perimiter
		if(row == height -1 || (row + 1 < height && map[row+1][col] != c)) ++res.perimeter;
		if(row == 0 || (row - 1 >= 0 && map[row-1][col] != c)) ++res.perimeter;
		if(col == width - 1 || (col + 1 < width && map[row][col+1] != c)) ++res.perimeter;
		if(col == 0 || (col - 1 >= 0 && map[row][col-1] != c)) ++res.perimeter;

		// Add unvisited neighbours of same region
		if(col + 1 < width && map[row][col+1] == c)	flood.push(id+1);
		if(col - 1 >= 0 && map[row][col-1] == c) flood.push(id-1);
		if(row + 1 < height && map[row+1][col] == c) flood.push(id+width);
		if(row - 1 >= 0 && map[row-1][col] == c) flood.push(id-width);
	}
	return res;
}

int Part2(int width, int height, std::vector<std::string>& map){
	return 0;
}

void aoc::solutions::day12(char* path){
	std::ifstream fs(path);
	std::string line;
	std::vector<std::string> field;

	while(getline(fs, line)){
		field.push_back(line);
		std::cout << line << std::endl;
	}

	int width = field[0].size();
	int height = field.size();

	std::vector<bool> visited(width * height, false);

	int cost = 0;

	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			int id = row * width + col;
			if(!visited[id]){
				Region region = Floodfill(id, width, height, field, visited);
				std::cout << "{" << region.c << "," << region.area << "," 
					      << region.perimeter << "}" <<std::endl;
				cost += region.area * region.perimeter;
			}
		}
	}

	std::cout << "SOLUTION 1: " << cost << std::endl;

	int bulkCost = Part2(width, height, field);
	
	std::cout << "SOLUTION 2: " << bulkCost << std::endl;
}
