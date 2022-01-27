#include <mpi.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <random>

 void findDifference(int firstSlice[], int secondSlice[], int l) {
	for (int i = 0; i < l; ++i) {
		firstSlice[i] -= secondSlice[i];
	}
}

 void printMatrix(const char* str, int** matrix, const int M, const int L) {
	std::cout << str << "\n";
	for (auto i = 0; i < M; i++)
	{
		for (int j = 0; j < L; j++)
			std::cout << std::setw(8) << matrix[i][j] << "|";
		std::cout << "\n";
	}
	std::cout << "*******************************************************************" << "\n";
}

 void Fill(int** data, int M, int L, std::mt19937 &gen)
{
	std::uniform_int_distribution<> uid(-30, 30);
	for (auto i = 0; i < M; i++)
	{
		for (int j = 0; j < L; j++)
			data[i][j] = uid(gen);
	}
}
 void setSize(int* data, int process_count, int datalen, int* displs)
{
	int after = datalen;
	int MAX_PROCESSES = (after / process_count) + 1;

	for (int i = 0; i < process_count && after; ++i) {
		if (after < MAX_PROCESSES) {
			data[i] = after;
			after = 0;
		}
		else {
			data[i] = MAX_PROCESSES;
			after -= MAX_PROCESSES;
		}

		displs[i] = (i ? displs[i - 1] + data[i - 1] : 0);
	}
}

 std::unique_ptr<int[]> ConvertToVector(int** matrix, int M, int L)
{
	auto answer = std::make_unique<int[]>(M * L);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < L; j++)
		{
			answer[i * L + j] = matrix[i][j];
		}
	}

	return move(answer);
}
 void ConvertToMatrix(int* vector, int M, int L, int** matrix)
{
	for (int i = 0; i < M * L; i++)
	{
		matrix[i / L][i % L] = vector[i];
	}
}

 void printAnswerMatrixAndFreeMemory(std::unique_ptr<int[]> answer, const int M, const int L,
	int**& matrix1, int**& matrix2, int processCount) {

	ConvertToMatrix(answer.get(), M, L, matrix1);
	printMatrix("Answer Matrix:", matrix1, M, L);

	std::cout << "\n\nProcess count: " << processCount << "\n";

	for (int i = 0; i < M && matrix1; i++)
		delete[] matrix1[i];
	delete[] matrix1;

	for (int i = 0; i < M && matrix2; i++)
		delete[] matrix2[i];
	delete[] matrix2;
}

int main()
{
	using namespace std;

	mt19937 gen(time(0));
	int processCount{}, rank{};
	const int MASTER_RANK{};
	MPI_Init(nullptr, nullptr);
	MPI_Comm_size(MPI_COMM_WORLD, &processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	unique_ptr<int[]> data1{}, data2{}, answer{};

	const int M = 5;
	const int L = 5;

	int** matrix1 = nullptr;
	int** matrix2 = nullptr;
	if (rank == MASTER_RANK)
	{
		data1 = make_unique<int[]>(M * L);
		data2 = make_unique<int[]>(M * L);
		answer = make_unique<int[]>(M * L);

		matrix1 = new int* [M];
		matrix2 = new int* [M];

		for_each(matrix1, matrix1 + M, [L](int*& x) { x = new int[L]; });
		for_each(matrix2, matrix2 + M, [L](int*& x) { x = new int[L]; });

		Fill(matrix1, M, L, gen);
		Fill(matrix2, M, L, gen);

		printMatrix("First Matrix: ", matrix1, M, L);
		printMatrix("Second Matrix: ", matrix2, M, L);

		data1 = ConvertToVector(matrix1, M, L);
		data2 = ConvertToVector(matrix2, M, L);
	}

	auto sizes = make_unique<int[]>(processCount);
	auto displs = make_unique<int[]>(processCount);

	setSize(sizes.get(), processCount, M * L, displs.get());

	const int MAX_SIZE{ M * L / processCount + 1 };
	auto first_matrix_slice = make_unique<int[]>(MAX_SIZE);
	auto second_matrix_slice = make_unique<int[]>(MAX_SIZE);

	MPI_Scatterv(data1.get(), sizes.get(), displs.get(), MPI_INT, first_matrix_slice.get(), sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatterv(data2.get(), sizes.get(), displs.get(), MPI_INT, second_matrix_slice.get(), sizes[rank], MPI_INT, 0, MPI_COMM_WORLD);

	findDifference(first_matrix_slice.get(), second_matrix_slice.get(), sizes[rank]);

	MPI_Gatherv(first_matrix_slice.get(), sizes[rank], MPI_INT, answer.get(), sizes.get(), displs.get(), MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == MASTER_RANK)
	{
		printAnswerMatrixAndFreeMemory(move(answer), M, L, matrix1, matrix2, processCount);
	}

	MPI_Finalize();
	return 0;
}