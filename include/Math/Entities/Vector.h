// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include <cstdlib>
#include <cstdint>
#include <cstring>

namespace simple {

template <typename T>
class Vector {
public:
	explicit Vector(uint32_t size);
	~Vector();

	T& operator()(uint32_t index);
	T const& operator()(uint32_t index) const;

	void set(T value = 0);

	uint32_t getSize() const;

	T* getPointer();
	T const* getPointer() const;
private:
	T* mData;
	uint32_t mSize;
};

template <typename T>
Vector<T>::Vector(uint32_t size) : mData(nullptr), mSize(size) {
	mData = static_cast<T*>(malloc(size * sizeof(T)));
}

template <typename T>
Vector<T>::~Vector() {
	if (mData != nullptr) { free(mData); }
}

template <typename T>
T& Vector<T>::operator()(uint32_t index) {
	return mData[index];
}

template <typename T>
T const& Vector<T>::operator()(uint32_t index) const {
	return mData[index];
}

template <typename T>
void Vector<T>::set(T value) {
	std::memset(mData, value, mSize * sizeof(T));
}

template <typename T>
uint32_t Vector<T>::getSize() const {
	return mSize;
}

template <typename T>
T* Vector<T>::getPointer() {
	return mData;
}

template <typename T>
T const* Vector<T>::getPointer() const {
	return mData;
}

} // namespace simple
