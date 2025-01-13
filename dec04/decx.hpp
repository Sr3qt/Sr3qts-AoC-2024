#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>

// NEW INCLUDES


#define CURRENT_DAY 04

// MACRO wizardry from https://stackoverflow.com/a/30114018, see comment
#define MACRO1(x, FOO) x##FOO
#define MACRO3(CURRENT_DAY, x) MACRO1(CURRENT_DAY, x)
#define NAMEDAY(name, x) MACRO3(name, x)


namespace NAMEDAY(dec, CURRENT_DAY) {

// first draft 26:10
// Make a arbitrary word, word search solver
// THis is too boring
int check_down(std::vector<std::string> map, int x, int y) {
	if (y >= map.size() - 3) return 0;
	return 1;
}

int check_up(std::vector<std::string> map, int x, int y) {
	if (y < 3) return 0;
	return 1;
}
int check_downleft(std::vector<std::string> map, int x, int y) {
	if (y >= map.size() - 3 || x < 3) return 0;
	return 1;
}
int check_downright(std::vector<std::string> map, int x, int y) {
	if (y >= map.size() - 3 || x > map.size() - 3) return 0;
	return 1;
}
int check_upleft(std::vector<std::string> map, int x, int y) {
	if (y < 3 || x < 3) return 0;
	return 1;
}
int check_upright(std::vector<std::string> map, int x, int y) {
	if (y < 3 || x > map.size() - 3) return 0;
	return 1;
}
int check_left(std::vector<std::string> map, int x, int y) {
	if (x < 3) return 0;
	return 1;
}
int check_right(std::vector<std::string> map, int x, int y) {
	if (x > map.size() - 3) return 0;
	return 1;
}

int check_all(std::vector<std::string> map, int x, int y) {
	int res = 0;
	res += check_up(map, x, y);
	res += check_upleft(map, x, y);
	res += check_upright(map, x, y);
	res += check_downleft(map, x, y);
	res += check_downright(map, x, y);
	res += check_left(map, x, y);
	res += check_right(map, x, y);
	return res;
}

// first try: 41:47
int check_index(std::vector<std::string> map, int x, int y, std::string word) {
	int res = 0;

	bool skip = false;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) {continue;}
			if (!(in_range(i * (word.size() - 1) + x, 0, map[0].size() - 1) &&
				in_range(j * (word.size() - 1) + y, 0, map.size() - 1))) {
					continue;
			}
			for (int letter = 1; letter < word.size(); letter++) {
				// std::cout << "Tested index: " << x + i * letter << ", " << y + j * letter <<
				// map[y + j * letter][x + i * letter] << std::endl;
				if (!(word[letter] == map[y + j * letter][x + i * letter])) {
					skip = true;
					break;
				}
			}
			if (!skip) {
				res++;
			} else {
				skip = false;
			}
		}
	}
	return res;
}

int find_mas(std::vector<std::string> map, int x, int y) {
	if (x == 0 || x == map.size() - 1 || y == 0 || y == map.size() - 1) {
		return 0;
	}

	char pp = map[y + 1][x + 1];
	char np = map[y - 1][x + 1];
	char pn = map[y + 1][x - 1];
	char nn = map[y - 1][x - 1];

	if ((pp == 'M' || pp == 'S') &&
		(np == 'M' || np == 'S') &&
		(pn == 'M' || pn == 'S') &&
		(nn == 'M' || nn == 'S') &&
		(nn != pp) && (np != pn)
	) {
		return 1;
	}
	return 0;
}

static int solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind('/')) + "/data.txt");
	int res = 0;

	std::vector<std::string> word_search;
	while (getline (MyReadFile, myText)) {
		word_search.push_back(myText);
	}

	for (int i = 0; i < word_search.size(); i++) {
		for (int j = 0; j < word_search[0].size(); j++) {
			if (word_search[j][i] == 'X') {
				res += check_index(word_search, i, j, std::string("XMAS"));
			}
		}
	}

	MyReadFile.close();

	return res;
}

// first try: 8:15
static int solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind('/')) + "/data.txt");
	int res = 0;

	std::vector<std::string> word_search;
	while (getline (MyReadFile, myText)) {
		word_search.push_back(myText);
	}

	for (int i = 0; i < word_search.size(); i++) {
		for (int j = 0; j < word_search[0].size(); j++) {
			if (word_search[j][i] == 'A') {
				res += find_mas(word_search, i, j);
			}
		}
	}
	MyReadFile.close();

	return res;
}
} // namespace end

void NAMEDAY(solve, CURRENT_DAY)() {
	print_solve1(NAMEDAY(dec, CURRENT_DAY)::solve1(), CURRENT_DAY);
	print_solve2(NAMEDAY(dec, CURRENT_DAY)::solve2(), CURRENT_DAY);
}

#undef NAMEDAY
#undef MACRO1
#undef MACRO3
#undef CURRENT_DAY
