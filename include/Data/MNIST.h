// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include "Data/Image.h"
#include "Data/Utility.h"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace simple {

class MNIST {
public:
	MNIST();
	~MNIST();

	void saveBinary(std::string const& imagesPath, std::string const& binaryPath);
	void loadBinary(std::string const& binaryPath);

	uint32_t getSamples();

	void getLabel(uint32_t index, Vector<int32_t>& label);
	void getImage(uint32_t index, Vector<float>& image);

	void getBatchLabels(
			Vector<int32_t> const& samples,
			uint32_t               batchSize,
			uint32_t               batchIndex,
			Matrix<float>&         batchImages);

	void getBatchImages(
			Vector<int32_t> const& samples,
			uint32_t               batchSize,
			uint32_t               batchIndex,
			Matrix<float>&         batchImages);

	void getImageSize(uint32_t& height, uint32_t& width, uint32_t& channels);
private:
	struct Header {
		uint32_t samples;
		uint32_t height;
		uint32_t width;
		uint32_t channels;
	};

	Header mHeader;
	uint8_t* mImages;
	uint8_t* mLabels;
};

MNIST::MNIST() : mImages(nullptr), mLabels(nullptr) {}

MNIST::~MNIST() {
	if (mImages != nullptr) { free(mImages); }
	if (mLabels != nullptr) { free(mLabels); }
}

void MNIST::saveBinary(std::string const& imagesPath, std::string const& binaryPath) {
	mHeader.samples  = 0;
	mHeader.channels = 1;
	mHeader.height   = 28;
	mHeader.width    = 28;

	std::vector<std::vector<std::string>> trainingImages;

	for (size_t number = 0; number < 10; ++number) {
		std::string path = imagesPath + "/" + std::to_string(number);
		trainingImages.push_back(FilesInDir(path.c_str(), "png"));
		mHeader.samples += trainingImages[number].size();
	}

	uint32_t pixelsPerImage = mHeader.height * mHeader.width * mHeader.channels;
	uint32_t size = mHeader.samples * pixelsPerImage;

	mImages = static_cast<uint8_t*>(malloc(size * sizeof(uint8_t)));
	mLabels = static_cast<uint8_t*>(malloc(mHeader.samples * sizeof(uint8_t)));

	uint32_t byte = 0;
	uint32_t example = 0;

	for (size_t number = 0; number < 10; ++number) {
		std::string folder = imagesPath + "/" + std::to_string(number) + "/";
		for (size_t sample = 0; sample < trainingImages[number].size(); ++sample) {
			std::string path = folder + trainingImages[number][sample];
			std::cout << "Image: " << path << std::endl;
			Image image(path);
			mLabels[example++] = number;
			std::memcpy(mImages + byte, image.getData(), image.getSize());
			byte += image.getSize();
		}
	}

	std::ofstream outFile(binaryPath, std::ios::out | std::ios::binary);

	if (outFile.is_open()) {
		outFile.write(reinterpret_cast<char*>(&mHeader), sizeof(mHeader));

		uint32_t labelsSize = mHeader.samples * sizeof(uint8_t);
		uint32_t imagesSize = mHeader.samples * sizeof(uint8_t) * pixelsPerImage;

		outFile.write(reinterpret_cast<char*>(mLabels), labelsSize);
		outFile.write(reinterpret_cast<char*>(mImages), imagesSize);
	}
}

void MNIST::loadBinary(std::string const& binaryPath) {
	std::ifstream inFile(binaryPath, std::ios::in | std::ios::binary);

	inFile.read(reinterpret_cast<char*>(&mHeader), sizeof(mHeader));

	uint32_t pixelsPerImage = mHeader.height * mHeader.width * mHeader.channels;
	uint32_t size = mHeader.samples * pixelsPerImage;

	mImages = static_cast<uint8_t*>(malloc(size * sizeof(uint8_t)));
	mLabels = static_cast<uint8_t*>(malloc(mHeader.samples * sizeof(uint8_t)));

	uint32_t labelsSize = mHeader.samples * sizeof(uint8_t);
	uint32_t imagesSize = mHeader.samples * sizeof(uint8_t) * pixelsPerImage;

	inFile.read(reinterpret_cast<char*>(mLabels), labelsSize);
	inFile.read(reinterpret_cast<char*>(mImages), imagesSize);
}

void MNIST::getLabel(uint32_t index, Vector<int32_t>& label) {
#ifndef NDEBUG
	if (index >= mHeader.samples) {
		std::runtime_error("index >= mHeader.samples");
	}
#endif
	label.set();
	label(mLabels[index]) = 1.0f;
}

inline uint32_t MNIST::getSamples() {
	return mHeader.samples;
}

void MNIST::getImage(uint32_t index, Vector<float>& image) {
	auto size = mHeader.width * mHeader.height * mHeader.channels;
#ifndef NDEBUG
	if (size != image.getSize()) {
		std::runtime_error("pixelsPerImage != image.getSize()");
	}
#endif
	std::memcpy(image.getPointer(), mImages + index * size, size);
}

void MNIST::getBatchLabels(
		Vector<int32_t> const& samples,
		uint32_t               batchSize,
		uint32_t               batchIndex,
		Matrix<float>&         batchLabels) {
	uint32_t numbers = 10;
#ifndef NDEBUG
	if (samples.getSize() % batchSize != 0) {
		std::runtime_error("samples.getSize() \% batchSize != 0");
	}

	if (batchLabels.getRows() != batchSize) {
		std::runtime_error("batchLabels.getRows() != batchSize");
	}

	if (batchLabels.getColumns() != numbers) {
		std::runtime_error("batchLabels.getColumns() != numbers");
	}
#endif
	batchLabels.set();

	uint32_t startSample = batchIndex * batchSize;

	for (size_t index = 0; index < batchSize; ++index) {
		batchLabels(index * numbers + mLabels[samples(startSample + index)]) = 1.0f;
	}
}

void MNIST::getBatchImages(
		Vector<int32_t> const& samples,
		uint32_t               batchSize,
		uint32_t               batchIndex,
		Matrix<float>&         batchImages) {
	uint32_t pixelsPerImage = mHeader.height * mHeader.width * mHeader.channels;
#ifndef NDEBUG
	if (samples.getSize() % batchSize != 0) {
		std::runtime_error("samples.getSize() is not multiple batchSize != 0");
	}

	if (batchImages.getRows() != batchSize) {
		std::runtime_error("batchImages.getRows() != batchSize");
	}

	if (batchImages.getColumns() != pixelsPerImage) {
		std::runtime_error("batchImages.getColumns() != pixelsPerImage");
	}
#endif
	uint32_t startSample = batchIndex * batchSize;

	for (uint32_t index = 0; index < batchSize; ++index) {
		uint32_t dstShift = pixelsPerImage * index;
		uint32_t srcShift = pixelsPerImage * samples(startSample + index);

		for (uint32_t i = 0; i < pixelsPerImage; ++i) {
			batchImages(dstShift + i) = mImages[srcShift + i] / 255.0f;
		}
	}
}

void MNIST::getImageSize(uint32_t& height, uint32_t& width, uint32_t& channels) {
	height   = mHeader.height;
	width    = mHeader.width;
	channels = mHeader.channels;
}

} // namespace simple
