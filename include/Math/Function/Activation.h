// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include <cstdint>
#include <stdexcept>

namespace simple {
namespace math {

template <typename T>
void relu(Vector<T>& input) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = input(i) > 0 ? input(i) : 0;
	}
}

template <typename T>
void relu(Matrix<T>& input) {
	for (size_t i = 0; i < input.getRows() * input.getColumns(); ++i) {
		input(i) = input(i) > 0 ? input(i) : 0;
	}
}

template <typename T>
void reluDerivative(Vector<T> const& input, Vector<T>& output) {
#ifndef NDEBUG
	if (input.getSize() != output.getSize()) {
		std::runtime_error("input.getSize() != output.getSize()");
	}
#endif
	for (size_t i = 0; i < input.getSize(); ++i) {
		output(i) = input(i) > 0 ? 1 : 0;
	}
}

template <typename T>
void reluDerivative(Matrix<T> const& input, Matrix<T>& output) {
#ifndef NDEBUG
	if (input.getRows() != output.getRows()) {
		std::runtime_error("input.getRows() != output.getRows()");
	}

	if (input.getColumns() != output.getColumns()) {
		std::runtime_error("input.getColumns() != output.getColumns()");
	}
#endif
	for (size_t i = 0; i < input.getRows() * input.getColumns(); ++i) {
		output(i) = input(i) > 0 ? 1 : 0;
	}
}

template <typename T>
void sigmoid(Vector<T>& input) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = 1.0f / (1.0f + expf(-input(i)));
	}
}

template <typename T>
void sigmoid(Matrix<T>& input) {
	for (size_t i = 0; i < input.getRows() * input.getColumns(); ++i) {
		input(i) = 1.0f / (1.0f + expf(-input(i)));
	}
}

template <typename T>
void sigmoidDerivative(Vector<T> const& input, Vector<T>& output) {
#ifndef NDEBUG
	if (input.getSize() != output.getSize()) {
		std::runtime_error("input.getSize() != output.getSize()");
	}
#endif
	for (size_t i = 0; i < input.getSize(); ++i) {
		output(i) = input(i) * (1.0f - input(i));
	}
}

template <typename T>
void sigmoidDerivative(Matrix<T> const& input, Matrix<T>& output) {
#ifndef NDEBUG
	if (input.getRows() != output.getRows()) {
		std::runtime_error("input.getRows() != output.getRows()");
	}

	if (input.getColumns() != output.getColumns()) {
		std::runtime_error("input.getColumns() != output.getColumns()");
	}
#endif
	for (auto i = 0; i < input.getRows() * input.getColumns(); ++i) {
		output(i) = input(i) * (1.0f - input(i));
	}
}

template <typename T>
void tanh(Vector<T>& input) {
	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = tanhf(input(i));
	}
}

template <typename T>
void tanh(Matrix<T>& input) {
	for (size_t i = 0; i < input.getRows() * input.getColumns(); ++i) {
		input(i) = tanhf(input(i));
	}
}

template <typename T>
void tanhDerivative(Vector<T> const& input, Vector<T>& output) {
#ifndef NDEBUG
	if (input.getSize() != output.getSize()) {
		std::runtime_error("input.getSize() != output.getSize()");
	}
#endif
	for (size_t i = 0; i < input.getSize(); ++i) {
		output(i) = 1.0f - input(i) * input(i);
	}
}

template <typename T>
void tanhDerivative(Matrix<T> const& input, Matrix<T>& output) {
#ifndef NDEBUG
	if (input.getRows() != output.getRows()) {
		std::runtime_error("input.getRows() != output.getRows()");
	}

	if (input.getColumns() != output.getColumns()) {
		std::runtime_error("input.getColumns() != output.getColumns()");
	}
#endif
	for (size_t i = 0; i < input.getRows() * input.getColumns(); ++i) {
		output(i) = 1.0f - input(i) * input(i);
	}
}

template <typename T>
void softmax(Vector<T>& input) {
	T sum = 0.0f;

	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) = expf(input(i));
		sum += input(i);
	}

	for (size_t i = 0; i < input.getSize(); ++i) {
		input(i) /= sum;
	}
}

template <typename T>
void softmax(Matrix<T>& input) {
	for (size_t k = 0; k < input.getRows(); ++k) {
		float sum = 0.0f;

		for (size_t i = 0; i < input.getColumns(); ++i) {
			input(k,i) = expf(input(k,i));
			sum += input(k,i);
		}

		for (size_t i = 0; i < input.getColumns(); ++i) {
			input(k,i) /= sum;
		}
	}
}

template <typename T>
void softmaxDerivative(Vector<T> const& input, Vector<int32_t> const& label, Vector<T>& output) {
#ifndef NDEBUG
	if (input.getSize() != label.getSize()) {
		std::runtime_error("input.getSize() != label.getSize()");
	}

	if (label.getSize() != output.getSize()) {
		std::runtime_error("label.getSize() != output.getSize()");
	}
#endif
	auto size = input.getSize();

	for (size_t i = 0; i < size; ++i) {
		output(i) = (input(i) - label(i)) / size;
	}
}

template <typename T>
void softmaxDerivative(Matrix<T> const& input, Matrix<int32_t> const& label, Matrix<T>&  output) {
#ifndef NDEBUG
	if (input.getRows() != label.getRows()) {
		std::runtime_error("input.getRows() != label.getRows()");
	}

	if (input.getColumns() != label.getColumns()) {
		std::runtime_error("input.getColumns() != label.getColumns()");
	}

	if (label.getRows() != output.getRows()) {
		std::runtime_error("label.getRows() != output.getRows()");
	}

	if (label.getColumns() != output.getColumns()) {
		std::runtime_error("label.getColumns() != output.getColumns()");
	}
#endif
	for (size_t i = 0; i < input.getRows() * input.getColumns(); ++i) {
		output(i) = (input(i) - label(i)) / label.getColumns();
	}
}

} // namespace math
} // namespace simple
