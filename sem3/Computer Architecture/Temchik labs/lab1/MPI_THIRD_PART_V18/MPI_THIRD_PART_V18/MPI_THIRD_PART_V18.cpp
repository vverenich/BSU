#include <mpi.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <memory>

using namespace std;

unique_ptr<double[]> createMatrix(int N, int M)
{
	mt19937 gen(time(0));
	unique_ptr<double[]> result = make_unique<double[]>(N * M);
	uniform_int_distribution<> uid(-1, 1);
	for (int i = 0; i < M * N; i++)
	{
		result[i] = uid(gen);
	}

	return move(result);
}


double* multiply(double* firstMatrix, double* secondMatrix, int K, int L, int M)
{
	double* answer = new double[K * M];

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < M; j++)
		{
			answer[i * M + j] = 0;

			for (int k = 0; k < L; k++)
			{
				answer[i * M + j] += firstMatrix[k * K + i] * secondMatrix[k * M + j];
			}
		}
	}

	return answer;
}

void printMatrix(const char* str, double* matrix, int N, int M, bool isTransplant = false)
{
	cout << '\n' << str << '\n';
	if (isTransplant) {
		for (int j = 0; j < M; j++)
		{
			for (int i = 0; i < N; i++)
			{
				cout << matrix[i * M + j] << setw(5);
			}
			cout << '\n';
		}
	}
	else {
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cout << matrix[i * M + j] << setw(6);
			}
			cout << '\n';
		}
	}
	cout << "*************************************\n";
}

void setSize(int processCount, int L, int kOrM,
	int*& countElementsInAllFirstOrSecondSubMatrixes, int*& displs)
{
	countElementsInAllFirstOrSecondSubMatrixes = new int[processCount];
	displs = new int[processCount];
	const int el{ (L / processCount) * kOrM };

	
	for (int i = 0; i < processCount; ++i)
	{
		countElementsInAllFirstOrSecondSubMatrixes[i] = el;
		displs[i] = i * countElementsInAllFirstOrSecondSubMatrixes[i];
	}

	int sh = 0;
	for (int i = 1; i < (L % processCount) + 1; ++i)
	{
		countElementsInAllFirstOrSecondSubMatrixes[i] += kOrM;
		displs[i] += sh; 
		sh += kOrM;
	}

}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);

	int processCount{}, rank{};
	constexpr int MASTER_RANK{};

	MPI_Init(nullptr, nullptr);
	MPI_Comm_size(MPI_COMM_WORLD, &processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int K{}, L{}, M{};

	if (rank == MASTER_RANK)
	{
		cout << "\nEnter values of K, L, M\n";
		cin >> K >> L >> M;
	}

	MPI_Bcast(&M, 1, MPI_DOUBLE, MASTER_RANK, MPI_COMM_WORLD);
	MPI_Bcast(&K, 1, MPI_DOUBLE, MASTER_RANK, MPI_COMM_WORLD);



	double timestart{};
	unique_ptr<double[]> firstMatrix{}, secondMatrix{};
	unique_ptr<int[]> countElementsInThisSubMatrixes = make_unique<int[]>(2);
	int* countElementsInAllSecondSubMatrixes{}, * secondDispls{};
	int* countElementsInAllFirstSubMatrixes{}, * firstDispls{};

	if (rank != MASTER_RANK) {
		MPI_Recv(countElementsInThisSubMatrixes.get(), 2, MPI_INT, MASTER_RANK, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	}
	else {
		firstMatrix = createMatrix(L, K);
		secondMatrix = createMatrix(L, M);

		printMatrix("First Matrix:", firstMatrix.get(), L, K, true);
		printMatrix("Second Matrix:", secondMatrix.get(), L, M, false);

		timestart = MPI_Wtime();
		setSize(processCount, L, K, countElementsInAllFirstSubMatrixes, firstDispls);
		setSize(processCount, L, M, countElementsInAllSecondSubMatrixes, secondDispls);

		for (int i = 0; i < processCount; i++) {
			countElementsInThisSubMatrixes[0] = countElementsInAllFirstSubMatrixes[i];
			countElementsInThisSubMatrixes[1] = countElementsInAllSecondSubMatrixes[i];

			if (i) {
				MPI_Send(countElementsInThisSubMatrixes.get(), 2, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
		}
	}


	auto firstSubMatrix = make_unique<double[]>(countElementsInThisSubMatrixes[0]);
	auto secondSubMatrix = make_unique<double[]>(countElementsInThisSubMatrixes[1]);

	MPI_Scatterv(firstMatrix.get(), countElementsInAllFirstSubMatrixes, firstDispls, MPI_DOUBLE,
		firstSubMatrix.get(), countElementsInThisSubMatrixes[0], MPI_DOUBLE, MASTER_RANK, MPI_COMM_WORLD);
	MPI_Scatterv(secondMatrix.get(), countElementsInAllSecondSubMatrixes, secondDispls, MPI_DOUBLE,
		secondSubMatrix.get(), countElementsInThisSubMatrixes[1], MPI_DOUBLE, MASTER_RANK, MPI_COMM_WORLD);



	unique_ptr<double[]> answer{};
	if (rank == MASTER_RANK) {
		answer = make_unique<double[]>(K * M);
	}


	MPI_Reduce(multiply(firstSubMatrix.get(), secondSubMatrix.get(), K, countElementsInThisSubMatrixes[0] / K, M), answer.get(), K * M, MPI_DOUBLE, MPI_SUM, MASTER_RANK, MPI_COMM_WORLD);

	if (rank == MASTER_RANK) {
		cout.precision(2);
		printMatrix("Answer Matrix:", answer.get(), K, M);

		cout << "\n\nTime: " << setprecision(7) << MPI_Wtime() - timestart << "\n";
		cout << "\nProcess Count: " << processCount << "\n";

		delete[] countElementsInAllFirstSubMatrixes, delete[] firstDispls;
		delete[] countElementsInAllSecondSubMatrixes, delete[] secondDispls;
	}
	MPI_Finalize();
	return 0;
}