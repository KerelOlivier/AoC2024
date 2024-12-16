#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
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

long int Part2(std::vector<int> map, std::vector<int>& moves, int robot, int width){

	for(size_t i = 0; i < map.size(); ++i){
		int row = i / width;
		int col = i % width;
		std::cout << (i == robot ? '@' : map[i] == 0 ? '.' : map[i] == 1 ? '#' : 
				map[i] == 2 ? '[' : ']');
		if(i > 0 && i % (width) == width-1) std::cout << std::endl;
		
	}

	char ms[4] = {'^','>','v','<'};

	for(const int move : moves){
		// Determine new position
		int check_pos = robot;
		//std::cout << ms[move] << std::endl;
		switch(move){
			case 0:
				//std::cout << "UP" << std::endl;
				check_pos -= width;
				if(map[check_pos] == 0){
					robot -= width;
				}else if(map[check_pos] >= 2){	
					std::queue<int> q;
					std::unordered_set<int> visited;
					q.push(check_pos);
					visited.insert(check_pos);

					bool canMove = true;
					while(!q.empty()){
						int pos = q.front();
						q.pop();
						visited.insert(pos);
						if(map[pos] == 1) canMove = false;
						else if(map[pos] == 2){
							if(!visited.contains(pos + 1)) q.push(pos + 1);
							q.push(pos - width);
						}else if(map[pos] == 3){
							if(!visited.contains(pos - 1)) q.push(pos - 1);
							q.push(pos - width);
						}
					}
						
					// Wall check
					if(canMove){
						//std::cout << "MOVEABLE" << std::endl;
						std::unordered_map<int, int> mapping;
						for(const int id : visited){
							int row = id / width;
							int col = id % width;
							//std::cout << row << "," << col << std::endl;
							int rr = robot/width;
							//std::cout << rr << "==" << row <<std::endl;
							mapping[id] = !visited.contains(id+width)? 0: map[id+width];
						}
						
						for(const auto& p : mapping){
							map[p.first] = p.second;
						}
						robot -= width;
					}
				}
				break;
			case 1:
				check_pos += 1;
				if(map[check_pos] == 0){
					robot += 1;
				}else if(map[check_pos] >= 2){
					// Box pushing sequence
					int box_pos = check_pos;
					while(map[box_pos] >= 2)
						box_pos += 1;

					// Wall check
					if(map[box_pos] == 0){
						// move everything in
						while(box_pos >= check_pos){
							if(map[box_pos] == 3) map[box_pos] = 2;
							else map[box_pos] = 3;
							--box_pos;
						}
						map[check_pos] = 0;
						robot += 1;
					}
				}
				break;
			case 2:
				//std::cout << "UP" << std::endl;
				check_pos += width;
				if(map[check_pos] == 0){
					robot += width;
				}else if(map[check_pos] >= 2){	
					std::queue<int> q;
					std::unordered_set<int> visited;
					q.push(check_pos);
					visited.insert(check_pos);

					bool canMove = true;
					while(!q.empty()){
						int pos = q.front();
						q.pop();
						visited.insert(pos);
						if(map[pos] == 1) canMove = false;
						else if(map[pos] == 2){
							if(!visited.contains(pos + 1)) q.push(pos + 1);
							q.push(pos + width);
						}else if(map[pos] == 3){
							if(!visited.contains(pos - 1)) q.push(pos - 1);
							q.push(pos + width);
						}
					}
						
					// Wall check
					if(canMove){
						//std::cout << "MOVEABLE" << std::endl;
						std::unordered_map<int, int> mapping;
						for(const int id : visited){
							int row = id / width;
							int col = id % width;
							//std::cout << row << "," << col << std::endl;
							int rr = robot/width;
							//std::cout << rr << "==" << row <<std::endl;
							mapping[id] = !visited.contains(id-width)? 0: map[id-width];
						}
						
						for(const auto& p : mapping){
							map[p.first] = p.second;
						}
						robot += width;
					}
				}
				break;
			case 3:
				check_pos -= 1;
				if(map[check_pos] == 0){
					robot -= 1;
				}else if(map[check_pos] >= 2){
					// Box pushing sequence
					int box_pos = check_pos;
					while(map[box_pos] >= 2)
						box_pos -= 1;

					// Wall check
					if(map[box_pos] == 0){
						// move everything in
						while(box_pos <= check_pos){
							if(map[box_pos] == 2) map[box_pos] = 3;
							else map[box_pos] = 2;
							++box_pos;
						}
						map[check_pos] = 0;
						robot -= 1;
					}
				}
				break;
		}

		/*
		for(size_t i = 0; i < map.size(); ++i){
			int row = i / width;
			int col = i % width;
			std::cout << (i == robot ? '@' : map[i] == 0 ? '.' : map[i] == 1 ? '#' : 
				map[i] == 2 ? '[' : ']');
			if(i > 0 && i % (width) == width-1) std::cout << std::endl;
		
		}*/
	}

	long int res = 0;
	// Calculate sum of coordinates
	for(size_t i = 0; i < map.size(); ++i){
		int row = i / width;
		int col = i % width;
		std::cout << (i == robot ? '@' : map[i] == 0 ? '.' : map[i] == 1 ? '#' : 
				map[i] == 2 ? '[' : ']');
		if(i > 0 && i % (width) == width-1) std::cout << std::endl;

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
	std::vector<int> warehouse2;
	int width = 0;
	int height = 0;
	int robot = 0;

	// Process Warehouse
	while(getline(fs, line) && line !=""){
		width = line.length();
		for(const char c: line){
			switch(c){
				case '#':
					warehouse.push_back(1);

					warehouse2.push_back(1);
					warehouse2.push_back(1);
					break;
				case 'O':
					warehouse.push_back(2);

					warehouse2.push_back(2);
					warehouse2.push_back(3);
					break;
				case '@':
					robot = warehouse.size();
					warehouse.push_back(0);

					warehouse2.push_back(0);
					warehouse2.push_back(0);
					break;
				default: 
					warehouse.push_back(0);

					warehouse2.push_back(0);
					warehouse2.push_back(0);
			}
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
	long int res2 = Part2(warehouse2, moves, robot*2, width*2);
	std::cout << "SOLUTION 1: " << res1 << std::endl;
	std::cout << "SOLUTION 2: " << res2 << std::endl;

}
