#include <iostream>
#include <chrono>
#include <solutions.h>

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
			aoc::solutions::day1(path);
			break;
		case 2:
			aoc::solutions::day2(path);
			break;
		case 3:
			aoc::solutions::day3(path);
			break;
		case 4:
			aoc::solutions::day4(path);
			break;
		case 5:
			aoc::solutions::day5(path);
			break;
		case 6:
			aoc::solutions::day6(path);
			break;
		case 7:
			aoc::solutions::day7(path);
			break;
		case 8:
			aoc::solutions::day8(path);
			break;
		case 9:
			aoc::solutions::day9(path);
			break;
		case 10:
			aoc::solutions::day10(path);
			break;
		case 11:
			aoc::solutions::day11(path);
			break;
		case 12:
			aoc::solutions::day12(path);
			break;
		case 13:
			aoc::solutions::day13(path);
			break;
		case 14:
			aoc::solutions::day14(path);
			break;
		case 15:
			aoc::solutions::day15(path);
			break;
		case 16:
			aoc::solutions::day16(path);
			break;
		case 17:
			aoc::solutions::day17(path);
			break;
		case 18:
			aoc::solutions::day18(path);
			break;
	}

	end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	std::cout << "TIME: " << time.count() << "μs" << std::endl;

	return 0;
}
