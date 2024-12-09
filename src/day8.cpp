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
		std::vector<Tower> towers, size_t width, size_t height){
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
				
				std::cout << towers[i].freq << " [" << towers[i].x << "," << towers[i].y << "] ["
						         << towers[j].x << "," << towers[j].y << "]" << std::endl; 

				if(x >= 0 && x < width && y >=0 && y < height){
					nodes.insert(y * width + x);
					std::cout << right << "[" << x << "," << y << "] " << (y * width * x) << std::endl;
				}else{
					std::cout << wrong << "[" << x << "," << y << "]" << std::endl;
				}
				if(u >= 0 && u < width && v >=0 && v < height){
					nodes.insert(v * width + u);
					std::cout << right << "[" << u << "," << v << "] " << (v * width * u) << std::endl;
				}else{
					std::cout << wrong << "[" << u << "," << v << "]" << std::endl;
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
	std::cout << "SOLUTION 2: " << std::endl;
}
