#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <solutions.h>
#include <map>
#include <cmath>
#include <cstdint>

struct Machine{
	int ax, ay; // Button A
	int bx, by; // Button B
	int px, py; // Prize
};

struct ClawMove{
	int cost;
	int step;
};

bool operator<(const ClawMove& lhs, const ClawMove& rhs){
	if(lhs.cost == rhs.cost) return lhs.step < rhs.step;
	else return lhs.cost < rhs.cost;
}

bool operator>(const ClawMove& lhs, const ClawMove& rhs){
	if(lhs.cost == rhs.cost) return lhs.step > rhs.step;
	else return lhs.cost > rhs.cost;
}

bool operator==(const ClawMove& lhs, const ClawMove& rhs){
	return lhs.cost == rhs.cost && lhs.step == rhs.step;
}


int MinCost(Machine& m){
	int mincost = INT32_MAX;
	for(int a = 1; a <= 100; ++a){
		for(int b = 1; b <= 100; ++b){
			if(a * m.ax + b * m.bx == m.px &&
			   a * m.ay + b * m.by == m.py){
				mincost = std::min(a*3 + b, mincost);
			}
		}
	}

	return mincost;
}

long int SpicyMinCost(Machine& m){
	
	long int px = m.px + 10000000000000;
	long int py = m.py + 10000000000000;
	
	double det = m.ax*m.by-m.bx*m.ay;

	double a = std::abs(m.ax)/det;
	double b = std::abs(m.bx)/det;
	double c = std::abs(m.ay)/det;
	double d = std::abs(m.by)/det;

	double A = px*d + py*-b;
	double B = px*-c + py*a;

	double da = std::abs(A - std::round(A));
	double db = std::abs(B - std::round(B));
	double e = 0.0001;

	long int mincost = da < e && db < e ? std::round(A)*3+std::round(B) : INT64_MAX;

	return mincost;
}

void aoc::solutions::day13(char* path){
	std::ifstream fs(path);
	std::string ax, ay;
	std::string bx, by;
	std::string px, py;

	int mincost = 0;
	long int mincost2 = 0;
	while(fs >> ax >> ax >> ax >> ay
			 >> bx >> bx >> bx >> by
			 >> px >> px >> py){
		Machine m = {
			std::stoi(ax.substr(2, ax.size()-3)),
			std::stoi(ay.substr(2, by.size()-2)),
			std::stoi(bx.substr(2, bx.size()-3)),
			std::stoi(by.substr(2, by.size()-2)),
			std::stoi(px.substr(2, px.size()-3)),
			std::stoi(py.substr(2, py.size()-2)),
		};
		
		int cost = MinCost(m);
		if(cost != INT32_MAX) 
			mincost += cost;

		long int cost2 = SpicyMinCost(m);
		if(cost2 != INT64_MAX)
			mincost2 += cost2;
	}
	std::cout << "SOLUTION 1: " << mincost << std::endl;
	std::cout << "SOLUTION 2: " << mincost2 << std::endl;
}
