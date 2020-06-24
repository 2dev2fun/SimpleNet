// Copyright (C) 2020 Maxim, 2dev2fun@gmail.com. All rights reserved.

#pragma once

#include "Data/MNIST.h"

#include "Math/Entities/Matrix.h"
#include "Math/Entities/Vector.h"

#include "Math/Function/Activation.h"
#include "Math/Function/Dot.h"
#include "Math/Function/Minus.h"
#include "Math/Function/Other.h"
#include "Math/Function/OuterProduct.h"
#include "Math/Function/Plus.h"
#include "Math/Function/Print.h"
#include "Math/Function/Product.h"
#include "Math/Function/Random.h"

#include <chrono>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std::chrono;
using namespace std::chrono_literals;

namespace simple {

void FullyConnectedNet(std::string const& path) {
	MNIST trainMNIST;
	MNIST testMNIST;

	const char* trainImagesPath = "./data/mnist/train";
	const char* testImagesPath  = "./data/mnist/test";

	const char* trainBinaryPath = "./data/mnist/train.bin";
	const char* testBinaryPath  = "./data/mnist/test.bin";

	// Load train MNIST

	std::fstream trainBinaryFile(trainBinaryPath);

	if (!trainBinaryFile.good()) {
		trainMNIST.saveBinary(trainImagesPath, trainBinaryPath);
	}

	trainMNIST.loadBinary(trainBinaryPath);

	trainBinaryFile.close();

	// Load test MNIST

	std::fstream testBinaryFile(testBinaryPath);

	if (!testBinaryFile.good()) {
		testMNIST.saveBinary(testImagesPath, testBinaryPath);
	}

	testMNIST.loadBinary(testBinaryPath);

	testBinaryFile.close();

	// Properties -------------------------------------------------------------

	uint32_t height   = 28;
	uint32_t width    = 28;
	uint32_t channels = 1;

	uint32_t pixelsPerImage = height * width * channels;
	uint32_t numbers        = 10;

	uint32_t layer_0_Size = pixelsPerImage;
	uint32_t layer_1_Size = 128;
	uint32_t layer_2_Size = numbers;

	float    alpha      = 0.001f;
	uint32_t batchSize  = 32;
	uint32_t iterations = 100;

	float dropout_1_Rate = 0.5f;

	// Prepare examples -------------------------------------------------------

	uint32_t trainSamples = 1000;
	uint32_t testSamples  = 10000;

	uint32_t trainBatches = ((trainSamples + batchSize) / batchSize);
	uint32_t testBatches  = ((testSamples  + batchSize) / batchSize);

	trainSamples = trainBatches * batchSize;
	testSamples  = testBatches  * batchSize;

	Vector<int32_t> trainSamples_Vector(trainSamples);
	Vector<int32_t> testSamples_Vector(testSamples);

	uint32_t seed = 1;

	math::seed(seed);

	math::randomInitRange(trainSamples_Vector, trainMNIST.getSamples());
	math::randomInitRange(testSamples_Vector, testMNIST.getSamples());

	// Weights matrices

	Matrix<float> weight_0_1_Matrix(layer_0_Size, layer_1_Size);
	Matrix<float> weight_1_2_Matrix(layer_1_Size, layer_2_Size);

	// Delta weight matrices

	Matrix<float> weightDelta_0_1_Matrix(layer_0_Size, layer_1_Size);
	Matrix<float> weightDelta_1_2_Matrix(layer_1_Size, layer_2_Size);

	// Delta matrices

	Matrix<float> delta_0_Matrix(batchSize, layer_0_Size);
	Matrix<float> delta_1_Matrix(batchSize, layer_1_Size);
	Matrix<float> delta_2_Matrix(batchSize, layer_2_Size);

	// Error vector

	// Math::MatrixF error_2_Matrix;
	// Math::Create(error_2_Matrix, batchSize, layer_2_Size);

	// Layers

	Matrix<float> layer_0_Matrix(batchSize, layer_0_Size);
	Matrix<float> layer_1_Matrix(batchSize, layer_1_Size);
	Matrix<float> layer_2_Matrix(batchSize, layer_2_Size);

	// Labels

	Vector<int32_t> label_Vector(batchSize);

	Matrix<float> label_2_Matrix(batchSize, layer_2_Size);

	// Derivative

	Matrix<float> derivative_1_Matrix(batchSize, layer_1_Size);

	// Dropout

	Matrix<uint8_t> dropout_1_Matrix(batchSize, layer_1_Size);

	// Predict

	Vector<int32_t> predict_Vector(batchSize);

	//-------------------------------------------------------------------------

	auto start = high_resolution_clock::now();

	//-------------------------------------------------------------------------

	math::random(weight_0_1_Matrix, -0.01f, 0.01f);
	math::random(weight_1_2_Matrix, -0.01f, 0.01f);

	// Float error;
	float correctPredict;

	for (uint32_t iteration = 0; iteration < iterations; ++iteration) {

		// error = 0.0f;
		correctPredict = 0;

		for (uint32_t batchIndex = 0; batchIndex < trainBatches; ++batchIndex) {

			trainMNIST.getBatchImages(
					trainSamples_Vector,
					batchSize,
					batchIndex,
					layer_0_Matrix);

			trainMNIST.getBatchLabels(
					trainSamples_Vector,
					batchSize,
					batchIndex,
					label_2_Matrix);

			// Dropout
			math::randomBinary(dropout_1_Matrix, dropout_1_Rate);

			// Forward
			math::dot(layer_0_Matrix, weight_0_1_Matrix, layer_1_Matrix);
			math::tanh(layer_1_Matrix);
			math::product(layer_1_Matrix, dropout_1_Matrix, layer_1_Matrix);
			math::product(layer_1_Matrix, 1.0f / dropout_1_Rate, layer_1_Matrix);
			math::dot(layer_1_Matrix, weight_1_2_Matrix, layer_2_Matrix);
			math::softmax(layer_2_Matrix);

			// Derivative
			math::tanhDerivative(layer_1_Matrix, derivative_1_Matrix);

			// Delta
			math::minus(label_2_Matrix, layer_2_Matrix, delta_2_Matrix);
			math::dotTranspose(delta_2_Matrix, weight_1_2_Matrix, delta_1_Matrix);
			math::product(delta_1_Matrix, dropout_1_Matrix, delta_1_Matrix);
			math::product(delta_1_Matrix, derivative_1_Matrix, delta_1_Matrix);

			// Error
			// Math::Product(delta_2_Matrix, delta_2_Matrix, error_2_Matrix);
			// error += Math::Sum(error_2_Matrix) / batchSize;

			// CorrectPredict
			math::argmaxByRow(label_2_Matrix, label_Vector);
			math::argmaxByRow(layer_2_Matrix, predict_Vector);

			for (uint32_t k = 0; k < batchSize; ++k) {
				if (predict_Vector(k) == label_Vector(k)) {
					correctPredict += 1.0f;
				}
			}

			math::outerProduct(layer_0_Matrix, delta_1_Matrix, weightDelta_0_1_Matrix);
			math::outerProduct(layer_1_Matrix, delta_2_Matrix, weightDelta_1_2_Matrix);

			math::product(weightDelta_0_1_Matrix, alpha, weightDelta_0_1_Matrix);
			math::product(weightDelta_1_2_Matrix, alpha, weightDelta_1_2_Matrix);

			math::plus(weight_0_1_Matrix, weightDelta_0_1_Matrix, weight_0_1_Matrix);
			math::plus(weight_1_2_Matrix, weightDelta_1_2_Matrix, weight_1_2_Matrix);
		}

		bool check = (iteration % 10 == 0) || (iteration == iterations - 1);

		if (!check) { continue; }

		// error          /= trainBatches;
		correctPredict /= trainBatches * batchSize;

		std::cout << std::setprecision(3) << std::fixed;
		std::cout << "[" << std::setw(4) << iteration << "] ";
		std::cout << "Train correct predict: " << correctPredict;

		// error = 0.0f;
		correctPredict = 0;

		for (uint32_t batchIndex = 0; batchIndex < testBatches; ++batchIndex) {

			testMNIST.getBatchImages(
					testSamples_Vector,
					batchSize,
					batchIndex,
					layer_0_Matrix);

			testMNIST.getBatchLabels(
					testSamples_Vector,
					batchSize,
					batchIndex,
					label_2_Matrix);

			// Forward
			math::dot(layer_0_Matrix, weight_0_1_Matrix, layer_1_Matrix);
			math::tanh(layer_1_Matrix);
			math::dot(layer_1_Matrix, weight_1_2_Matrix, layer_2_Matrix);
			math::softmax(layer_2_Matrix);

			// Delta
			math::minus(label_2_Matrix, layer_2_Matrix, delta_2_Matrix);

			// Error
			// Math::Product(delta_2_Matrix, delta_2_Matrix, error_2_Matrix);
			// error += Math::Sum(error_2_Matrix) / batchSize;

			// CorrectPredict
			math::argmaxByRow(label_2_Matrix, label_Vector);
			math::argmaxByRow(layer_2_Matrix, predict_Vector);

			for (uint32_t k = 0; k < batchSize; ++k) {
				if (predict_Vector(k) == label_Vector(k)) {
					correctPredict += 1.0f;
				}
			}
		}

		// error          /= testBatches;
		correctPredict /= testBatches * batchSize;

		std::cout << std::setprecision(3) << std::fixed;
		std::cout << " Test correct predict: " << correctPredict;
		std::cout << std::endl;
	}

	//-------------------------------------------------------------------------

	// Layers
	Vector<float> layer_0_Vector(layer_0_Size);
	Vector<float> layer_1_Vector(layer_1_Size);
	Vector<float> layer_2_Vector(layer_2_Size);

	// Image
	Image image(path);

	uint8_t* data = image.getData();

	for (size_t i = 0; i < 28 * 28; ++i) {
		layer_0_Vector(i) = data[i] / 255.0f;
	}

	// Forward
	math::transposeDot(layer_0_Vector, weight_0_1_Matrix, layer_1_Vector);
	math::tanh(layer_1_Vector);
	math::transposeDot(layer_1_Vector, weight_1_2_Matrix, layer_2_Vector);
	math::softmax(layer_2_Vector);

	std::cout << "Predict: " << math::argmax(layer_2_Vector) << std::endl;

	//-------------------------------------------------------------------------

	auto end = high_resolution_clock::now();

	std::cout << "time: " << duration_cast<microseconds>(end - start).count() << " mc" << std::endl;

	//-------------------------------------------------------------------------
}

} // namespace simple
