#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <solutions.h>
#include <iomanip>
#include <cmath>


struct Point{
	size_t row;
	size_t col;
};

struct Vertex{
	size_t id;
	size_t dist;
};
std::strong_ordering operator<=>(const Vertex& lhs, const Vertex& rhs){
	return lhs.dist <=> rhs.dist;
}

size_t Dijkstra(std::vector<bool>& maze, Point start, Point end, int width){
	std::vector<size_t> distances(maze.size(), UINT64_MAX);
	std::unordered_map<size_t, size_t> prev;

	std::priority_queue<Vertex> q;
	// Enter start to queue
	size_t id = start.row * width + start.col;
	distances[id] = 0;
	q.push({id, 0});

	while(!q.empty()){
		// Grab with smallest distance
		Vertex v = q.top();
		q.pop();

		// Determine eligable neighbours and score
		if(maze[v.id - width]){
			size_t dist = v.dist;
			if(prev.contains(v.id) && prev[v.id] == v.id + width) // Same direction
				dist += 1;
			else 
				dist += 1001;

			if(distances[v.id - width] > dist){
				q.push({v.id - width , dist});
				distances[v.id - width] = dist;
				prev[v.id - width] = v.id;
			}
		}

		if(maze[v.id + 1]){
			size_t dist = v.dist;
			if(!prev.contains(v.id) || prev[v.id] == v.id - 1) // Same direction
				dist += 1;
			else 
				dist += 1001;

			if(distances[v.id+1] > dist){
				q.push({v.id +1, dist});
				distances[v.id + 1] = dist;
				prev[v.id+1] = v.id;
			}
		}
		
		if(maze[v.id + width]){
			size_t dist = v.dist;
			if(prev.contains(v.id) && prev[v.id] == v.id - width) // Same direction
				dist += 1;
			else 
				dist += 1001;

			if(distances[v.id + width] > dist){
				q.push({v.id + width , dist});
				distances[v.id + width] = dist;
				prev[v.id + width] = v.id;
			}
		}

		if(maze[v.id - 1]){
			size_t dist = v.dist;
			if(prev.contains(v.id) && prev[v.id] == v.id + 1) // Same direction
				dist += 1;
			else 
				dist += 1001;

			if(distances[v.id-1] > dist){
				q.push({v.id - 1, dist});
				distances[v.id - 1] = dist;
				prev[v.id - 1] = v.id;
			}
		}
	}

	std::unordered_set<size_t> path;
	size_t prev_id = end.row * width + end.col; 
	while(prev.contains(prev_id)){
		path.insert(prev_id);
		prev_id = prev[prev_id];
	}

	// Print solved maze
	for(size_t i = 0; i < maze.size(); ++i){
		if(path.contains(i)) std::cout << "\u001b[31m";
		std::cout << (maze[i] ? '.' : '#') << "\u001b[0m";
		if(i > 0 && i % width == width - 1) std::cout << std::endl;
	}

	return distances[end.row * width + end.col];
}
struct Edge{
	size_t length;
	size_t target;
};

struct Node{
	size_t id;
	size_t dist;
	size_t prev;
};
std::strong_ordering operator<=>(const Node& lhs, const Node& rhs){
	return lhs.dist <=> rhs.dist;
}

bool IsStraight(std::vector<bool>& maze, size_t id, size_t width){
	return  !maze[id] || !((maze[id+1] && maze[id+width]) ||
		     (maze[id+1] && maze[id-width]) ||
		     (maze[id-1] && maze[id+width]) ||
		     (maze[id-1] && maze[id-width]));
}

bool connectedRow(std::vector<bool>& maze, size_t row, size_t i, size_t j, size_t width){
	for(size_t c = i; c <= j; ++c){
		size_t id = row * width + c;
		if(!maze[id]) return false;
	}
	return true;
}
bool connectedCol(std::vector<bool>& maze, size_t col, size_t i, size_t j, size_t width){
	for(size_t r = i; r <= j; ++r){
		size_t id = r * width + col;
		if(!maze[id]) return false;
	}
	return true;
}

