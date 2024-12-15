#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <solutions.h>

long int Part1(std::vector<int> map, std::vector<int>& moves, int robot, int width){

	for(const int move : moves){
		// Determine new position
		int check_pos = robot;
		switch(move){
			case 0:
				check_pos -= width;
				if(map[check_pos] == 0){
					robot -= width;
				}else if(map[check_pos] == 2){
					// Box pushing sequence
					int box_pos = check_pos;
					while(map[box_pos] == 2)
						box_pos -= width;
					// Wall check
					if(map[box_pos] == 0){
						map[box_pos] = 2;
						map[check_pos] = 0;
						robot-=width;
					}
				}
				break;
			case 1:
				check_pos += 1;
				if(map[check_pos] == 0){
					robot += 1;
				}else if(map[check_pos] == 2){
					// Box pushing sequence
					int box_pos = check_pos;
					while(map[box_pos] == 2)
						box_pos += 1;
					// Wall check
					if(map[box_pos] == 0){
						map[box_pos] = 2;
						map[check_pos] = 0;
						robot+=1;
					}
				}
				break;
			case 2:
				check_pos += width;
				if(map[check_pos] == 0){
					robot += width;
				}else if(map[check_pos] == 2){
					// Box pushing sequence
					int box_pos = check_pos;
					while(map[box_pos] == 2)
						box_pos += width;
					// Wall check
					if(map[box_pos] == 0){
						map[box_pos] = 2;
						map[check_pos] = 0;
						robot+=width;
					}
				}
				break;
			case 3:
				check_pos -= 1;
				if(map[check_pos] == 0){
					robot -= 1;
				}else if(map[check_pos] == 2){
					// Box pushing sequence
					int box_pos = check_pos;
					while(map[box_pos] == 2)
						box_pos -= 1;
					// Wall check
					if(map[box_pos] == 0){
						map[box_pos] = 2;
						map[check_pos] = 0;
						robot -= 1;
					}
				}
				break;
		}
	}

	long int res = 0;
	// Calculate sum of coordinates
	for(size_t i = 0; i < map.size(); ++i){
		int row = i / width;
		int col = i % width;
		//std::cout << (i == robot ? '@' : map[i] == 0 ? '.' : map[i] == 1 ? '#' : 'O');
		//if(i > 0 && i % (width) == width-1) std::cout << std::endl;
		
		if(map[i] == 2){
			res += 100 * row + col;
		}
		
	}

	return res;
}



void aoc::solutions::day15(char* path){
	std::ifstream fs(path);
	std::string line;

	std::vector<int> warehouse;
	int width = 0;
	int height = 0;
	int robot = 0;

	// Process Warehouse
	while(getline(fs, line) && line !=""){
		width = line.length();
		int ci = 0;
		for(const char c: line){
			switch(c){
				case '#':
					warehouse.push_back(1);
					break;
				case 'O':
					warehouse.push_back(2);
					break;
				case '@':
					robot = warehouse.size();
					warehouse.push_back(0);
					break;
				default: 
					warehouse.push_back(0);
			}
			++ci;
		}
		++height;
	}
	

	// Process Moves
	std::vector<int> moves;
	while(getline(fs, line)){
		for(const char c: line){
			switch(c){
				case '^':
					moves.push_back(0);
					break;
				case '>':
					moves.push_back(1);
					break;
				case 'v':
					moves.push_back(2);
					break;
				case '<':
					moves.push_back(3);
					break;
			}
		}
	}

	long int res1 = Part1(warehouse, moves, robot, width);
	std::cout << "SOLUTION 1: " << res1 << std::endl;

}
