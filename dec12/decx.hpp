#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES


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
int count_area2(char letter, int x, int y, std::vector<int>& visited, std::vector<int>& sides, std::vector<std::string>& map) {
	int res = 0;
	const int combs[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
	const int dirs[4] = {LEFT, UP, RIGHT, DOWN};
	const Range x_range = {0, int(map[0].size()) - 1}; // inclusive ranges of valid indices
	const Range y_range = {0, int(map.size()) - 1};
	visited.push_back(score_hash(x, y));
	sides.push_back(0);
	// std::cout << x << ", " << y << ". ";
	std::vector<int> to_visit;
	std::vector<int> other_sides;
	for (int i = 0; i < 8; i += 2) {
		int x2 = x + combs[i];
		int y2 = y + combs[i + 1];
		if (in_range(x2, x_range) && in_range(y2, y_range) && map[y2][x2] == letter) {
			// std::cout << "Found end!\n";
			int pos = find(visited, score_hash(x2, y2));
			if (pos == -1) {
				to_visit.push_back(x2);
				to_visit.push_back(y2);
			} else {
				other_sides.push_back(sides[pos]);
			}
		} else {
			sides.back() += dirs[i / 2];
		}
	}

	// A side int's 4 least significant digits tell you which sides it has.
	// If we are in-between two letters with same sides, and current letter has those sides as well,
	// then we *know* that we have double counted those sides.
	// A side can only be double counted once, we can detect this and remove one count.
	int temp_int = sides.back();
	int check = 0b1111;
	for (int i = 0; i < other_sides.size(); i++) {
		temp_int ^= (sides.back() & (other_sides[i]));
		int record = other_sides[i];
		for (int j = i + 1; j < other_sides.size(); j++) {
			res -= std::__popcount(record & other_sides[j] & sides.back());
			if (record & other_sides[j]) {
				// Since 3 numbers have the same bit set, xoring them sequentially results in true
				// when we want false. turn off corresponding bit in checker.
				check ^= record & other_sides[j];
				break;
			}
		}
	}

	res += std::__popcount(temp_int & check);

	for (int i = 0; i < to_visit.size(); i += 2) {
		// Need to double check that a position hasn't already been recursively checked.
		if (find(visited, score_hash(to_visit[i], to_visit[i + 1])) == -1) {
			res += count_area2(letter, to_visit[i], to_visit[i + 1], visited, sides, map);

		}
	}
	return res;
}

// Returns area of a block given a letter and start position.
// Read visited.size() to see block area.
int count_area(char letter, int x, int y, std::vector<int>& visited, std::vector<std::string>& map) {
	int res = 0;
	const int combs[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
	const Range x_range = {0, int(map[0].size()) - 1}; // inclusive ranges of valid indices
	const Range y_range = {0, int(map.size()) - 1};
	visited.push_back(score_hash(x, y));
	for (int i = 0; i < 8; i += 2) {
		int x2 = x + combs[i];
		int y2 = y + combs[i + 1];
		if (in_range(x2, x_range) && in_range(y2, y_range) && map[y2][x2] == letter) {
			// std::cout << "Found end!\n";
			if (find(visited, score_hash(x2, y2)) == -1) {
				res += count_area(letter, x2, y2, visited, map);
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
	std::vector<int> globally_visited;
	// globally_visited.reserve(140 * 140);

	while (getline (MyReadFile, myText)) {
		map.push_back(myText);
	}

	MyReadFile.close();

	for (int i = 0; i < map[0].size(); i++) {
		for (int j = 0; j < map.size(); j++) {

			if (find(globally_visited, score_hash(i, j)) == -1) {
				std::vector<int> visited;
				std::vector<int> temp;
				int perimeter = count_area(map[j][i], i, j, visited, map);
				// std::cout << map[j][i] << ": " << perimeter << " * " << visited.size() << "\n";
				temp.reserve(visited.size() + globally_visited.size());
				temp.insert(temp.end(), globally_visited.begin(), globally_visited.end());
				temp.insert(temp.end(), visited.begin(), visited.end());
				temp.swap(globally_visited);
				// globally_visited.insert(globally_visited.end(), visited.begin(), visited.end());
				// std::cout << i << ", " << j << "\n" << visited.size() * perimeter << "\n";
				res += visited.size() * perimeter;
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
	std::vector<int> globally_visited;

	while (getline (MyReadFile, myText)) {
		map.push_back(myText);
	}

	MyReadFile.close();

	for (int i = 0; i < map[0].size(); i++) {
		for (int j = 0; j < map.size(); j++) {

			if (find(globally_visited, score_hash(i, j)) == -1) {
				std::vector<int> visited;
				std::vector<int> sides;
				std::vector<int> temp;
				int perimeter = count_area2(map[j][i], i, j, visited, sides, map);
				temp.reserve(visited.size() + globally_visited.size());
				temp.insert(temp.end(), globally_visited.begin(), globally_visited.end());
				temp.insert(temp.end(), visited.begin(), visited.end());
				temp.swap(globally_visited);
				res += visited.size() * perimeter;
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
