#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>

#include <solutions.h>


void aoc::solutions::day10(char* path){
	std::ifstream fs(path);
	std::string line;

	std::vector<std::string> map;

	while(getline(fs, line)){
		map.push_back(line);	
	}

	int width = map[0].size();
	int height = map.size();

	int score = 0;

	for(int row = 0; row < map.size(); ++row){
		for(int col = 0; col < map[0].size(); ++col){
			if(map[row][col] == '0'){
				// Start traversing the hikes
				std::unordered_set<int> goals;
				std::stack<int> q;
				q.push(row * width + col);

				while(!q.empty()){
					int p = q.top();
					q.pop();
					int r = p / width;
					int c = p % width;
					int v = map[r][c] - '0';

					//std::cout << r << "," << c << ">>" << v << std::endl;

					if(v == 9 && !goals.contains(p)){
						goals.insert(p);
						std::cout << ">>>" << r << "," << c << std::endl;
					}
					else{
						int N = (r-1)*width + c;
						int E = r*width + (c+1);
						int S = (r+1)*width + c;
						int W = r*width + (c-1);
						if(r - 1 >= 0 && map[r-1][c]-'0'-v == 1) q.push(N);
						if(c - 1 >= 0 && map[r][c-1]-'0'-v == 1) q.push(W);
						if(r + 1 < height && map[r+1][c]-'0'-v == 1) q.push(S);
						if(c + 1 < width && map[r][c+1]-'0'-v == 1)	q.push(E);
					}
				}
				std::cout << row << "," << col << "->" << goals.size() << std::endl;
				std::cout << "--------" << std::endl;
				score += goals.size();
			}
		}
	}
	
	std::cout << "SOLUTION 1: " << score << std::endl;


}
