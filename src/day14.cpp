#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <solutions.h>

struct Vec2{
	int x;
	int y;
};

struct Robot{
	Vec2 pos;
	Vec2 vel;
};

void aoc::solutions::day14(char* path){
	std::ifstream fs(path);
	std::string p;
	std::string v;

	int width = 101;
	int height = 103;

	std::vector<Robot> robots;

	while(fs >> p >> v){
		Robot b;
		auto ptr = p.find(',');
		b.pos.x = std::stoi(p.substr(2, ptr));
		b.pos.y = std::stoi(p.substr(ptr+1, p.size()-ptr));
		ptr = v.find(',');
		b.vel.x = std::stoi(v.substr(2, ptr));
		b.vel.y = std::stoi(v.substr(ptr+1, v.size()-ptr));

		robots.push_back(b);
	}


	int quadrants[4] = {0,0,0,0};
	int seconds = 100;

	std::vector<int> map(width*height, 0);

	for(const Robot robot: robots){
		std::cout << "ROBOT: [" << robot.pos.x << "," << robot.pos.y << "] , ["
				  << robot.vel.x << "," << robot.vel.y << "]";
		int x = (robot.pos.x + seconds * robot.vel.x)%width;
		int y = (robot.pos.y + seconds * robot.vel.y)%height;
		if(x < 0) x += width;
		if(y < 0) y += height;

		std::cout << "->[" << x << "," << y << "]" << std::endl;

		int id = y * width + x;
		map[id] += 1;

		// Add to quadrants
		if(x < width / 2 && y < height/2) ++quadrants[0];
		else if(x < width / 2 && y > height / 2) ++quadrants[1];
		else if(x > width / 2 && y < height/2) ++quadrants[2];
		else if(x > width / 2 && y > height / 2) ++quadrants[3];
	}

	for(int row = 0; row < height; ++row){
		for(int col =0; col < width; ++col){
			int id = row * width + col;
			std::cout << (map[id] == 0 ? "." : std::to_string(map[id]));
		}
		std::cout << std::endl;
	}

	int safety = quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
	std::cout << "SOLUTION 1: " << safety << std::endl;
	
}
