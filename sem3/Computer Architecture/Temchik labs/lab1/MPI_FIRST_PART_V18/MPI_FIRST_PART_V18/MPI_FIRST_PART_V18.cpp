#include "mpi.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <memory>
#include <utility>
#include <algorithm>

using namespace std;

void printVector(const char* str, double* vector, int length) {
	cout << str << "\t";
	for_each(vector, vector + length, [](const double& x) {cout << x << ",\t"; });
	cout << ")\n\n";
}


void initialize(double* data, int length)
{
	for_each(data, data + length, [](double& x) { x = -rand() % 2; });
}

void fill_sizes(int* data, int process_count, int datalen, int* displs)
{
	int MAX_PROCESSES = (datalen / process_count) + 1;

	for (int i = 0; i < process_count && datalen; ++i) {
		if (datalen < MAX_PROCESSES) {
			data[i] = datalen;
			datalen = 0;
		}
		else {
			data[i] = MAX_PROCESSES;
			datalen -= MAX_PROCESSES;
		}

		displs[i] = (i ? displs[i - 1] + data[i - 1] : 0);
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "You did't enter the length of vectors";
		return -1;
	}

	srand(time(0));
	
	const int DATALENGTH{ atoi(argv[1]) };


	int processCount{}, rank{};
	const int MASTER_RANK{};
	MPI_Init(nullptr, nullptr);
	MPI_Comm_size(MPI_COMM_WORLD, &processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	cout.setf(ios::fixed);
	cout.precision(2);

	unique_ptr<double[]> firstVector{}, secondVector{};
	if (rank == MASTER_RANK)
	{
		firstVector = make_unique<double[]>(DATALENGTH);
		secondVector = make_unique<double[]>(DATALENGTH);

		initialize(firstVector.get(), DATALENGTH);
		initialize(secondVector.get(), DATALENGTH);

		printVector("First:  (", firstVector.get(), DATALENGTH);
		printVector("Second: (", secondVector.get(), DATALENGTH);
	}

	auto sizes = make_unique<int[]>(processCount);
	auto displs = make_unique<int[]>(processCount);

	fill_sizes(sizes.get(), processCount, DATALENGTH, displs.get());


	const int MAX_SIZE = (DATALENGTH + processCount - 1) / processCount;
	auto slice1 = make_unique<double[]>(MAX_SIZE);
	auto slice2 = make_unique<double[]>(MAX_SIZE);

	MPI_Scatterv(firstVector.get(), sizes.get(), displs.get(), MPI_DOUBLE, slice1.get(), sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatterv(secondVector.get(), sizes.get(), displs.get(), MPI_DOUBLE, slice2.get(), sizes[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	double sum = 0;
	for (int i = 0; i < sizes[rank]; i++)
	{
		sum += slice1[i] * slice2[i];
	}


	auto answer = make_unique<double[]>(processCount);
	MPI_Gather(&sum, 1, MPI_DOUBLE, answer.get(), 1, MPI_DOUBLE, MASTER_RANK, MPI_COMM_WORLD);

	if (rank == MASTER_RANK)
	{
		double answer_sum = 0;
		for (int i = 0; i < processCount; i++)
		{
			answer_sum += answer[i];
		}

		cout << "Scalar multiplication = " << answer_sum << "\n" <<
			"Count proccesses: " << processCount;
	}

	MPI_Finalize();
	return 0;
}