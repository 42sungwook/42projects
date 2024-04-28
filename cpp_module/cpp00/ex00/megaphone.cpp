#include <iostream>
#include <cstring>

int main(int argc, char **argv) {

	std::string input;

	if (argc < 2) {
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		input += argv[i];
	}

	for (std::size_t i = 0; i < input.length(); ++i) {
		input[i] = std::toupper(static_cast<unsigned char>(input[i]));
	}

	std::cout << input << std::endl;

	return 0;
}
