// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include <cstdlib>
#include <cstdint>
#include <cstring>

namespace simple {

template <typename T>
class Matrix {
public:
	Matrix(uint32_t rows, uint32_t columns);
	~Matrix();

	T& operator()(uint32_t index);
	T const& operator()(uint32_t index) const;

	T& operator()(uint32_t row, uint32_t column);
	T const& operator()(uint32_t row, uint32_t column) const;

	void set(T value = 0);

	uint32_t getColumns() const;
	uint32_t getRows() const;

	uint32_t getSize() const;

	T* getPointer();
	T const* getPointer() const;
private:
	T* mData;
	uint32_t mColumns;
	uint32_t mRows;
};

template <typename T>
Matrix<T>::Matrix(uint32_t rows, uint32_t columns) : mData(nullptr), mColumns(columns), mRows(rows) {
	mData = static_cast<T*>(malloc(mColumns * mRows * sizeof(T)));
}

template <typename T>
Matrix<T>::~Matrix() {
	if (mData) { free(mData); }
}

template <typename T>
T& Matrix<T>::operator()(uint32_t index) {
	return mData[index];
}

template <typename T>
T const& Matrix<T>::operator()(uint32_t index) const {
	return mData[index];
}

template <typename T>
T& Matrix<T>::operator()(uint32_t row, uint32_t column) {
	return mData[row * mColumns + column];
}

template <typename T>
T const& Matrix<T>::operator()(uint32_t row, uint32_t column) const {
	return mData[row * mColumns + column];
}

template <typename T>
void Matrix<T>::set(T value) {
	std::memset(mData, value, mRows * mColumns * sizeof(T));
}

template <typename T>
uint32_t Matrix<T>::getColumns() const {
	return mColumns;
}

template <typename T>
uint32_t Matrix<T>::getRows() const {
	return mRows;
}

template <typename T>
uint32_t Matrix<T>::getSize() const {
	return mColumns * mRows;
}

template <typename T>
T* Matrix<T>::getPointer() {
	return mData;
}

template <typename T>
T const* Matrix<T>::getPointer() const {
	return mData;
}

} // namespace simple
