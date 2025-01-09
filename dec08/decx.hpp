#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES
#include <unordered_map>


#define CURRENT_DAY 08

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

struct Coordinate {
	int x;
	int y;
};


// first attempt: 1:15:31
// Second attempt: 33:33
// first try
int pos_hash(int x, int y) {
	return x + y * 100;
}

int find(std::vector<int> vec, int value) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == value) {
			return i;
		}
	}
	return -1;
}

int count_antinodes(std::unordered_map<char, std::vector<Coordinate>> antennas, int width, int height) {
	std::vector<int> unique_positions;
	for (auto const& i : antennas) {
		auto coordinate_vector = &(i.second);
		for (int j = 0; j < i.second.size() - 1; j++) {
			Coordinate start = i.second[j];
			for (int k = j + 1; k < i.second.size(); k++) {
				Coordinate end = i.second[k];
				int x_diff = start.x - end.x;
				int y_diff = start.y - end.y;

				int new_x1 = start.x + x_diff;
				int new_y1 = start.y + y_diff;
				int new_x2 = end.x - x_diff;
				int new_y2 = end.y - y_diff;
				if (in_range(new_x1, 0, width - 1) &&
					in_range(new_y1, 0, height - 1) &&
					find(unique_positions, pos_hash(new_x1, new_y1)) == -1) {
						unique_positions.push_back(pos_hash(new_x1, new_y1));
					}

				if (in_range(new_x2, 0, width - 1) &&
					in_range(new_y2, 0, height - 1) &&
					find(unique_positions, pos_hash(new_x2, new_y2)) == -1) {
						unique_positions.push_back(pos_hash(new_x2, new_y2));
					}
			}
		}
	}
	return unique_positions.size();
}


// First attempt: 17~ min
// first try.
int count_antinodes2(std::unordered_map<char, std::vector<Coordinate>> antennas, int width, int height) {
	std::vector<int> unique_positions;
	for (auto const& i : antennas) {
		auto coordinate_vector = &(i.second);
		for (int j = 0; j < i.second.size() - 1; j++) {
			Coordinate start = i.second[j];

			// CHeck all but the last antenna for inclusion
			if (find(unique_positions, pos_hash(start.x, start.y)) == -1) {
				unique_positions.push_back(pos_hash(start.x, start.y));
			}
			for (int k = j + 1; k < i.second.size(); k++) {
				Coordinate end = i.second[k];
				int x_diff = start.x - end.x;
				int y_diff = start.y - end.y;

				int new_x1 = start.x + x_diff;
				int new_y1 = start.y + y_diff;
				int new_x2 = end.x - x_diff;
				int new_y2 = end.y - y_diff;
				while (in_range(new_x1, 0, width - 1) && in_range(new_y1, 0, height - 1)) {
					if (find(unique_positions, pos_hash(new_x1, new_y1)) == -1) {
						unique_positions.push_back(pos_hash(new_x1, new_y1));
					}
					new_x1 += x_diff;
					new_y1 += y_diff;
				}

				while (in_range(new_x2, 0, width - 1) && in_range(new_y2, 0, height - 1)) {
					if (find(unique_positions, pos_hash(new_x2, new_y2)) == -1) {
						unique_positions.push_back(pos_hash(new_x2, new_y2));
					}
					new_x2 -= x_diff;
					new_y2 -= y_diff;
				}
			}
		}
		// Check the last antenna for inclusion
		if (find(unique_positions, pos_hash(i.second.back().x, i.second.back().y)) == -1) {
			unique_positions.push_back(pos_hash(i.second.back().x, i.second.back().y));
		}
	}
	return unique_positions.size();
}

static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	std::unordered_map<char, std::vector<Coordinate>> antennas;

	int line_num = 0;
	while (getline (MyReadFile, myText)) {
		for (int i = 0; i < myText.size(); i++) {
			if (myText[i] != '.' && myText[i] != '#') {
				if (antennas.find(myText[i]) == antennas.end()) {
					antennas[myText[i]] = std::vector<Coordinate>{{i, line_num}};
				} else {
					antennas[myText[i]].push_back({i, line_num});
				}
			}
		}
		line_num++;
	}

	res += count_antinodes(antennas, myText.size(), line_num);

	MyReadFile.close();

	return res;
}

static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	std::unordered_map<char, std::vector<Coordinate>> antennas;

	int line_num = 0;
	while (getline (MyReadFile, myText)) {
		for (int i = 0; i < myText.size(); i++) {
			if (myText[i] != '.' && myText[i] != '#') {
				if (antennas.find(myText[i]) == antennas.end()) {
					antennas[myText[i]] = std::vector<Coordinate>{{i, line_num}};
				} else {
					antennas[myText[i]].push_back({i, line_num});
				}
			}
		}
		line_num++;
	}

	res += count_antinodes2(antennas, myText.size(), line_num);

	MyReadFile.close();

	return res;
}
} // namespace end

void NAMEDAY(solve, CURRENT_DAY)() {
	auto start = std::chrono::high_resolution_clock::now();
	print_solve1(NAMEDAY(dec, CURRENT_DAY)::solve1(), 8);
	auto mid = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);
	std::cout << "Time taken: "  << duration1.count() / 1000.0 << " ms.\n";
	print_solve2(NAMEDAY(dec, CURRENT_DAY)::solve2(), 8);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - mid);
	std::cout << "Time taken: "  << duration2.count() / 1000.0 << " ms.\n";
}

#undef NAMEDAY
#undef MACRO1
#undef MACRO3
#undef CURRENT_DAY
