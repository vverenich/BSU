#include "pch.h"
#include <mpi.h>
#include "Process.h"

namespace MPI
{

	Process::Process()
	{

		

	}

	Process::~Process()
	{
		MPI_Finalize();
	}

	int Process::GetProcessCount() const
	{
		return _processCount;
	}

	int Process::GetRank() const
	{
		return _rank;
	}

	bool Process::IsMaster() const
	{
		return GetRank() == MasterRank;
	}
}