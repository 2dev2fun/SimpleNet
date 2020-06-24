// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include <cstdint>
#include <stdexcept>

namespace simple {
namespace math {

template <typename T>
uint32_t argmax(Vector<T> const& input) {
#ifndef NDEBUG
	if (input.getSize() <= 0) {
		std::runtime_error("input.getSize() <= 0");
	}
#endif
	uint32_t argmax = 0;

	for (size_t i = 1; i < input.getSize(); ++i) {
		if (input(i) > input(argmax)) {
			argmax = i;
		}
	}

	return argmax;
}

template <typename T>
void argmaxByRow(Matrix<T> const& input, Vector<int32_t>& output) {
#ifndef NDEBUG
	if (input.getRows() != output.getSize()) {
		std::runtime_error("input.getRows() != output.getSize()");
	}
#endif
	output.set();

	for (size_t i = 0; i < input.getRows(); ++i) {
		for (size_t j = 1; j < input.getColumns(); ++j) {
			if (input(i,j) > input(i, output(i))) { output(i) = j; }
		}
	}
}

void matrixGetRow(Matrix<float> const& input, uint32_t row, Vector<float>& output) {
#ifndef NDEBUG
	if (input.getColumns() != output.getSize()) {
		std::runtime_error("input.getColumns() != output.getSize()");
	}

	if (row >= input.getRows()) {
		std::runtime_error("row >= input.getRows()");
	}
#endif
	for (size_t i = 0; i < input.getColumns(); ++i) {
		output(i) = input(row, i);
	}
}

void matrixGetColumn(Matrix<float> const& input, uint32_t column, Vector<float>& output) {
#ifndef NDEBUG
	if (input.getRows() != output.getSize()) {
		std::runtime_error("input.getRows() != output.getSize()");
	}

	if (column >= input.getColumns()) {
		std::runtime_error("column >= input.getColumns()");
	}
#endif
	for (size_t i = 0; i < input.getRows(); ++i) {
		output(i) = input(i, column);
	}
}


template <typename T>
T sum(Vector<T> const& input) {
	T total = 0.0f;
	for (size_t i = 0; i < input.getSize(); ++i) {
		total += input(i);
	}
	return total;
}

template <typename T>
T sum(Matrix<T> const& input) {
	T total = 0.0f;
	for (size_t i = 0; i < input.getColumns() * input.getRows(); ++i) {
		total += input(i);
	}
	return total;
}

template <typename T>
void sumByRow(Matrix<T> const& input, Vector<T>& output) {
#ifndef NDEBUG
	if (input.getRows() != output.getSize()) {
		std::runtime_error("input.getRows() != output.getSize()");
	}
#endif
	output.setZero();

	for (auto i = 0; i < input.getRows(); ++i) {
		for (auto j = 0; j < input.getColumns(); ++j) {
			output(i) = input(i, j);
		}
	}
}

template <typename T>
void sumByColumn(Matrix<T> const& input, Vector<T>& output) {
#ifndef NDEBUG
	if (input.getColumns() != output.getSize()) {
		std::runtime_error("input.getColumns() != output.getSize()");
	}
#endif
	output.setZero();

	for (size_t i = 0; i < input.getRows(); ++i) {
		for (size_t j = 0; j < input.getColumns(); ++j) {
			output(j) = input(i, j);
		}
	}
}

} // namespace math
} // namespace simple
