#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES
// #include <cmath>

#define CURRENT_DAY 07

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

long long try_addmult(long long result, std::vector<int> numbers) {
	long long res = 0;

	for (int i = 0; i < std::pow(2, numbers.size() - 1); i++) {
		res = (long long)numbers[0];
		for (int j = 1; j < numbers.size(); j++) {
			if ((i & (1 << (j - 1))) >> (j - 1)) {
				res *= (long long)numbers[j];
			} else {
				res += (long long)numbers[j];
			}

			// std::cout << ((i & (1 << (j - 1))) >> (j - 1));


		}
		if (res == result) {
			// std::cout << res << std::endl;
			return res;}
		// std::cout << std::endl;
	}
	return (long long)0;
}

// first try: 1:58:39, used one hour just on nary representer.
// also solution is really inefficient.
// took 80 s to solve.
long long try_addmultconc(long long result, std::vector<int> numbers) {
	long long res = 0;


	// std::string max_string = get_nary(std::pow(3, numbers.size()), 3);

	for (int i = 0; i < std::pow(3, numbers.size() - 1); i++) {
		res = (long long)numbers[0];
		// std::cout << get_nary(i, 3) << " " ;
		for (int j = 1; j < numbers.size(); j++) {
			int digit = get_nary_digit(i, 3, j - 1);
			// std::cout << get_nary_digit(i, 3, j - 1);
			// int digit = "020"[j - 1] - '0';

			if (digit == 0) {
				res *= (long long)numbers[j];
			} else if (digit == 1) {
				res += (long long)numbers[j];
			} else if (digit == 2) {
				// std::cout << "triggered";
				res = stoll(std::to_string(res) + std::to_string(numbers[j]));
			} else {
				std::cout << "NOOOO";
			}

			if (res < 0 || res > result) {
				break;
			}
			// std::cout << ((i & (1 << (j - 1))) >> (j - 1));


		}
		// std::cout << ", ";
		if (res == result) {
			// std::cout << " " << res << std::endl;
			return res;
		}
	}
	// std::cout << " " << result << std::endl;
	return (long long)0;
}

// second try; got integer overflowed; got it after 40min~ish
static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;


	while (getline (MyReadFile, myText)) {

		auto split1 = split(myText, ": ");
		auto split2 = split(split1[1], " ");
		res += try_addmult(stoll(split1[0]), satia(split2));
		// break;
	}

	MyReadFile.close();

	return res;
}

static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;


	while (getline (MyReadFile, myText)) {

		auto split1 = split(myText, ": ");
		auto split2 = split(split1[1], " ");
		res += try_addmultconc(stoll(split1[0]), satia(split2));
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
