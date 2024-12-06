#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <solutions.h>

bool HasIntersection(std::vector<int> lhs, std::vector<int> rhs){
	std::unordered_set<int> a(lhs.begin(), lhs.end());
	std::unordered_set<int> b(rhs.begin(), rhs.end());

	std::vector<int> c;
	std::set_intersection(a.begin(), a.end(),
	    				  b.begin(), b.end(),
						  std::back_inserter(c));
	return c.size() > 0;
}

std::string Fix(std::string line, std::vector<std::vector<int>>& order){
	std::istringstream ss(line);
	std::string token;

	std::vector<int> manual;

	// Init manual
	while(std::getline(ss, token, ',')){
		int val = std::stoi(token);
		std::vector<int> & before = order[val];
		// Determine where to place the new item
		size_t i = 0;
		while(i < manual.size() && std::find(before.begin(), before.end(), manual[i]) != before.end()){
			++i;
		}
		if(i == manual.size()){
			manual.push_back(val);
		}else{
			manual.insert(manual.begin() + i, val);
		}
	}

	std::reverse(manual.begin(), manual.end());

	//Build string
	std::string res;

	for(const int v: manual){
		res += std::to_string(v);
		res += ",";
	}

	return res.substr(0, res.length()-1);

}

bool IsValid(std::string line, std::vector<std::vector<int>>& order){
	bool res = true;
	std::string token;
	std::istringstream ss(line);
	std::unordered_set<int> prev_tokens;

	while(std::getline(ss, token, ',')){
		int val = std::stoi(token);
		
		for(const int v : order[val]){
			if(prev_tokens.contains(v)){
				return false;
			}
		}

		prev_tokens.insert(val);	
	}
	return res;
}

void aoc::solutions::day5(char* path){
	std::ifstream fs(path, std::ios::in);

	std::vector<std::vector<int>> order(100);

	std::string line = "";
	int sum = 0;
	int sum1 = 0;
	while(std::getline(fs, line)){
		if(line.length() == 0) continue;
		if(line.length() == 5){
			int a = std::stoi(line.substr(0, 2));
			int b = std::stoi(line.substr(3, 2)); 
			std::cout << a << " ≻ " << b << std::endl;
			order[a].push_back(b);
		}else{
			bool valid = IsValid(line, order);
			if(valid){
				sum += std::stoi(line.substr((line.length()/2-1),2));
				std::cout << "\u001b[32m✓\u001b[0m " << line << std::endl;	
			}else{
				// Fixing time
				std::string s = Fix(line, order);
				sum1 += std::stoi(s.substr((s.length()/2-1),2));
				std::cout << "\u001b[31m✗\u001b[0m " << line <<
					         " -> " << s << std::endl;	
				
			}
		}
	}



	std::cout << "SOLUTION 1: " << sum << std::endl;
	std::cout << "SOLUTION 2: " << sum1 << std::endl;
}
