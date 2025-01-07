#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES
#include <unordered_map>

#define CURRENT_DAY 11

// MACRO wizardry from https://stackoverflow.com/a/30114018, see comment
#define MACRO1(x, FOO) x##FOO
#define MACRO3(CURRENT_DAY, x) MACRO1(CURRENT_DAY, x)
#define NAMEDAY(name, x) MACRO3(name, x)

#ifndef OS_SEP
	#ifdef WIN32
	#define OS_SEP '\\'
	#else
	#define OS_SEP '/'
	#endif
#endif


namespace NAMEDAY(dec, CURRENT_DAY) {


// another optimization would be to have long int vector instead of string vector
void iterate(std::vector<std::string>& vec, std::vector<std::string>& out, int& size) {
	int offset = 0;
	for (int i = 0; i < size; i++) {
		auto item = vec[i];
		if (item == "0") {
			out[i + offset] = "1";
		} else if (item.size() % 2 == 0) {
			std::string right = std::to_string(stoull(item.substr(item.size() / 2)));
			out[i + offset] = item.substr(0, item.size() / 2);
			out[i + offset + 1] = right;
			offset++;
		} else {
			out[i + offset] = std::to_string(stoull(item) * 2024);
		}
	}
	size += offset;
}

// First attemp: 34:11
// Got it first try, however the answer was given after 45s ...
// Going to optimize
// After first optimizations, ran in 45~ms!
static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	getline (MyReadFile, myText);

	MyReadFile.close();

	auto temp = split(myText);
	std::vector<std::string> temp2;
	int running_count = temp.size();
	temp.resize(200000);
	temp2.resize(200000);

	for (int i = 0; i < 25; i++) {
		iterate(temp, temp2, running_count);
		temp.swap(temp2);
		// std::cout << running_count << std::endl;
	}

	res = running_count;
	return res;
}


// First attmempt: 54:11
// Recursive memoization was faster, but not the right approach.
// Searched online and it seems that grouping works better.
// After more researched i found a guy who also solved it using memoization.
// My implementation must be bugged, will try to fix.
long long recursive(
	long long num,
	int depth,
	std::unordered_map<long long, std::unordered_map<int, long long>>& memory) {

	// std::cout << "Called: " << num << ", " << depth << "\n";

	if (memory.find(num) != memory.end()) {
		// Value has already been calculated.
		if (memory[num].find(depth) != memory[num].end()) {
			// Value has already been calculated at this depth.
			// std::cout << "Remembered value!\n";
			return memory[num][depth];
		}
		// auto temp = recursive(num, depth + 1, memory);
		// memory[num] = {{depth, temp}};
		// return temp;
	}

	// Base case. Set number of steps
	if (depth == 30) {
		// std::cout << "base cas found\n";
		return 1 + int(!(floor(log10(num) + 1 % 2)));
	} else {
		// Recursively try to find solutions
		if (num == 0) {
			auto temp = recursive(1, depth + 1, memory);
			memory[num] = {{depth, temp}};
			return temp;
		}
		if ((long long)floor(log10(num) + 1) % 2 == 0) {
			auto item = std::to_string(num);
			auto right = std::to_string(stoull(item.substr(item.size() / 2)));
			auto left = item.substr(0, item.size() / 2);

			// If left and right are same, memoization will kick in. Calling twice is fine.
			auto temp1 = recursive(stoll(left), depth + 1, memory);
			auto temp2 = recursive(stoll(right), depth + 1, memory);
			memory[num] = {{depth, temp1 + temp2}};
			return temp1 + temp2;
		} else {
			auto temp = recursive(num * 2024, depth + 1, memory);
			memory[num] = {{depth, temp}};
			return temp;
		}
	}
}


// Need recursive memoization bullshit to complete
static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	getline (MyReadFile, myText);

	MyReadFile.close();

	std::unordered_map<long long, std::unordered_map<int, long long>> memory;
	auto temp = split(myText);
	for (auto const& num : temp) {
		res += recursive(stoll(num), 0, memory);
	}
	// std::vector<std::string> temp2;
	// int running_count = temp.size();
	// temp.resize(200000);
	// temp2.resize(200000);

	// for (int i = 0; i < 25; i++) {
	// 	iterate(temp, temp2, running_count);
	// 	temp.swap(temp2);
	// 	std::cout << running_count << std::endl;
	// }

	// res = recursive();
	return res;
}
} // namespace end

void NAMEDAY(solve, CURRENT_DAY)() {
	auto start = std::chrono::high_resolution_clock::now();
	print_solve1(NAMEDAY(dec, CURRENT_DAY)::solve1(), CURRENT_DAY);
	auto mid = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);
	std::cout << "Time taken: "  << duration1.count() / 1000.0 << " ms.\n";
	print_solve2(NAMEDAY(dec, CURRENT_DAY)::solve2(), CURRENT_DAY);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - mid);
	std::cout << "Time taken: "  << duration2.count() / 1000.0 << " ms.\n";
}

#undef NAMEDAY
#undef MACRO1
#undef MACRO3
#undef CURRENT_DAY
