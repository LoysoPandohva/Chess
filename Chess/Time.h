#pragma once
#include <iostream>
#include <chrono>
#include <string>

class Time {
public:
	Time(std::string _name): name(_name) {
		start = std::chrono::high_resolution_clock::now();
	}

	~Time() {
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		std::cout << name << " - " << duration.count() << " sec." << std::endl;
	}
private:
	std::string name;
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};