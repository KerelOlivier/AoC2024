#include <day2.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>

bool IsValid(int lhs, int rhs, int dir){
	int d = rhs - lhs;
	return std::signbit(d) == std::signbit(dir) && 
		std::abs(d) >= 1 && std::abs(d) <= 3;
}

void aoc::day2::solve(char* path){
	 // Parse input
	std::ifstream stream(std::string(path), std::ios::in);

	std::string line;
	int safe_cnt = 0;
	int safe_cnt2 = 0;
	while(std::getline(stream, line)){
		std::stringstream sstream(line);
		int curr, prev, last;
		bool safe = true;	 // Safe flag for part 1
		bool safe2 = true;	 // Safe flag for part 2
		bool skipped = false;
		int dir = 0;

		sstream >> prev;
		std::cout << prev << " ";
		while(sstream >> curr){
			dir+=std::signbit(curr - prev)? -1 : 1;
			std::cout << curr << " ";
			prev = curr;
		}

		// Check list for validity
		sstream = std::stringstream(line, std::ios_base::app | std::ios_base::out | std::ios_base::in);
		sstream >> prev;
		
		bool first = true;

		while(sstream >> curr){
			//std::cout << "[" << curr << "]";
			if(!IsValid(prev, curr, dir)){
				safe = false;
				if(!skipped){
					int tmp;
					if(sstream >> tmp){
						//std::cout << prev << "-" << curr << "-" << tmp;
						if(!IsValid(prev, tmp, dir)){ // Removing mid
							if(first){
								if(!IsValid(curr, tmp, dir)){
									safe2 = false;
								}else{
									// drop prev
									curr = tmp;
								}
							}else{
								//std::cout << last << "-" << prev << "-" << curr <<"-" << tmp << " ";
								if(!IsValid(last, curr, dir)){
									safe2 = false;
								}else{
									// drop prev
									prev = last;
									//std::cout << "(" << last << "," << prev << "," << curr << "," << tmp << ")";
								}
								std::stringstream str;
								str << std::to_string(tmp);
								std::string s;
								while(sstream >> s) str << " " << s;
								sstream = std::stringstream(str.str());
							}
						}else{
							curr = tmp;
						}
					}
					skipped = true;
				}else{
					safe2 =false;
				}
			}
			first = false;
			last = prev;
			prev = curr;
			
		}

		if(safe) ++safe_cnt;
		if(safe2) ++safe_cnt2;
		std::cout << " " << std::setw(40-line.length()) << 
			(safe ? "T" : "F") << 
			(safe2 ? "T" : "F") << 
			" " <<(std::signbit(dir) ? "<" : ">") << " " << dir << std::endl;
	}

	std::cout << "SOLUTION 1: " << safe_cnt << std::endl;
	std::cout << "SOLUTION 2: " << safe_cnt2 << std::endl;
}
