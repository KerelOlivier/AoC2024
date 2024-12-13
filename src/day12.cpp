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
	std::vector<int> regions(width*height, -1);
	std::vector<int> areas;
	// Properly ID regions
	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			int id = row * width + col;
			if(regions[id] < 0){
				int area = 0;
				//Floodfill and update region
				std::queue<int> cells;
				cells.push(id);

				while(!cells.empty()){
					int cell = cells.front();
					int row = cell / width;
					int col = cell % width;
					cells.pop();


					if(regions[cell] != -1) continue;
					regions[cell] = areas.size();

					++area;

					// Add unvisited neighbours of same region
					char c = map[row][col];
					if(col + 1 < width && map[row][col+1] == c)	cells.push(cell+1);
					if(col - 1 >= 0 && map[row][col-1] == c) cells.push(cell-1);
					if(row + 1 < height && map[row+1][col] == c) cells.push(cell+width);
					if(row - 1 >= 0 && map[row-1][col] == c) cells.push(cell-width);

				}
				areas.push_back(area);
			}
		}
	}

	std::vector<int> perimeters(areas.size(), 0);
	// Find horizonal Fences
	for(int row = 0; row < height; ++row){

		for(int col = 0; col < width; ++col){
			int id = row * width + col;
			int tl = row == 0 || col == 0 ? -1 : regions[id-width-1];
			int t = row == 0 ? -1 : regions[id-width];
			int ml = col == 0 ? -1 : regions[id-1];
			int m = regions[id];
			int bl = row == height - 1 || col == 0? -1 : regions[id+width-1];
			int b = row == height ? -1 : regions[id+width];
			
			if(row == 0 || m != t){ // Up
				if(tl == m || ml != m){
					++perimeters[regions[id]];
				}
			}
			if(row == height - 1 || m != b){ // Down
				if(bl == m || ml != m){
					++perimeters[regions[id]];
				}
			}
		
		}
	}
	for(int col = 0; col < width; ++col){
		for(int row = 0; row < height; ++row){
			int id = row * width + col;
			
			int t = row == 0 ? -1 : regions[id-width];
			int m = regions[id];

			int tr = row == 0 || col == width - 1 ? -1 : regions[id+1-width];
			int mr = col == width - 1 ?  - 1 : regions[id+1];

			int tl = row == 0 || col == 0 ? -1 : regions[id-width-1];
			int ml = col == 0 ? -1 : regions[id-1];
			
			if(col == 0 || m != ml){ // Left
				if(tl == m || t != m){
					++perimeters[regions[id]];
				}
			}
			if(col == width - 1 || m != mr){ // Right
				if(tr == m || t != m){
					++perimeters[regions[id]];
				}
			}
		
		}
	}

	int res = 0;
	for(size_t i = 0;i < perimeters.size(); ++i){
		res += perimeters[i]*areas[i];
	}
	return res;
}

void aoc::solutions::day12(char* path){
	std::ifstream fs(path);
	std::string line;
	std::vector<std::string> field;

	while(getline(fs, line)){
		field.push_back(line);
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
				cost += region.area * region.perimeter;
			}
		}
	}

	std::cout << "SOLUTION 1: " << cost << std::endl;

	int bulkCost = Part2(width, height, field);
	
	std::cout << "SOLUTION 2: " << bulkCost << std::endl;
}
