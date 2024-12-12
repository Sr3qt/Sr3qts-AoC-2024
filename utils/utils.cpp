#include "utils.h"


int test_func3() {};

int main() {
	std::string test1 = "This is a test!";
	auto vec = split(test1);
	for (std::size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i];
	}
	// std::cout << split(test1);
}
