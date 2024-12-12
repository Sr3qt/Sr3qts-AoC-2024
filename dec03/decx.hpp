#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>

// NEW INCLUDES


#define CURRENT_DAY 03

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
int find_muls(std::string line) {
	int res = 0;
	int begin = 0;

	while (line.find("mul(", begin) != std::string::npos) {
		int start = line.find("mul(", begin) + 3;
		int comma = line.find(",", start);

		int first_diff = comma - start;
		if (first_diff > 4 || first_diff <= 1) {
			// INVALID
			// std::cout << "INVALID FIRST\n";
			begin = start;
			continue;
		}

		int end = line.find(")", comma);
		int second_diff = end - comma;
		if (second_diff > 4 || second_diff <= 1) {
			// INVALID
			// std::cout << "INVALID SECOND\n";
			begin = start;
			continue;
		}
		// std::cout << "FIRST NUM: " << line.substr(start + 1, first_diff - 1) << std::endl;
		// std::cout << "SECOND NUM: " << line.substr(comma + 1, second_diff - 1) << std::endl;
		int first_num = stoi(line.substr(start + 1, first_diff - 1));
		int second_num = stoi(line.substr(comma + 1, second_diff - 1));

		res += first_num * second_num;
		begin = end;
	}
	return res;
}

// Time taken: 27:39. First try
static int solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	int res = 0;

	while (getline (MyReadFile, myText)) {
		res += find_muls(myText);
	}

	MyReadFile.close();

	return res;
}

// First attempt, 74210088
// Time taken: 20:46, Second attempt
// whould have gotten it in 5 minutes, if not for newlines breaking the program
// Task could have been more clear/formated correctly idk
static int solve2() {
	int res = 0;
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");


	while (getline (MyReadFile, myText)) {
		auto new_lines = split(myText, "do()");

		for (int i = 0; i < new_lines.size(); i++) {
			// std::cout << split(new_lines[i], "don't()")[0] << std::endl;
			int index = new_lines[i].find("don't");
			res += find_muls(new_lines[i].substr(0, index));
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
