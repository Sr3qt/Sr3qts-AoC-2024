#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>

// NEW INCLUDES
#include <unordered_map>


#define CURRENT_DAY 05

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

int verify_page_order(std::unordered_map<int, std::vector<int>> rules, std::string line) {
	auto pages = split(line, ",");
	std::vector<int> seen_pages = {stoi(pages[0])};

	for (int i = 1; i < pages.size(); i++) {
		int current_page = stoi(pages[i]);
		if (rules.find(current_page) == rules.end()) {
			seen_pages.push_back(current_page);
			std::cout << "should never happen";
			continue;
		}
		for (int j = 0; j < rules[current_page].size(); j++) {
			for (int k = 0; k < seen_pages.size(); k++) {
				if (rules[current_page][j] == seen_pages[k]) {return 0;}
			}
		}
		seen_pages.push_back(current_page);
	}

	return seen_pages[(seen_pages.size() - 1) / 2];
}

int deverify_page_order(std::unordered_map<int, std::vector<int>> rules, std::string line) {
	if (verify_page_order(rules, line) != 0) {
		return 0;
	}

	auto pages = split(line, ",");
	std::vector<int> seen_pages = {stoi(pages[0])};

	for (int i = 1; i < pages.size(); i++) {
		int current_page = stoi(pages[i]);
		// if (rules.find(current_page) == rules.end()) {
		// 	seen_pages.push_back(current_page);
		// 	continue;
		// }
		int lowest_index = seen_pages.size();
		for (int j = 0; j < rules[current_page].size(); j++) {
			for (int k = 0; k < seen_pages.size(); k++) {
				if (rules[current_page][j] == seen_pages[k]) {
					lowest_index = std::min(lowest_index, k);
				}
			}
		}
		seen_pages.insert(seen_pages.begin() + lowest_index, current_page);
	}

	return seen_pages[(seen_pages.size() - 1) / 2];
}

// first try: 44:44
static int solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	int res = 0;

	std::unordered_map<int, std::vector<int>> rules;
	bool defining_rules = true;

	while (getline (MyReadFile, myText)) {

		if (myText == "") {
			defining_rules = false;
			continue;
		}
		if (defining_rules)	{
			auto splitted = split(myText, "|");
			int left = stoi(splitted[0]);
			int right = stoi(splitted[1]);
			if (rules.find(left) == rules.end()) {
				std::vector<int> temp = {right};
				rules[left] = temp;
			} else {
				rules[left].push_back(right);
			}
		} else {
			res += verify_page_order(rules, myText);
		}
	}

	MyReadFile.close();

	return res;
}

// first try: 11:04
static int solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	int res = 0;

	std::unordered_map<int, std::vector<int>> rules;
	bool defining_rules = true;

	while (getline (MyReadFile, myText)) {
		if (myText == "") {
			defining_rules = false;
			continue;
		}
		if (defining_rules)	{
			auto splitted = split(myText, "|");
			int left = stoi(splitted[0]);
			int right = stoi(splitted[1]);
			if (rules.find(left) == rules.end()) {
				std::vector<int> temp = {right};
				rules[left] = temp;
			} else {
				rules[left].push_back(right);
			}
		} else {
			res += deverify_page_order(rules, myText);
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
