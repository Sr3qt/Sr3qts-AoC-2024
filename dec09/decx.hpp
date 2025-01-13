#pragma once

// DEFAULTS
#include "../utils/utils.h"
#include <fstream>
#include <chrono>

// NEW INCLUDES


#define CURRENT_DAY 09

// MACRO wizardry from https://stackoverflow.com/a/30114018, see comment
#define MACRO1(x, FOO) x##FOO
#define MACRO3(CURRENT_DAY, x) MACRO1(CURRENT_DAY, x)
#define NAMEDAY(name, x) MACRO3(name, x)


namespace NAMEDAY(dec, CURRENT_DAY) {

long long int sum_range(int start, int end) {
	// int diff = end - start;
	// return (diff * diff) / 2;
	long long int res = 0;
	for (int i = start; i < end; i++) {
		res += i;
	}
	return res;
}

// First attempt: 36:15
// Second attempt: 1:26:53
// first try: 6121374645794 too low
// got it second try, error was caused by integer overflow
static long long solve1() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind('/')) + "/data.txt");
	long long res = 0;

	getline(MyReadFile, myText);

	int first = 0; // The curser position in memory
	int last = myText.size() - 1;
	int leftover = (myText[last] - '0'); // first index is number of blocks, second is block id.
	for (int i = 0; i < myText.size(); i++) {
		int block_num = (myText[i] - '0');
		if (i % 2) {
			// Range contains the first memory block index and the index after the last memory block
			Range empty = {first, first + block_num};

			while (empty.start < empty.end) {
				if (i > last) {
					break; // early break to stop double counting
				}

				int diff = empty.end - empty.start;
				if (leftover <= diff) {
					res += sum_range(first, first + leftover) * (last / 2);
					first += leftover;
					empty.start += leftover;
					last -= 2;
					leftover = (myText[last] - '0');
				} else {
					res += sum_range(first, first + diff) * (last / 2);
					first += diff;
					leftover -= diff;
					break;
				}

			}
		} else {
			// Only count uncounted last blocks
			if (i == last) {
				block_num = leftover;
			}
			res += sum_range(first, first + block_num) * (i / 2);
			first += block_num;
		}

		if (i >= last) {
			break;
		}
	}

	MyReadFile.close();

	return res;
}


// First attempt: 1:07:09
// First try: 7431795422308 too high
// got it second try
static long long solve2() {
	std::string myText;
	std::string file = std::string(__FILE__);
	std::fstream MyReadFile(file.substr(0, file.rfind('/')) + "/data.txt");
	long long res = 0;

	// Range contains the first memory block index and the index after the last memory block
	std::vector<Range> empty_spaces;

	getline(MyReadFile, myText);

	// First make Range array for gaps.
	// Then loop over in opposite order, try to move every file and count

	// Interesting optimization might be grouping spaces by size, then you can skip checking smaller spaces

	int first = 0; // The curser position in memory
	for (int i = 0; i < myText.size(); i++) {
		int block_num = (myText[i] - '0');
		// if (block_num == 0) {continue;}
		if (i % 2) {
			// Range contains the first memory block index and the index after the last memory block
			empty_spaces.push_back({first, first + block_num});

		}
		first += block_num;
	}

	for (int i = myText.size() - 1; 0 < i; i -= 2) {
		int block_num = (myText[i] - '0');
		bool fits = false;
		for (int j = 0; j < empty_spaces.size(); j++) {
			Range range = empty_spaces[j];
			if (in_range(range.start + block_num, range)) {
				// Add new position score
				res += sum_range(range.start, range.start + block_num) * (i / 2);
				fits = true;

				empty_spaces[j].start += block_num;
				// if (empty_spaces[j].start == empty_spaces[j].end) {
				// 	empty_spaces.erase(empty_spaces.begin() + j);
				// }
				// std::cout << res << std::endl;
				break;
			}
		}

		if (!fits) {
			// Add normal score
			res += sum_range(empty_spaces.back().end, empty_spaces.back().end + block_num) * (i / 2);
		}
		// if (empty_spaces.size() > 0) {
		empty_spaces.pop_back();
		// }
	}

	MyReadFile.close();

	return res;
}
} // namespace end

void NAMEDAY(solve, CURRENT_DAY)() {
	auto start = std::chrono::high_resolution_clock::now();
	print_solve1(NAMEDAY(dec, CURRENT_DAY)::solve1(), 9);
	auto mid = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(mid - start);
	std::cout << "Time taken: "  << duration1.count() / 1000.0 << " ms.\n";
	print_solve2(NAMEDAY(dec, CURRENT_DAY)::solve2(), 9);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - mid);
	std::cout << "Time taken: "  << duration2.count() / 1000.0 << " ms.\n";
}

#undef NAMEDAY
#undef MACRO1
#undef MACRO3
#undef CURRENT_DAY
