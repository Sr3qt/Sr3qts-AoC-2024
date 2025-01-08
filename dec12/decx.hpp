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

int score_hash(int x, int y) {
	return x + (y << 16);
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


			// std::cout << "Continuneing!\n";
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
				std::vector<int> temp;
				int perimeter = count_area(map[j][i], i, j, visited, map);
				temp.reserve(visited.size() + globally_visited.size());
				temp.insert(temp.end(), globally_visited.begin(), globally_visited.end());
				temp.insert(temp.end(), visited.begin(), visited.end());
				temp.swap(globally_visited);
				// std::cout << i << ", " << j << "\n" << visited.size() * perimeter << "\n";
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
