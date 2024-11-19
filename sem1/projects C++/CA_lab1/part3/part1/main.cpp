#include "Process.h"

#include <mpi.h>
#include <iostream>
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

constexpr int32_t VECTOR_SIZE{ 5 };

void generateVector(double* vector, int32_t N, int32_t M)
{
	for (size_t i{ 0 }; i < M * N; ++i) {
		vector[i] = getRanomInt(-1, 1);
	}
}

void printVectorAsMatrix(double* matrix, int32_t N, int32_t M)
{
	for (size_t j{ 0 }; j < M; ++j) {
		for (size_t i{ 0 }; i < N; ++i) {
			std::cout << matrix[i * M + j] << "\t";
		}
		std::cout << '\n';
	}
}
void printTransplantMatrix(double* matrix, int N, int M)
{
	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < N; i++)
		{
			std::cout << matrix[i * M + j] << "\t";
		}
		std::cout << '\n';
	}
}
void printMatrix(double* matrix, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cout << matrix[i * M + j] << "\t";
		}
		std::cout << '\n';
	}
}
void countSlices(int32_t processNumber, int32_t N, int32_t M, int*& slices, int*& positions)
{
	slices = new int[processNumber];
	positions = new int[processNumber];

	for (size_t i{ 0 }; i < processNumber; ++i) {
		slices[i] = (N * M) / processNumber;
		positions[i] = i * slices[i];
	}

	for (size_t i{ 1 }, shift{ 0 }; i < (N % processNumber) + 1; ++i, shift += M) {
		slices[i] += M;
		positions[i] += shift;
	}
}

double* multiply(double* firstMatrix, double* secondMatrix, int32_t K, int32_t dimC, int32_t M)
{
	double* answer = new double[K * M];

	for (size_t i{ 0 }; i < K; ++i) {
		for (size_t j{ 0 }; j < M; ++j) {
			answer[i * M + j] = 0;

			for (size_t k{ 0 }; k < dimC; ++k) {
				answer[i * M + j] += firstMatrix[k * K + i] * secondMatrix[k * M + j];
			}
		}
	}

	return answer;
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int32_t processNumber, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &processNumber);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int32_t K, L, M;

	if (!rank) {
		std::cout << "Enter K, L, M: \n";
		std::cin >> K >> L >> M;
	}

	MPI_Bcast(&K, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&M, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	double* firstMatrix{ nullptr }, * secondMatrix{ nullptr },
		* firstSlice{ nullptr }, * secondSlice{ nullptr },
		* answer{ nullptr }, * result{ nullptr };

	int* firstSlices{ nullptr }, * firstPosition{ nullptr },
		* secondSlices{ nullptr }, * secondPosition{ nullptr },
		sliceSizes[2];
	double timestart, timefinish;


	if (!rank) {
		firstMatrix = new double[K * L];
		generateVector(firstMatrix, K, L);
		secondMatrix = new double[L * M];
		generateVector(secondMatrix, L, M);

		std::cout << "\nFirst Matrix:\n";
		printTransplantMatrix(firstMatrix, L, K);
		std::cout << "\nSecond Matrix:\n";
		printMatrix(secondMatrix, L, M);

		timestart = MPI_Wtime();
		countSlices(processNumber, L, K, firstSlices, firstPosition);
		countSlices(processNumber, L, M, secondSlices, secondPosition);

		for (size_t i{ 1 }; i < processNumber; ++i) {
			sliceSizes[0] = firstSlices[i];
			sliceSizes[1] = secondSlices[i];

			MPI_Send(sliceSizes, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

		sliceSizes[0] = firstSlices[0];
		sliceSizes[1] = secondSlices[0];
	}
	else {
		MPI_Recv(sliceSizes, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	}

	firstSlice = new double[sliceSizes[0]];
	secondSlice = new double[sliceSizes[1]];


	MPI_Scatterv(firstMatrix, (int*)firstSlices, (int*)firstPosition, MPI_DOUBLE, firstSlice, sliceSizes[0], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatterv(secondMatrix, (int*)secondSlices, (int*)secondPosition, MPI_DOUBLE, secondSlice, sliceSizes[1], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	result = multiply(firstSlice, secondSlice, K, sliceSizes[0] / K, M);

	if (!rank) {
		answer = new double[K * M];
	}

	MPI_Reduce(result, answer, K * M, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (!rank){
		std::cout << "\nTime: " << MPI_Wtime() - timestart << "\n";
		std::cout << "\nResult:\n";
		printMatrix(answer, M, K);
	}


	delete[] firstSlice;
	delete[] secondSlice;
	delete[] result;

	if (!rank)
	{
		delete[] firstMatrix;
		delete[] secondMatrix;
		delete[] firstSlices;
		delete[] firstPosition;
		delete[] secondSlices;
		delete[] secondPosition;
		delete[] answer;
	}
}