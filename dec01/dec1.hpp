#pragma once
#include "../utils/utils.h"

#include <bits/stdc++.h>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <unordered_map>

#define CURRENT_DAY 01

// MACRO wizardry from https://stackoverflow.com/a/30114018, see comment
#define MACRO1(x, FOO) x##FOO
#define MACRO3(CURRENT_DAY, x) MACRO1(CURRENT_DAY, x)
#define NAMEDAY(name, x) MACRO3(name, x)


namespace NAMEDAY(dec, CURRENT_DAY) {
static int solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::string path = file.substr(0, file.rfind("/")) + "/data.txt";
	#ifdef WIN32
	std::fstream MyReadFile(unix_to_windows_path(path));
	#else
	std::fstream MyReadFile(path);
	#endif

	std::vector<int> left;
	std::vector<int> right;

	while (getline (MyReadFile, myText)) {
		auto left_right = split(myText, "   ");
		left.push_back(stoi(left_right[0]));
		right.push_back(stoi(left_right[1]));
	}

	MyReadFile.close();

	auto comp = [](int a, int b) {return !(a >= b);};
	std::sort(left.begin(), left.end(), comp);
	std::sort(right.begin(), right.end(), comp);

	int total = 0;
	for (int i = 0; i < left.size(); i++) {
		total += abs(left[i] - right[i]);
	}

	return total;
}

static int solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind('/')) + "/data.txt");

	std::vector<int> left;
	std::vector<int> right;

	while (getline (MyReadFile, myText)) {
		auto left_right = split(myText, "   ");
		left.push_back(stoi(left_right[0]));
		right.push_back(stoi(left_right[1]));
	}

	MyReadFile.close();

	int total = 0;
	std::unordered_map<int, int> similarity;
	for (int i = 0; i < left.size(); i++) {
		if (similarity.find(left[i]) == similarity.end()) {
			int sub_total = 0;
			for (int j = 0; j < right.size(); j++) {
				if (right[j] == left[i]) {
					sub_total++;
				}
			}
			similarity[left[i]] = sub_total;
			total += similarity[left[i]] * left[i];
		} else {
			total += similarity[left[i]] * left[i];
		}
	}

	return total;
}
} // namespace end

void NAMEDAY(solve, CURRENT_DAY)() {
	// Define a buffer
    const size_t size = 1024;
    // Allocate a character array to store the directory path
    char buffer[size];

	print_solve1(NAMEDAY(dec, CURRENT_DAY)::solve1(), CURRENT_DAY);
	print_solve2(NAMEDAY(dec, CURRENT_DAY)::solve2(), CURRENT_DAY);
}

#undef NAMEDAY
#undef MACRO1
#undef MACRO3
#undef CURRENT_DAY
