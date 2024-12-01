#include <iostream>
#include <chrono>

#include <day1.h>

int main(int argc, char** argv){
	if(argc > 3 || argc < 3) return 1;

	int day = std::stoi(argv[1]);
	char* path = argv[2];

	std::cout << "======== AoC 2024 ========" <<std::endl;
	std::cout << "DAY: " << day <<std::endl;
	
	std::chrono::time_point start = std::chrono::high_resolution_clock::now();
	std::chrono::time_point end = std::chrono::high_resolution_clock::now();
	switch(day){
		case 1:

			aoc::day1::solve(path);

			end = std::chrono::high_resolution_clock::now();
			break;
	}

	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	std::cout << "TIME: " << time.count() << "μs" << std::endl;

	return 0;
}
