// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include <stdexcept>

namespace simple {
namespace math {

template <typename T, typename U, typename V>
void product(Matrix<T> const& left, U right, Matrix<V>& output) {
#ifndef NDEBUG
	if (left.getRows() != output.getRows()) {
		std::runtime_error("left.getRows() != right.getRows()");
	}

	if (left.getColumns() != output.getColumns()) {
		std::runtime_error("left.getColumns() != right.getColumns()");
	}
#endif
	for (size_t i = 0; i < left.getSize(); ++i) {
		output(i) = left(i) * right;
	}
}

template <typename T, typename U, typename V>
void product(Matrix<T> const& left, Matrix<U> const& right, Matrix<V>& output) {
#ifndef NDEBUG
	if (left.getColumns() != right.getColumns()) {
		std::runtime_error("left.getColumns() != right.getColumns()");
	}

	if (left.getRows() != right.getRows()) {
		std::runtime_error("left.getRows() != right.getRows()");
	}

	if (right.getColumns() != output.getColumns()) {
		std::runtime_error("right.getColumns() != output.getColumns()");
	}

	if (right.getRows() != output.getRows()) {
		std::runtime_error("right.getRows() != output.getRows()");
	}
#endif
	for (size_t i = 0; i < output.getSize(); ++i) {
		output(i) = left(i) * right(i);
	}
}

template <typename T, typename U, typename V>
void product(Vector<T> const& left, U right, Vector<V>& output) {
#ifndef NDEBUG
	if (left.getSize() != output.getSize()) {
		std::runtime_error("left.getSize() != right.getSize()");
	}
#endif
	for (size_t i = 0; i < left.getSize(); ++i) {
		output(i) = left(i) * right;
	}
}

template <typename T, typename U, typename V>
void product(Vector<T> const& left, Vector<U> const& right, Vector<V>& output) {
#ifndef NDEBUG
	if (left.getSize() != right.getSize()) {
		std::runtime_error("left.getSize() != right.getSize()");
	}

	if (right.getSize() != output.getSize()) {
		std::runtime_error("right.getSize() != output.getSize()");
	}
#endif
	for (size_t i = 0; i < left.getSize(); ++i) {
		output(i) = left(i) * right(i);
	}
}

} // namespace math
} // namespace simple
