// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <cstdint>
#include <stdexcept>
#include <string>

namespace simple {

class Image {
public:
	Image(std::string const& path, bool flipY = false);
	~Image();

	uint8_t* getData();

	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getChannels() const;

	uint32_t getSize() const;
private:
	uint8_t* mData;
	uint32_t mWidth;
	uint32_t mHeight;
	uint32_t mChannels;
};

inline Image::Image(std::string const& path, bool flipY)
		: mData(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mChannels(0) {
	if (flipY) { stbi_set_flip_vertically_on_load(flipY); }

	int width;
	int height;
	int channels;

	uint8_t* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (data == nullptr) {
		std::runtime_error("Failed to load image: " + path);
	}

	mWidth    = width;
	mHeight   = height;
	mChannels = channels;

	mData = static_cast<uint8_t*>(malloc(mHeight * mWidth * mChannels * sizeof(uint8_t)));
	memcpy(mData, data, mHeight * mWidth * mChannels * sizeof(uint8_t));

	if (data == nullptr) { std::runtime_error("Failed to load image " + path); }

	stbi_image_free(data);
}

inline Image::~Image() {
	if (mData != nullptr) { free(mData); }
}

inline uint8_t* Image::getData() {
	return mData;
}

inline uint32_t Image::getSize() const {
	return mWidth * mHeight * mChannels;
}

inline uint32_t Image::getWidth() const {
	return mWidth;
}

inline uint32_t Image::getHeight() const {
	return mHeight;
}

inline uint32_t Image::getChannels() const {
	return mChannels;
}

} // namespace simple