size_t DijkstraAll(std::vector<bool>& maze, Point start, Point end, size_t width){


	// Find all the non straight pieces
	size_t height = maze.size()/width;
	std::vector<Point> vertices;

	// Add start and end vertices
	vertices.push_back(start);
	vertices.push_back(end);
	
	for(size_t row = 0; row < height; ++row){
		for(size_t col = 0; col < width; ++col){
			size_t i = row *width + col;
			if(row == start.row && col == start.col) continue;
			if(row == end.row && col == end.col) continue;

			if(!IsStraight(maze, i, width)){
				std::cout << "\u001b[31m";
				vertices.push_back({row, col});
			}
			std::cout << (maze[i] ? "." : "#") << "\u001b[0m";
		}
		std::cout << std::endl;
	}

	std::vector<std::vector<Edge>> adj(vertices.size());

	for(size_t i = 0; i < vertices.size(); ++i){
		for(size_t j = i + 1; j < vertices.size(); ++j){
			Point a = vertices[i];
			Point b = vertices[j];

			if(a.row == b.row && a.col == b.col) continue;

			if(a.row == b.row && connectedRow(maze, a.row, 
				std::min(a.col, b.col), std::max(a.col, b.col), width)){
				size_t dist = std::abs((long int)b.col - (long int)a.col);
				adj[i].push_back({dist, j}); 
				adj[j].push_back({dist, i}); 
			}else if(a.col == b.col && connectedCol(maze, a.col, 
					std::min(a.row, b.row), std::max(a.row, b.row),  width)){
				size_t dist = std::abs((long int)b.row - (long int)a.row);
				adj[i].push_back({dist, j}); 
				adj[j].push_back({dist, i}); 
			}
		}
	}

	// Dijkstra's algorithm
	std::vector<size_t> distances(vertices.size(), UINT64_MAX);
	std::unordered_map<size_t, std::unordered_set<size_t>> prev;

	std::priority_queue<Node> q;


	distances[0] = 0;
	q.push({0, 0, 0});

	while(!q.empty()){
		Node v = q.top();
		q.pop();

		size_t sr = vertices[v.prev].row;
		size_t sc = vertices[v.prev].col;

		// Add neighbours
		for(const Edge& e: adj[v.id]){
			size_t r = vertices[e.target].row;
			size_t c = vertices[e.target].col;
			
			size_t penalty = sr == r || sc == c ? 0 : 1000;

			size_t dist = e.length + distances[v.id] + penalty; // TODO:: add turn penalty

			if(distances[e.target] > dist){
				distances[e.target] = dist;
				q.push({e.target, dist, v.id});
				prev[e.target] = {v.id};
			}else if(distances[e.target] == dist){
				prev[e.target].insert(v.id);
			}
		}
	}

	// Reconstruct path
	std::unordered_set<size_t> path;
	std::unordered_set<size_t> visited;
	std::queue<size_t> p;

	p.push(1);
	while(!p.empty()){
		size_t i = p.front();
		p.pop();

		visited.insert(i);
		
		for(const auto& v : prev[i]){
			if(!visited.contains(v)) p.push(v);
			// Add intermediates
			size_t r1 = std::min(vertices[i].row, vertices[v].row);
			size_t r2 = std::max(vertices[i].row, vertices[v].row);
			size_t c1 = std::min(vertices[i].col, vertices[v].col);
			size_t c2 = std::max(vertices[i].col, vertices[v].col);
			for(size_t row = r1; row <= r2; ++row){
				for(size_t col = c1; col <= c2; ++col){
					path.insert(row * width + col);
				}
			}
		}
		std::cout << "  " << p.size() << std::endl;
	}
	for(size_t i = 0; i < maze.size(); ++i){
		if(i == 0 || i % width == 0) std::cout << std::setw(3) << i/width << " " ;
		if(path.contains(i)) std::cout << "\u001b[31m";
		std::cout << (maze[i] ? 'o' : '#') << "\u001b[0m";
		if(i > 0 && i % width == width - 1) std::cout << std::endl;
	}
	

	return path.size();
}

void aoc::solutions::day16(char* path){
	std::ifstream fs(path);
	
	std::vector<bool> maze;

	std::string line;
	Point start;
	Point end;

	size_t row = 0;
	size_t width;

	while(getline(fs, line)){
		width = line.length();
		for(size_t col = 0; col < line.length(); ++col){
			char c = line[col];
			std::cout << c;
			if(c == 'E') end = {row, col};
			if(c == 'S') start = {row, col};
			maze.push_back(!(c == '#'));
		}
		++row;
		std::cout << std::endl;
	}

	std::cout << "START: " << start.row << "," << start.col << std::endl;
	std::cout << "END: " << end.row << "," << end.col << std::endl;

	size_t res1 = Dijkstra(maze, start, end, width);
	std::cout << "SOLUTION 1: " << res1 << std::endl;

	size_t res2 = DijkstraAll(maze, start, end, width);
	std::cout << "SOLUTION 2: " << res2 << std::endl;
}

