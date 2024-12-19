#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <solutions.h>

struct Point{
	size_t x;
	size_t y;
};

struct MemStep{
	size_t id;
	size_t dist;
};

std::strong_ordering operator<=>(const MemStep& lhs, const MemStep& rhs){
	return lhs.dist <=> rhs.dist;
}

void PrintMemory(std::vector<bool>& memory, size_t size){
	for(size_t row =0; row < size; ++row){
		for(size_t col = 0; col < size; ++col){
			std::cout << (memory[row * size + col] ? "." : "#");
		}
		std::cout << std::endl;
	}
}

size_t Part1(std::vector<bool> memory, std::vector<Point>& locations, size_t size){

	for(int i = 0; i < 1024; ++i){
		memory[locations[i].y * size + locations[i].x] = false;
	}

	PrintMemory(memory, size);

	// Path finding
	std::unordered_map<size_t, size_t> prev;
	std::vector<size_t> dist(size*size, UINT64_MAX);
	std::priority_queue<MemStep> q;

	std::unordered_set<size_t> visited;

	q.emplace(0,0);
	
	while(!q.empty()){
		MemStep n = q.top();
		q.pop();
		visited.insert(n.id);
		
		//if(n.id == size*size-1) break; // End reached

		// Add valid neighbours 
		if(n.id % size > 0 && memory[n.id - 1] && dist[n.id - 1] > n.dist+1){
			dist[n.id - 1] = n.dist + 1;
			prev[n.id - 1] = n.id;
			q.emplace(n.id-1, n.dist+1);
		}
		if(n.id % size < size - 1 && memory[n.id + 1] && dist[n.id + 1] > n.dist+1){
			dist[n.id + 1] = n.dist + 1;
			prev[n.id + 1] = n.id;
			q.emplace(n.id+1, n.dist+1);
		}
		
		if(n.id / size > 0 && memory[n.id - size] && dist[n.id - size] > n.dist+1){
			dist[n.id - size] = n.dist + 1;
			prev[n.id - size] = n.id;
			q.emplace(n.id-size, n.dist+1);
		}
		if(n.id / size < size - 1 && memory[n.id + size] && dist[n.id + size] > n.dist+1){
			dist[n.id + size] = n.dist + 1;
			prev[n.id + size] = n.id;
			q.emplace(n.id+size, n.dist+1);
		}
	}


	// Reconstruct path
	std::unordered_set<size_t> path;
	path.insert(0);
	size_t p = size * size - 1;
	while(prev.contains(p) && p != 0){
		path.insert(p);
		p = prev[p];
	}
	
	std::cout << std::endl;

	// Draw solved memory
	for(size_t row =0; row < size; ++row){
		for(size_t col = 0; col < size; ++col){
			size_t id = row * size + col;
			//if(visited.contains(id))std::cout << "\u001b[35m";
			if(path.contains(id)) std::cout << "\u001b[31m";
			std::cout << (memory[id] ? "." : "#") << "\u001b[0m";
		}
		std::cout << std::endl;
	}
	
	return path.size()-1;
}

void aoc::solutions::day18(char* path){
	std::ifstream fs(path);
	std::string line;

	size_t size = 71;
	std::vector<bool> memory(size*size, true);
	std::vector<Point> locations;

	while(getline(fs, line)){
		auto ptr = line.find(',');
		size_t x = std::stoul(line.substr(0, ptr));
		size_t y = std::stoul(line.substr(ptr+1, line.length() - ptr));
		locations.emplace_back(x, y);
	}

	std::cout << locations.size() << std::endl;

	size_t res1 = Part1(memory, locations, size);	

	std::cout << "SOLUTION 1: " << res1 << std::endl;
}
