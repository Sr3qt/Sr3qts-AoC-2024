#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES


#define CURRENT_DAY 11

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


void iterate(std::vector<std::string>& vec) {
	int offset = 0;
	for (int i = 0; i < vec.size(); i++) {
		if (i + offset >= vec.size()) {
			break;
		}
		auto item = vec[i + offset];
		if (item == "0") {
			vec[i + offset] = "1"; // WIll this replace value in vector? maybe just use vector indexing
		} else if (item.size() % 2 == 0) {
			std::string right = std::to_string(stoull(item.substr(item.size() / 2)));
			// std::cout << right << "\n";
			vec.insert(vec.begin() + i + offset + 1, right);
			vec[i + offset] = item.substr(0, item.size() / 2);
			offset++;
		} else {
			vec[i + offset] = std::to_string(stoull(item) * 2024);
		}



	}
}

// First attemp: 34:11
// Got it first try, however the answer was given after 45s ...
// Going to optimize
static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;


	getline (MyReadFile, myText);

	auto temp = split(myText);
	// temp.reserve(55312);

	for (int i = 0; i < 25; i++) {
		iterate(temp);

		// for (auto const& i : temp) {
		// 	std::cout << i << ", ";
		// }
		// std::cout << "\n";
	}

	res = temp.size();

	MyReadFile.close();

	return res;
}

static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;


	while (getline (MyReadFile, myText)) {

	}

	MyReadFile.close();

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
