#include "Process.h"

#include <mpi.h>
#include <iostream>
#include<sstream>
#include <random>


std::random_device rd;
std::mt19937 mersenne(rd());

int32_t getRanomInt(int32_t begin, int32_t end) {
	return begin + mersenne() % (end - begin + 1);
}

void fillSizes(int32_t* data, int32_t processNumber, int32_t vectorLength, int32_t* boundaries)
{
	for (size_t i{ 0 }; i < processNumber; ++i) {
		if (vectorLength % (processNumber - i) == 0) {
			data[i] = (vectorLength / (processNumber - i));
		}
		else {
			data[i] = (vectorLength / (processNumber - i)) + 1;
		}

		vectorLength -= data[i];

		if (i) {
			boundaries[i] = boundaries[i - 1] + data[i - 1];
		}
		else {
			boundaries[i] = 0;
		}
	}
}

void fillMatrix(int32_t** matrix, int32_t M, int32_t L) {
	for (size_t i{ 0 }; i < M; ++i){
		for (size_t j{ 0 }; j < L; ++j) {
			matrix[i][j] = getRanomInt(-5, 5);
		}
	}
}

void convertMatrixToVector(int32_t** matrix, int32_t* vectorOut, int32_t M, int32_t L) {
	for (size_t i{ 0 }; i < M; ++i) {
		for (size_t j{ 0 }; j < L; ++j) {
			vectorOut[i * L + j] = matrix[i][j];
		}
	}
}

void convertFromVectorToMatrix(int32_t* vector, int32_t** matrix, int32_t M, int32_t L){
	for (size_t i{ 0 }; i < M * L; ++i){
		matrix[i / L][i % L] = vector[i];
	}
}

constexpr int32_t VECTOR_SIZE{ 5 };

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int32_t processNumber, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &processNumber);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int32_t* vector1{ nullptr };
	int32_t* vector2{ nullptr };
	int32_t* answer{ nullptr };

	int32_t** matrix1{ nullptr };
	int32_t** matrix2 {nullptr};

	int M, L;

	std::stringstream convert1(argv[1]);
	if (!(convert1 >> M)) {
		M = 0;
	}

	std::stringstream convert2(argv[2]);
	if (!(convert2 >> L)) {
		L = 0;
	}

	if (!rank) {
		std::cout << "\nTotal number of processes: " << processNumber << "\n";

		vector1 = new int32_t[M * L];
		vector2 = new int32_t[M * L];
		answer = new int32_t[M * L];

		matrix1 = new int32_t* [M];
		for (size_t i{ 0 }; i < M; ++i) {
			matrix1[i] = new int32_t[L];
		}

		matrix2 = new int32_t* [M];
		for (size_t i{ 0 }; i < M; ++i) {
			matrix2[i] = new int32_t[L];
		}

		fillMatrix(matrix1, M, L);
		std::cout << "The first matrix: \n";
		for (size_t i{ 0 }; i < M; ++i)
		{
			for (size_t j{ 0 }; j < L; ++j)
				std::cout << "\t" << matrix1[i][j];
			std::cout << "\n";
		}
		std::cout << "\n";


		fillMatrix(matrix2, M, L);
		std::cout << "The second matrix: \n";

		for (size_t i{ 0 }; i < M; ++i)
		{
			for (size_t j{ 0 }; j < L; ++j)
				std::cout << "\t" << matrix2[i][j];
			std::cout << "\n";
		}
		std::cout << "\n";

		vector1 = new int32_t[M * L];
		convertMatrixToVector(matrix1,vector1, M, L);
		vector2 = new int32_t[M * L];
		convertMatrixToVector(matrix2,vector2, M, L);
	}

	int32_t* sizes = new int32_t[processNumber];
	int32_t* boundaries = new int32_t[processNumber];

	fillSizes(sizes, processNumber, M*L, boundaries);

	const int32_t MAX_SLICE_SIZE{ (M*L / processNumber) + 1 };

	int32_t* slice1 = new int32_t[MAX_SLICE_SIZE];
	MPI_Scatterv(vector1, sizes, boundaries, MPI_INT, slice1, sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);

	int32_t* slice2 = new int32_t[MAX_SLICE_SIZE];
	MPI_Scatterv(vector2, sizes, boundaries, MPI_INT, slice2, sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);

	int32_t sum{ 0 };
	for (size_t i{ 0 }; i < sizes[rank]; ++i) {
		slice1[i] += slice2[i];
	}

	MPI_Gatherv(slice1, sizes[rank], MPI_INT, answer, sizes, boundaries, MPI_INT, 0, MPI_COMM_WORLD);

	if (!rank) {
		convertFromVectorToMatrix(answer, matrix1, M, L);
		std::cout << "Answer Matrix:\n";

		for (size_t i{ 0 }; i < M; i++) {
			for (int j = 0; j < L; j++)
				std::cout << "\t" << matrix1[i][j];

			std::cout << "\n";
		}
		for (size_t i{ 0 }; i < M; ++i) {
			delete[] matrix1[i];
		}
		delete[] matrix1;

		for (size_t i{ 0 }; i < M; ++i) {
			delete[] matrix2[i];
		}
		delete[] matrix2;

		delete[] vector1;
		delete[] vector2;
		delete[] answer;
	}
	delete[] slice1;
	delete[] slice2;
	delete[] boundaries;
	delete[] sizes;

	MPI_Finalize();
	return 0;
}