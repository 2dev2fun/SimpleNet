// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#include "Net/FullyConnected.h"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace simple;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "Image path should be specified!" << std::endl;
		return 0;
	}

	if (argc >= 3) {
		std::cout << "Only one argument is needed nad this is the path to the image!" << std::endl;
		return 0;
	}

	const std::string path = argv[1];
	std::ifstream file(path.c_str());

	if (!file.good()) {
		std::cout << "File not found!" << std::endl;
		return 0;
	}

	const std::string extension = path.substr(path.find_last_of(".") + 1);

	if ((extension == "png") || (extension == "jpg")) {
		try {
			FullyConnectedNet(path);
		} catch (std::exception const& e) {
			std::cout << e.what() << std::endl;
		}
	} else {
		std::cout << "Extension of a file is wrong! (only png or jpg)" << std::endl;
	}

	return 0;
}
