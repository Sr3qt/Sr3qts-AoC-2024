#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES


#define CURRENT_DAY 14

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


struct Pair {
	int x;
	int y;
};

Pair simulate_movement(Pair pos, Pair vel, Pair size, int steps) {
	int x = vel.x < 0 ? (size.x + (pos.x + vel.x * steps) % (size.x)) % size.x: (pos.x + vel.x * steps) % (size.x);
	int y = vel.y < 0 ? (size.y + (pos.y + vel.y * steps) % (size.y)) % size.y: (pos.y + vel.y * steps) % (size.y);
	return {x, y};
}

// First attempt: 50:03. Should have completed it faster given its simplicity,
// but creating the formula gave me some trouble.
// First try: 100599300, too low
// Got it second try. Forgot to change board dimensions
static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
	long long res = 0;

	Pair size = {101, 103};
	int steps = 100;

	int quad1 = 0;
	int quad2 = 0;
	int quad3 = 0;
	int quad4 = 0;

	while (getline (MyReadFile, myText)) {
		auto pos_vel = split(myText);
		Pair pos = {stoi(split(pos_vel[0], ",")[0].substr(2)), stoi(split(pos_vel[0], ",")[1])};
		Pair vel = {stoi(split(pos_vel[1], ",")[0].substr(2)), stoi(split(pos_vel[1], ",")[1])};
		Pair new_pos = simulate_movement(pos, vel, size, steps);

		if (new_pos.x < size.x / 2) {
			if (new_pos.y < size.y / 2) {
				quad1++;
			} else if (new_pos.y > size.y / 2) {
				quad2 ++;
			}
		} else if (new_pos.x > size.x / 2) {
			if (new_pos.y < size.y / 2) {
				quad3++;
			} else if (new_pos.y > size.y / 2) {
				quad4 ++;
			}
		}
	}

	MyReadFile.close();

	res = quad1 * quad2 * quad3 * quad4;
	return res;
}


// First attempt: 57:18
// Got it first try.
static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	long long res = 0;

	// input = std::cin;
	int input = 1;
	int steps = 0;

	std::cout <<
	"This solution is kind of special, because you have to search for a solution manually.\n" \
	"At least that was how i did it. You can enter a number to increase/decrease the step counter.\n" \
	"Inserting 0 will skip this and inserting 1 will jump by 103 for your convenience!\n" \
	"Enjoy searching! (101+ width terminal recommended!)\n" << "Enter a number:" << std::endl;

	while (input != 0) {
		std::fstream MyReadFile(file.substr(0, file.rfind(OS_SEP)) + OS_SEP + "data.txt");
		std::cin >> input;
		if (input == 1) {
			input = 103;
			if (steps == 0) {steps++;}
		} else if (input == 0) {
			break;
		}

		Pair size = {101, 103};
		steps += input;

		std::vector<std::vector<char>> canvas;
		for (int i = 0; i < size.y; i++) {
			std::vector<char> temp1;
			temp1.resize(size.x, '.');
			canvas.push_back(temp1);
		}

		while (getline (MyReadFile, myText)) {
			auto pos_vel = split(myText);
			Pair pos = {stoi(split(pos_vel[0], ",")[0].substr(2)), stoi(split(pos_vel[0], ",")[1])};
			Pair vel = {stoi(split(pos_vel[1], ",")[0].substr(2)), stoi(split(pos_vel[1], ",")[1])};
			Pair new_pos = simulate_movement(pos, vel, size, steps);
			canvas[new_pos.y][new_pos.x] = '@';
		}

		MyReadFile.close();

		for (auto &i : canvas) {
			for (auto &j : i) {
				std::cout << j;
			}

			std::cout << "\n";
		}
		std::cout << steps << std::endl;
	}
	res = steps;
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
