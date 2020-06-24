// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include <stdexcept>

namespace simple {
namespace math {

template <typename T>
void plus(Vector<T> const& left, Vector<T> const& right, Vector<T>& output) {
#ifndef NDEBUG
	if (left.getSize() != right.getSize()) {
		std::runtime_error("left.getSize() != right.getSize()");
	}

	if (right.getSize() != output.getSize()) {
		std::runtime_error("right.getSize() != output.getSize()");
	}
#endif
	for (size_t i = 0; i < output.getSize(); ++i) {
		output(i) = left(i) + right(i);
	}
}

template <typename T>
void plus(Matrix<T> const& left, Matrix<T> const& right, Matrix<T>& output) {
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
		output(i) = left(i) + right(i);
	}
}

} // namespace math
} // namespace simple
