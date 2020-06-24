// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include <stdexcept>

namespace simple {
namespace math {

template <typename T>
void outerProduct(Matrix<T> const& left, Matrix<T> const& right, Matrix<T>& output) {
#ifndef NDEBUG
	if (left.getRows() != right.getRows()) {
		std::runtime_error("left.getRows() != right.getRows()");
	}

	if (output.getRows() != left.getColumns()) {
		std::runtime_error("output.getRows() != left.getColumns()");
	}

	if (output.getColumns() != right.getColumns()) {
		std::runtime_error("output.getColumns() != right.getColumns()");
	}
#endif
	output.set();

	uint32_t batchSize = left.getRows();

	uint32_t rows    = output.getRows();
	uint32_t columns = output.getColumns();

	for (uint32_t k = 0; k < batchSize; ++k) {
		for (uint32_t i = 0; i < rows; ++i) {
			for (uint32_t j = 0; j < columns; ++j) {
				output(i,j) += left(k,i) * right(k,j);
			}
		}
	}
}

} // namespace math
} // namespace simple
