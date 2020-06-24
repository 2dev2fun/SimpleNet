// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include <stdexcept>

namespace simple {
namespace math {

template <typename T>
void dot(Matrix<T> const& left, Matrix<T> const& right, Matrix<T>& output) {
#ifndef NDEBUG
	if (&output == &left) {
		std::runtime_error("&output == &left");
	}

	if (&output == &right) {
		std::runtime_error("&output == &right");
	}

	if (left.getColumns() != right.getRows()) {
		std::runtime_error("left.getColumns() != right.getRows()");
	}

	if (left.getRows() != output.getRows()) {
		std::runtime_error("left.getRows() != output.getRows()");
	}

	if (right.getColumns() != output.getColumns()) {
		std::runtime_error("right.getColumns() != output.getColumns()");
	}
#endif
	output.set();

	for (uint32_t i = 0; i < output.getRows(); ++i) {
		for (uint32_t j = 0; j < output.getColumns(); ++j) {
			for (uint32_t k = 0; k < left.getColumns(); ++k) {
				output(i,j) += left(i,k) * right(k,j);
			}
		}
	}
}

template <typename T>
void dot(Matrix<T> const& left, Vector<T> const& right, Vector<T>& result) {
#ifndef NDEBUG
	if (left.getColumns() != right.getSize()) {
		std::runtime_error("left.getColumns() != right.getSize()");
	}

	if (left.getRows() != result.getSize()) {
		std::runtime_error("left.getRows() != result.getSize()");
	}
#endif
	for (size_t i = 0; i < result.getSize(); ++i) {
		result(i) = 0.0f;
		for (size_t j = 0; j < right.getSize(); ++j) {
			result(i) += left(i,j) * right(j);
		}
	}
}

template <typename T>
void dot(Vector<T> const& left, Vector<T> const& right, T& output) {
#ifndef NDEBUG
	if (left.getSize() != right.getSize()) {
		std::runtime_error("left.getSize() != right.getSize()");
	}
#endif
	output = 0.0f;

	for (size_t i = 0; i < left.getSize(); ++i) {
		output += left(i) * right(i);
	}
}

template <typename T>
void dotTranspose(Vector<T> const& left, Vector<T> const& right, Matrix<T>& output) {
#ifndef NDEBUG
	if (output.getRows() != left.getSize()) {
		std::runtime_error("output.getRows() != left.getSize()");
	}

	if (output.getColumns() != right.getSize()) {
		std::runtime_error("output.getColumns() != right.getSize()");
	}
#endif
	for (size_t i = 0; i < output.getRows(); ++i) {
		for (size_t j = 0; j < output.getColumns(); ++j) {
			output(i,j) = left(i) * right(j);
		}
	}
}

template <typename T>
void dotTranspose(Matrix<T> const& left, Matrix<T> const& right, Matrix<T>& output) {
#ifndef NDEBUG
	if (&output == &left) {
		std::runtime_error("&output == &left");
	}

	if (&output == &right) {
		std::runtime_error("&output == &right");
	}

	if (left.getColumns() != right.getColumns()) {
		std::runtime_error("left.getColumns() != right.getColumns()");
	}

	if (left.getRows() != output.getRows()) {
		std::runtime_error("left.getRows() != output.getRows()");
	}

	if (right.getRows() != output.getColumns()) {
		std::runtime_error("right.getRows() != output.getColumns()");
	}
#endif
	output.set();

	for (uint32_t i = 0; i < output.getRows(); ++i) {
		for (uint32_t j = 0; j < output.getColumns(); ++j) {
			for (uint32_t k = 0; k < left.getColumns(); ++k) {
				output(i,j) += left(i,k) * right(j,k);
			}
		}
	}
}

template <typename T>
void transposeDot(Vector<T> const& left, Matrix<T> const& right, Vector<T>& output) {
#ifndef NDEBUG
	if (&left == &output) {
		std::runtime_error("&left == &output");
	}

	if (left.getSize() != right.getRows()) {
		std::runtime_error("left.getSize() != right.getRows()");
	}

	if (output.getSize() != right.getColumns()) {
		std::runtime_error("output.getSize() != right.getColumns()");
	}
#endif
	output.set();

	for (uint32_t k = 0; k < output.getSize(); ++k) {
		for (uint32_t i = 0; i < left.getSize(); ++i) {
			output(k) += left(i) * right(i,k);
		}
	}
}

template <typename T>
void transposeDot(Matrix<T> const& left, Matrix<T> const& right, Matrix<T>& output) {
#ifndef NDEBUG
	if (&output == &left) {
		std::runtime_error("&output == &left");
	}

	if (&output == &right) {
		std::runtime_error("&output == &right");
	}

	if (left.getRows() != right.getRows()) {
		std::runtime_error("left.getRows != right.getRows()");
	}

	if (left.getColumns() != output.getRows()) {
		std::runtime_error("left.getColumns() != output.getRows()");
	}

	if (right.getColumns() != output.getColumns()) {
		std::runtime_error("right.getColumns() != output.getColumns()");
	}
#endif
	output.set();

	for (uint32_t i = 0; i < output.getRows(); ++i) {
		for (uint32_t j = 0; j < output.getColumns(); ++j) {
			for (uint32_t k = 0; k < left.getColumns(); ++k) {
				output(i,j) += left(k,i) * right(k,j);
			}
		}
	}
}

} // namespace math
} // namespace simple
