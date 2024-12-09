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
	for(size_t u = 0; u < res.size(); ++u){
		if(res[u] < 0){
			while(res[v] < 0 && u < v) --v;
			res[u] = res[v];
			res[v] = -1;
		}
	}


	for(size_t u = 0; u < res.size(); ++u){
		if(res[u] >= 0) checksum += res[u]*u;
	}

	return checksum;
}

struct Block{
	int id;
	int stride;
	int size;
};

unsigned long int Part2(std::string input){
	std::vector<Block> files;
	std::vector<Block> free;
	int stride = 0;
	for(int i =0; i < input.length(); ++i){
		int size = input[i] - '0';
		if(i%2 == 0){
			files.push_back({i/2, stride, size});
		}else{
			free.push_back({-1, stride, size});
		}
		stride += size;
	}

	for(int i = files.size()-1; i >= 0; --i){
		for(int j = 0; j < free.size(); ++j){
			if(free[j].size >= files[i].size && free[j].stride < files[i].stride){
				free[j].size -= files[i].size;
				files[i].stride = free[j].stride;
				free[j].stride += files[i].size;
			}
		}
	}

	unsigned long int checksum = 0;
	for(const Block& b: files){
		for(int i = b.stride; i < b.stride + b.size; ++i){
			checksum += b.id * i;
		}
	}
	return checksum;
}

void aoc::solutions::day9(char* path){
	std::ifstream fs(path);

	std::string line;
	std::getline(fs, line);
	unsigned long int a = Part1(line);
	unsigned long int b = Part2(line);

	std::cout << "SOLUTION 1: " << a << std::endl;
	std::cout << "SOLUTION 2: " << b << std::endl;
}
