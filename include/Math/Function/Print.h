// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace simple {
namespace math {

void print(Vector<uint8_t> const& input) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		std::cout << std::setw(4) << std::fixed;
		std::cout << input(i);
	}
	std::cout << std::endl;
}

void print(Vector<int32_t> const& input) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		std::cout << std::setw(8) << std::fixed;
		std::cout << input(i);
	}
	std::cout << std::endl;
}

void print(const Vector<float>& input) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		std::cout << std::setw(10) << std::setprecision(2) << std::fixed;
		std::cout << input(i);
	}
	std::cout << std::endl;
}

void print(Matrix<uint8_t> const& input) {
#ifndef NDEBUG
	if (input.getRows() == 0) {
		std::runtime_error("input.getRows() == 0");
	}

	if (input.getColumns() == 0) {
		std::runtime_error("input.getColumns() == 0");
	}
#endif
	for (size_t i = 0; i < input.getRows(); ++i) {
		for (size_t j = 0; j < input.getColumns(); ++j) {
			std::cout << std::setw(2);
			std::cout << static_cast<int>(input(i,j));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print(Matrix<int32_t> const& input) {
	for (size_t i = 0; i < input.getRows(); ++i) {
		for (size_t j = 0; j < input.getColumns(); ++j) {
			std::cout << std::setw(8) << std::fixed;
			std::cout << input(i,j);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void print(const Matrix<float>& input) {
	for (size_t i = 0; i < input.getRows(); ++i) {
		for (size_t j = 0; j < input.getColumns(); ++j) {
			std::cout << std::setw(12) << std::setprecision(2) << std::fixed;
			std::cout << input(i,j);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

} // namespace math
} // namespace simple
