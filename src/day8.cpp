#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <solutions.h>

struct Tower{
	char freq;
	size_t x;
	size_t y;
};

std::unordered_set<size_t> GetDistinctAntinodes(
		std::vector<Tower> towers, int width, int height){
	std::unordered_set<size_t> nodes;

	for(size_t i = 0; i < towers.size(); ++i){
		for(size_t j = i + 1; j < towers.size(); ++j){
			if(towers[i].freq == towers[j].freq){
				int dx = (int)towers[i].x - (int)towers[j].x;
				int dy = (int)towers[i].y - (int)towers[j].y;

				int x = towers[i].x + dx;
				int y = towers[i].y + dy;

				int u = towers[j].x - dx;
				int v = towers[j].y - dy;
				
				if(x >= 0 && x < width && y >=0 && y < height){
					nodes.insert(y * width + x);
				}
				if(u >= 0 && u < width && v >=0 && v < height){
					nodes.insert(v * width + u);
				}
			}
		}
	}

	return nodes;
}

std::unordered_set<size_t> GetDistinctAntinodes2(
		std::vector<Tower> towers, int width, int height){
	std::unordered_set<size_t> nodes;

	for(size_t i = 0; i < towers.size(); ++i){
		nodes.insert(towers[i].y * width + towers[i].x);
		for(size_t j = i + 1; j < towers.size(); ++j){
			if(towers[i].freq == towers[j].freq){
				std::cout << towers[i].freq << " [" << towers[i].x << "," << towers[i].y << "] ["
				          << towers[j].x << "," << towers[j].y << "]" << std::endl; 


				int dx = (int)towers[i].x - (int)towers[j].x;
				int dy = (int)towers[i].y - (int)towers[j].y;

				int x = towers[i].x + dx;
				int y = towers[i].y + dy;

				while(x >= 0 && x < width && y >= 0 && y < height){
					nodes.insert(y * width + x);
					std::cout << "[" << x << "," << y << "]" << std::endl;

					x += dx;
					y += dy;
				}

				int u = towers[j].x - dx;
				int v = towers[j].y - dy;

				while(u >= 0 && u < width && v >= 0 && v < height){
					nodes.insert(v * width + u);
					std::cout << "[" << u << "," << v << "]" << std::endl;

					u -= dx;
					v -= dy;
				}
				
			}
		}
	}

	return nodes;
}

void aoc::solutions::day8(char* path){
	std::ifstream fs(path);

	std::vector<Tower> towers;

	std::string line;
	size_t height = 0;
	size_t width = 0;
	while(std::getline(fs, line)){
		width = line.length();
		for(size_t i = 0; i < line.length(); ++i){
			if(line[i] != '.'){
				towers.push_back({line[i], height, i});
				std::cout << "{" << line[i] << "," << height  << "," << i <<"}" << std::endl;
			}
		}
		++height;
	}

	std::cout << width << " " << height << std::endl;
	size_t nodes = GetDistinctAntinodes(towers, width, height).size();
	std::cout << "SOLUTION 1: " << nodes << std::endl;
	size_t nodes2 = GetDistinctAntinodes2(towers, width, height).size();
	std::cout << "SOLUTION 2: " << nodes2 << std::endl;
}
