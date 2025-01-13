#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>

// NEW INCLUDES


#define CURRENT_DAY 00

// MACRO wizardry from https://stackoverflow.com/a/30114018, see comment
#define MACRO1(x, FOO) x##FOO
#define MACRO3(CURRENT_DAY, x) MACRO1(CURRENT_DAY, x)
#define NAMEDAY(name, x) MACRO3(name, x)

// 36:00 for manual attempt, got it second try, was off by one *classic*

namespace NAMEDAY(dec, CURRENT_DAY) {
static int solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind('/')) + "/data.txt");
	int res = 0;


	while (getline (MyReadFile, myText)) {

	}

	MyReadFile.close();

	return res;
}

static int solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind('/')) + "/data.txt");
	int res = 0;


	while (getline (MyReadFile, myText)) {

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
