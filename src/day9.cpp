#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <solutions.h>

unsigned long int Part1(std::string input){
	std::vector<int> res;
	
	for(int i = 0; i < input.length(); ++i){
		for(char j = 0; j < input[i]-'0'; ++j){
			if(i%2 == 0){
				res.push_back(i/2);
			}else{
				res.push_back(-1);

			}
		}
	}
	unsigned long int checksum = 0;
	int v = res.size()-1;
	for(int u = 0; u < res.size(); ++u){
		if(res[u] < 0){
			while(res[v] < 0 && u < v) --v;
			res[u] = res[v];
			res[v] = -1;
		}
	}


	for(int u = 0; u < res.size(); ++u){
		if(res[u] >= 0) checksum += res[u]*u;
	}

	return checksum;
}

void aoc::solutions::day9(char* path){
	std::ifstream fs(path);

	std::string line;
	std::getline(fs, line);

	unsigned long int res = Part1(line);

	std::cout << "SOLUTION 1: " << res << std::endl;
	std::cout << "SOLUTION 2: " << std::endl;
}
