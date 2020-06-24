// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <stdexcept>

namespace simple {
namespace math {

void seed(uint32_t seed) {
	if (seed != 0) { std::srand(seed); } else { std::srand(std::time(0)); }
}

void random(Vector<float>& input) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
}

void random(Vector<float>& input, float min, float max) {
	float range = max - min;

	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = min + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * range;
	}
}

void random(Matrix<float>& input) {
	for (size_t i = 0; i < input.getRows() * input.getColumns(); ++i) {
		input(i) = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
}

void random(Matrix<float>& input, float min, float max) {
	float range = max - min;

	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = min + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * range;
	}
}

void shuffle(Vector<float>& input) {
	uint32_t size = input.getSize();

	for (int32_t i = size - 1; i > 0; --i) {
		std::swap(input(i), input(rand() % size));
	}
}

void randomBinary(Vector<float>& input, float rate) {
#ifndef NDEBUG
	if (rate > 1) { std::runtime_error("rate > 1"); }
	if (rate < 0) { std::runtime_error("rate < 0"); }
#endif
	uint32_t size = input.getSize();

	for (uint32_t i = 0; i < size * rate; ++i) {
		input(i) = 1.0f;
	}

	for (uint32_t i = size * rate; i < size; ++i) {
		input(i) = 0.0f;
	}

	for (int32_t i = size - 1; i > 0; --i) {
		std::swap(input(i), input(rand() % size));
	}
}

void randomBinary(Matrix<uint8_t>& input, float rate) {
#ifndef NDEBUG
	if (rate > 1) { std::runtime_error("rate > 1"); }
	if (rate < 0) { std::runtime_error("rate < 0"); }
#endif
	uint32_t size = input.getSize();

	uint32_t a = 0;
	uint32_t b = static_cast<uint32_t>(size * rate);
	uint32_t c = size;

	std::memset(input.getPointer() + a, 1, (b - a) * sizeof(uint8_t));
	std::memset(input.getPointer() + b, 0, (c - b) * sizeof(uint8_t));

	for (size_t i = 0; i < size; ++i) {
		std::swap(input(i), input(rand() % size));
	}
}

void randomBinary(Matrix<float>& input, float rate) {
#ifndef NDEBUG
	if (rate > 1) { std::runtime_error("rate > 1"); }
	if (rate < 0) { std::runtime_error("rate < 0"); }
#endif
	uint32_t size = input.getSize();

	for (uint32_t i = 0; i < size * rate; ++i) {
		input(i) = 1.0f;
	}

	for (uint32_t i = size * rate; i < size; ++i) {
		input(i) = 0.0f;
	}

	for (int32_t i = size - 1; i > 0; --i) {
		std::swap(input(i), input(rand() % size));
	}
}

void randomInitRange(Vector<int32_t>& input, uint32_t until) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = rand() % until;
	}
}

} // namespace math
} // namespace simple
