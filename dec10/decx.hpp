#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES


#define CURRENT_DAY 10

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

int score_hash(int x, int y) {
	return x + 100 * y;
}

// Can include a list of previously visited spots and stop looking early for optimization
void find_trailhead(int num, int x, int y, std::vector<std::string>& map, std::vector<int>& tops) {
	// if (num > 3) {return;}
	const int combs[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
	const Range x_range = {0, int(map[0].size()) - 1}; // inclusive ranges of valid indices
	const Range y_range = {0, int(map.size()) - 1};
	for (int i = 0; i < 8; i += 2) {
		int x2 = x + combs[i];
		int y2 = y + combs[i + 1];
		if (in_range(x2, x_range) && in_range(y2, y_range) && map[y2][x2] - '0' == num + 1) {
			// std::cout << map[y2][x2] - '0';
			if (num == 8) {
				// std::cout << "Found end!\n";
				if (find(tops, score_hash(x2, y2)) == -1) {
					tops.push_back(score_hash(x2, y2));
				}
				continue;
			}

			// std::cout << "Continuneing!\n";
			find_trailhead(num + 1, x2, y2, map, tops);
		}
	}
}

// Can include a list of previously visited spots and stop looking early for optimization
void find_trailhead2(int num, int x, int y, std::vector<std::string>& map, int& tops) {
	// if (num > 3) {return;}
	const int combs[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
	const Range x_range = {0, int(map[0].size()) - 1}; // inclusive ranges of valid indices
	const Range y_range = {0, int(map.size()) - 1};
	for (int i = 0; i < 8; i += 2) {
		int x2 = x + combs[i];
		int y2 = y + combs[i + 1];
		if (in_range(x2, x_range) && in_range(y2, y_range) && map[y2][x2] - '0' == num + 1) {
			// std::cout << map[y2][x2] - '0';
			if (num == 8) {
				// std::cout << "Found end!\n";
				tops++;
				continue;
			}

			// std::cout << "Continuneing!\n";
			find_trailhead2(num + 1, x2, y2, map, tops);
		}
	}
}

// First attempt: 48:19
// Got it first try
static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	std::vector<std::string> map;

	while (getline (MyReadFile, myText)) {
		map.push_back(myText);
	}

	MyReadFile.close();

	for (int i = 0; i < map[0].size(); i++) {
		for (int j = 0; j < map.size(); j++) {
			if (map[j][i] == '0') {
				// std::cout << i << ", " << j << "\n";
				std::vector<int> temp;
				find_trailhead(0, i, j, map, temp);
				res += temp.size();
			}
		}
	}

	return res;
}

// First attempt: 20 seconds
// All i needed was to remove my own duplicate-top check
static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	std::vector<std::string> map;

	while (getline (MyReadFile, myText)) {
		map.push_back(myText);
	}

	MyReadFile.close();

	for (int i = 0; i < map[0].size(); i++) {
		for (int j = 0; j < map.size(); j++) {
			if (map[j][i] == '0') {
				int temp = 0;
				find_trailhead2(0, i, j, map, temp);
				res += temp;
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
