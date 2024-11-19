#include "Process.h"

#include <mpi.h>
#include <iostream>
#include <random>


std::random_device rd;
std::mt19937 mersenne(rd());

int32_t getRanomInt(int32_t begin, int32_t end) {
	return begin + mersenne() % (end - begin + 1);
}

void fillVector(int32_t* vector, int32_t length, int32_t begin, int32_t end) {
	for (size_t i{ 0 }; i < length; ++i) {
		vector[i] = getRanomInt(begin, end);
	}
}

void printVector(std::ostream& out, int32_t* vector, int32_t size) {
	for (size_t i{ 0 }; i < size; ++i) {
		std::cout << "\t" << vector[i];
	}
	std::cout << "\n";
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

int main(int argc, char* argv[])
{	
	MPI_Init(&argc, &argv);

	int32_t processNumber, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &processNumber);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//Process process = Process();

	int32_t* vector1{ nullptr };
	int32_t* vector2{ nullptr };
	int32_t* result{ nullptr };

	if (!rank) {
		std::cout << "\nTotal number of processes: " << processNumber << "\n";

		vector1 = new int32_t[VECTOR_SIZE];
		fillVector(vector1, VECTOR_SIZE, -1, 1);

		std::cout << "The first vector:  ";
		printVector(std::cout, vector1, VECTOR_SIZE);

		vector2 = new int32_t[VECTOR_SIZE];
		fillVector(vector2, VECTOR_SIZE, -1, 1);

		std::cout << "The second vector: ";
		printVector(std::cout, vector2, VECTOR_SIZE);

		result = new int32_t[processNumber];
	}

	int32_t* sizes = new int32_t[processNumber];
	int32_t* boundaries = new int32_t[processNumber];

	fillSizes(sizes, processNumber, VECTOR_SIZE, boundaries);

	const int32_t MAX_SLICE_SIZE{ (VECTOR_SIZE / processNumber) + 1 };
	int32_t* slice1 = new int32_t[MAX_SLICE_SIZE];
	MPI_Scatterv(vector1, sizes, boundaries, MPI_INT, slice1, sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);
	int32_t* slice2 = new int32_t[MAX_SLICE_SIZE];
	MPI_Scatterv(vector2, sizes, boundaries, MPI_INT, slice2, sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);

	int32_t sum{ 0 };
	for (size_t i{ 0 }; i < sizes[rank]; ++i) {
		sum += slice1[i] * slice2[i];
	}

	MPI_Gather(&sum, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (!rank) {
		int32_t answer_sum{ 0 };
		for (size_t i = 0; i < processNumber; ++i) {
			answer_sum += result[i];
		}


		std::cout << "Scalar multiplication of vectors: " << answer_sum << std::endl;


		delete[] vector1;
		delete[] vector2;
		delete[] result;
	}
	delete[] slice1;
	delete[] slice2;
	delete[] boundaries;
	delete[] sizes;

	MPI_Finalize();
	return 0;
}