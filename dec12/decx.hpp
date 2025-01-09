#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES
#include <bitset>


#define CURRENT_DAY 12

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

enum Side {
	LEFT = 1,
	UP = 2,
	RIGHT = 4,
	DOWN = 8,
};

int score_hash(int x, int y) {
	return x + (y << 16);
}

// Returns perimeter of a block given a letter and start position.
// Read visited.size() to see block area.
int count_area2(char letter, int x, int y, int* count, std::vector<std::vector<bool>>& visited, std::vector<std::vector<int>>& sides, std::vector<std::string>& map) {
	int res = 0;
	const int combs[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
	const int dirs[4] = {LEFT, UP, RIGHT, DOWN};
	const Range x_range = {0, int(map[0].size()) - 1}; // inclusive ranges of valid indices
	const Range y_range = {0, int(map.size()) - 1};
	visited[y][x] = true;
	sides[y][x] = 0;
	// std::cout << x << ", " << y << ". ";
	std::vector<int> to_visit;
	std::vector<int> other_sides;
	(*count)++;
	for (int i = 0; i < 8; i += 2) {
		int x2 = x + combs[i];
		int y2 = y + combs[i + 1];
		if (in_range(x2, x_range) && in_range(y2, y_range) && map[y2][x2] == letter) {
			if (!visited[y2][x2]) {
				to_visit.push_back(x2);
				to_visit.push_back(y2);
			} else {
				other_sides.push_back(sides[y2][x2]);
			}
		} else {
			sides[y][x] += dirs[i / 2];
		}
	}

	// A side int's 4 least significant digits tell you which sides it has.
	// If we are in-between two letters with same sides, and current letter has those sides as well,
	// then we *know* that we have double counted those sides.
	// A side can only be double counted once, we can detect this and remove one count.
	int temp_int = sides[y][x];
	int check = 0b1111;
	for (int i = 0; i < other_sides.size(); i++) {
		temp_int ^= (sides[y][x] & (other_sides[i]));
		int record = other_sides[i];
		for (int j = i + 1; j < other_sides.size(); j++) {
			res -= std::__popcount(record & other_sides[j] & sides[y][x]);
			if (record & other_sides[j]) {
				// Since 3 numbers have the same bit set, xoring them sequentially results in true
				// when we want false. turn off corresponding bit in checker.
				check ^= record & other_sides[j];
				break;
			}
		}
	}

	res += std::__popcount(temp_int & check);
	// std::cout << std::__popcount(temp_int & check) << "\n";

	for (int i = 0; i < to_visit.size(); i += 2) {
		// Need to double check that a position hasn't already been recursively checked.
		if (!visited[to_visit[i + 1]][to_visit[i]]) {
			res += count_area2(letter, to_visit[i], to_visit[i + 1], count, visited, sides, map);

		}
	}
	return res;
}

// Returns perimeter of a block given a letter and start position.
// Read count to see block area.
int count_area(char letter, int x, int y, int* count, std::bitset<140> (&visited)[140], std::vector<std::string>& map) {
	int res = 0;
	const int combs[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
	const Range x_range = {0, int(map[0].size()) - 1}; // inclusive ranges of valid indices
	const Range y_range = {0, int(map.size()) - 1};
	visited[y][x] = 1;
	(*count)++;
	for (int i = 0; i < 8; i += 2) {
		int x2 = x + combs[i];
		int y2 = y + combs[i + 1];
		if (in_range(x2, x_range) && in_range(y2, y_range) && map[y2][x2] == letter) {
			if (!visited[y2][x2]) {
				res += count_area(letter, x2, y2, count, visited, map);
			}
		} else {
			res++;
		}
	}
	return res;
}

// First attempt: 24:33
// Got it first try
static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	std::vector<std::string> map;
	std::bitset<140> visited[140];

	while (getline (MyReadFile, myText)) {
		map.push_back(myText);
	}

	MyReadFile.close();

	int count = 0;
	for (int i = 0; i < map[0].size(); i++) {
		for (int j = 0; j < map.size(); j++) {
			if (!visited[j][i]) {
				int perimeter = count_area(map[j][i], i, j, &count, visited, map);
				res += count * perimeter;
				count = 0;
			}
		}
	}

	return res;
}

// First attempt: 2:05:14
// Most of the time was spent figuring out how to do bit manip for overcount correction.
// first try: 811188, too high.
// second try: 805434, too low.
// Got it third try
static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	std::vector<std::string> map;
	std::vector<std::vector<bool>> visited;
	std::vector<std::vector<int>> sides;
	int count = 0;

	while (getline (MyReadFile, myText)) {
		map.push_back(myText);
	}

	MyReadFile.close();

	for (int i = 0; i < map.size(); i++) {
		std::vector<bool> temp1;
		std::vector<int> temp2;
		temp1.resize(map[0].size());
		temp2.resize(map[0].size());
		visited.push_back(temp1);
		sides.push_back(temp2);
	}

	for (int i = 0; i < map[0].size(); i++) {
		for (int j = 0; j < map.size(); j++) {
			if (!visited[j][i]) {
				int perimeter = count_area2(map[j][i], i, j, &count, visited, sides, map);
				// std::cout << map[j][i] << ": " << perimeter << ", " << count << "\n";
				res += count * perimeter;
				count = 0;
			}
		}
	}

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
