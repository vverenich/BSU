#include "tasks.h"

Tasks::Tasks()
{
    m_printer = new Printer();

    mkdir(m_dirNameForTasks1_8.c_str());
    mkdir(m_dirNameForTask9A1.c_str());
    mkdir(m_dirNameForTask9A2.c_str());
    mkdir(m_dirNameForTask10.c_str());
}

Tasks::~Tasks()
{
    if(m_printer != nullptr)
    {
        delete m_printer;
    }
}

double Tasks::fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


// Fill upper triangle of matrix A with rational random numbers from a
// half-interval[-2^(N/4), 2^(N/4)]. Fill lower triangle of matrix A
// in the way that A = A^T. Diagonal elements get from the
// formula 𝑎𝑖𝑖 = 1 + ∑ |𝑎𝑖𝑗|
//
// N = 4
//
void Tasks::performTask1(bool printResults)
{
    constexpr auto SIZE{256};

    Matrix A(SIZE, SIZE);

    // Filling the matrix, but leaving the diagonal unfilled
    for(unsigned i{0}; i < A.getRowCount(); ++i)
    {
        for(unsigned j{1+i}; j < A.getColumnCount(); ++j)
        {
            A.setMatrixElement(i, j, fRand(std::pow(-2, (double)N / 4), std::pow(2, (double)N / 4)));
            A.setMatrixElement(j, i, A.getMatrixElement(i, j));
        }
    }

    // Filling diagonal
    for(unsigned i{0}; i < A.getRowCount(); ++i)
    {
        double sum{0};
        for(unsigned j{0}; j < A.getColumnCount(); ++j)
        {
            if(i != j)
            {
                sum += std::abs(A.getMatrixElement(i, j));
            }
        }
        A.setMatrixElement(i, i, sum);
    }

    Matrix transposedA = A.getTransposedMatrix();
    m_A = A;

    m_printer->setFolderName(m_dirNameForTasks1_8);
    if(printResults)
    {
        m_printer->setFileName("task1A.txt");
        *m_printer->m_fout<<A;
    }
}

// Fill the vector 𝑦 with the length corresponding to the size of the matrix 𝐴
// with rational random numbers from the half-interval [−2^(N/4), 2^(N/4)].
// Multiplying the matrix 𝐴 by the vector 𝑦 we get the vector of the right side 𝑏.
// Thus, we have SLAE 𝐴𝑥 = 𝑏, exact whose solution is the vector 𝑦.

void Tasks::performTask2(bool printResults)
{
    Matrix y(m_A.getColumnCount(), 1);


    // Filling the vector with random numbers
    for(size_t i{0}; i < y.getRowCount(); ++i)
    {
        y.setMatrixElement(i, 0, fRand(std::pow(-2, (double)N / 4), std::pow(2, (double)N / 4)));
    }

    m_b = m_A * y;

    if(printResults)
    {
        m_printer->setFileName("task2A.txt");
        *m_printer->m_fout<<m_A;

        m_printer->setFileName("task2y.txt");
        *m_printer->m_fout<<y;

        m_printer->setFileName("task2b.txt");
        *m_printer->m_fout<<m_b;
    }

    m_y = y;
}

// Find the condition number of matrix 𝐴, calculate 𝐴^-1 using Gauss-Jordan method,
// as the norm of the matrix, choose cubic norm
double Tasks::performTask3(bool printResults)
{
    GaussJordan gaussJordan{};

    Matrix b(Matrix::getIdentityMatrix(m_A.getRowCount(), m_A.getColumnCount()));
    Matrix invertedMatrixA(gaussJordan.solveSystem(m_A, b));

    // Condition number of matrix A is equal to ||A|| * ||A^(-1)||
    double condA{m_A.getNorm3() * invertedMatrixA.getNorm3()};

    if(printResults)
    {
        m_printer->setFileName("task3A.txt");
        *m_printer->m_fout<<m_A;

        m_printer->setFileName("task3AInverted.txt");
        *m_printer->m_fout<<invertedMatrixA;

        m_printer->setFileName("task3Acond.txt");
        *m_printer->m_fout<<condA;
    }

    return condA;
}

// Solve 𝐴𝑥 = 𝑏 using the Gaussian method with the
// choice of the main element by column.
Matrix Tasks::performTask4(bool printResults)
{
    GaussColumnSelection gaussColumnSelection{};

    Matrix x{gaussColumnSelection.solveSystem(m_A, m_b)};

    if(printResults)
    {
        m_printer->setFileName("task4A.txt");
        *m_printer->m_fout<<m_A;

        m_printer->setFileName("task4b.txt");
        *m_printer->m_fout<<m_b;

        m_printer->setFileName("task4x.txt");
        *m_printer->m_fout<<x;
    }

    return x;
}

// Get the 𝐿𝑈𝑃-decomposition of the matrix 𝐴 and solve the resulting system.
Matrix Tasks::performTask5(bool printResults)
{
    Matrix L{};
    Matrix U{};
    Matrix P{};

    m_A.getLUPdecomp(L, U, P);

    GaussColumnSelection gaussColumnSelection{};
    Matrix UPx{gaussColumnSelection.solveSystem(L, m_b)};
    Matrix Px{gaussColumnSelection.solveSystem(U, UPx)};
    Matrix x{gaussColumnSelection.solveSystem(P.getTransposedMatrix(), Px)};

    if(printResults)
    {
        m_printer->setFileName("task5L.txt");
        *m_printer->m_fout<<L;

        m_printer->setFileName("task5U.txt");
        *m_printer->m_fout<<U;

        m_printer->setFileName("task5P.txt");
        *m_printer->m_fout<<P;

        m_printer->setFileName("task5x.txt");
        *m_printer->m_fout<<x;
    }

    return x;
}

//Solve the 𝐴𝑥 = 𝑏 using the square root method. Write out
// 𝐿𝐷𝐿^𝑇-decomposition of the matrix of the system.
Matrix Tasks::performTask6(bool printResults)
{
    Matrix L{};
    Matrix D{};
    Matrix Ltransposed{};

    m_A.getLDLtransposedDecomp(L, D, Ltransposed);

    GaussColumnSelection gaussColumnSelection{};
    Matrix DLtransposedx{gaussColumnSelection.solveSystem(L, m_b)};
    Matrix Ltransposedx{gaussColumnSelection.solveSystem(D, DLtransposedx)};
    Matrix x{gaussColumnSelection.solveSystem(Ltransposed, Ltransposedx)};

    if(printResults)
    {
        m_printer->setFileName("task6L.txt");
        *m_printer->m_fout<<L;

        m_printer->setFileName("task6D.txt");
        *m_printer->m_fout<<D;

        m_printer->setFileName("task6Ltransposed.txt");
        *m_printer->m_fout<<Ltransposed;

        m_printer->setFileName("task6x.txt");
        *m_printer->m_fout<<x;
    }

    return x;
}

// Get the most accurate solution of the 𝐴𝑥 = 𝑏 by the relaxation method
// (with parameter 1 − 𝑁/40). Include in the report convergence proof.
Matrix Tasks::performTask7(bool printResults)
{
    Relaxation relaxation;
    size_t numberOfIterations;
    std::vector<std::pair<size_t, double>> v;
    Matrix x{relaxation.solveSystem(m_A, m_b, 1 - (double)4 / 40, numberOfIterations, v)};

    if(printResults)
    {
        m_printer->setFileName("task7x.txt");
        *m_printer->m_fout<<x;
    }

    return x;
}

// In order to get rid of duplicating when setting max, min values
// of norms, condition numbers and etc
template <class T>
void setMaxMinAndSum(T number, T &min, T &max, T &sum)
{
    if(number < min)
    {
        min = number;
    }

    if(number > max)
    {
        max = number;
    }

    sum += number;
}

//Do steps 1-7 a hundred times and output the report in .txt format. The report should include:

//  • The minimum and maximum condition number, as well as the arithmetic mean for all matrices.
//    The matrix with the maximum condition number must be saved in a separate file (it will be
//    needed later).
//
//  • Average time to find the inverse matrix.
//
//  • For each of the used methods for solving SLAE, indicate the minimum, maximum and average
//    norms of the difference of the solution with the exact solution 𝑦. Take the cubic norm
//    as the vector norm.
//
//  • Average time of solution of SLAE by the Gauss method.
//
//  • Average construction time of the 𝐿𝑈𝑃-decomposition.
//
//  • Average SLAE solution time 𝐿𝑈𝑥 = 𝑏̃.
//
//  • Average time for solving SLAE by the square root method.
//
//  • Average time for SLAE solution by the relaxation method.
//
//  • The maximum, average and minimum number of iterations of the relaxation method required
//    to obtain an approximate solution.
void Tasks::performTask8()
{
    const size_t NUMBER_OF_ITERATIONS{100};

    // Variables needed for performing subparagraph 1
    double maxCondNumber{std::numeric_limits<double>::min()};
    double minCondNumber{std::numeric_limits<double>::max()};
    double sumCondNumbers{0};

    // Variables needed for performing subparagraph 2
    double timeTotalInvertedMatrixCalc{0};

    // Variables needed for performing subparagraph 3
    double minNormGauss{std::numeric_limits<double>::max()};
    double maxNormGauss{std::numeric_limits<double>::min()};
    double sumNormGauss{0};

    double minNormLUxb{std::numeric_limits<double>::max()};
    double maxNormLUxb{std::numeric_limits<double>::min()};
    double sumNormLUxb{0};

    double minNormSqrt{std::numeric_limits<double>::max()};
    double maxNormSqrt{std::numeric_limits<double>::min()};
    double sumNormSqrt{0};

    double minNormRelaxation{std::numeric_limits<double>::max()};
    double maxNormRelaxation{std::numeric_limits<double>::min()};
    double sumNormRelaxation{0};

    // Variables needed for performing subparagraph 4
    double timeTotalGaussCalc{0};

    // Variables needed for performing subparagraph 5
    double timeTotalLUPdecompCalc{0};

    // Variables needed for performing subparagraph 6
    double timeTotalLUxbCalc{0};

    // Variables needed for performing subparagraph 7
    double timeTotalSqrtCalc{0};

    // Variables needed for performing subparagraph 8
    double timeTotalRelaxationCalc{0};

    // Variables needed for performing subparagraph 9
    size_t maxRelaxationIteartions{std::numeric_limits<size_t>::min()};
    size_t minRelaxationIteartions{std::numeric_limits<size_t>::max()};
    size_t sumRelaxationIteartions{0};

    for(size_t i{0}; i < NUMBER_OF_ITERATIONS; ++i)
    {
        performTask1(0);
        performTask2(0);

        m_timer.reset();
        double condNumber{performTask3(0)};
        timeTotalInvertedMatrixCalc += m_timer.elapsed();
        setMaxMinAndSum(condNumber, minCondNumber, maxCondNumber, sumCondNumbers);
        if(maxCondNumber == condNumber)
        {
            m_maxCondMatrix = m_A;
            m_printer->setFileName("task8MaxCondMatrix.txt");
            *m_printer->m_fout<<m_A;
        }

        m_timer.reset();
        Matrix xGauss{performTask4(0)};
        timeTotalGaussCalc += m_timer.elapsed();
        setMaxMinAndSum((xGauss + (-m_y)).getNorm3(), minNormGauss, maxNormGauss, sumNormGauss);

        Matrix L{m_A};
        Matrix U{m_A};
        Matrix P{m_A};
        m_timer.reset();
        m_A.getLUPdecomp(L, U, P);
        double timeLUPdecompCalc = m_timer.elapsed();
        timeTotalLUPdecompCalc += timeLUPdecompCalc;

        m_timer.reset();
        Matrix xLUxb{performTask5(0)};
        timeTotalLUxbCalc += (m_timer.elapsed() - timeLUPdecompCalc);
        setMaxMinAndSum((xLUxb + (-m_y)).getNorm3(), minNormLUxb, maxNormLUxb, sumNormLUxb);

        m_timer.reset();
        Matrix xSqrt{performTask6(0)};
        timeTotalSqrtCalc += m_timer.elapsed();
        setMaxMinAndSum((xSqrt + (-m_y)).getNorm3(), minNormSqrt, maxNormSqrt, sumNormSqrt);

        m_timer.reset();
        Relaxation relaxation;
        size_t numberOfIterations;
        std::vector<std::pair<size_t, double>> v;
        Matrix xRelaxation{relaxation.solveSystem(m_A, m_b, 1 - (double)4 / 40, numberOfIterations, v)};
        timeTotalRelaxationCalc += m_timer.elapsed();
        setMaxMinAndSum((xRelaxation + (-m_y)).getNorm3(), minNormRelaxation, maxNormRelaxation, sumNormRelaxation);
        setMaxMinAndSum(numberOfIterations, minRelaxationIteartions, maxRelaxationIteartions, sumRelaxationIteartions);
    }

    m_printer->setFileName("task8report.txt");

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tMax condition number:     " << maxCondNumber;
    *m_printer->m_fout<<"\n\tMin condition number:     " << minCondNumber;
    *m_printer->m_fout<<"\n\tAverage condition number: " << sumCondNumbers / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tAverage time for inverted matrix calculation: " << timeTotalInvertedMatrixCalc / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tMax norm (x(gauss) - y):     " << maxNormGauss;
    *m_printer->m_fout<<"\n\tMin norm (x(gauss) - y):     " << minNormGauss;
    *m_printer->m_fout<<"\n\tAverage norm (x(gauss) - y): " << sumNormGauss / NUMBER_OF_ITERATIONS;
    *m_printer->m_fout<<"\n\n";
    *m_printer->m_fout<<"\n\tMax norm (x(LUxb) - y):     " << maxNormLUxb;
    *m_printer->m_fout<<"\n\tMin norm (x(LUxb) - y):     " << minNormLUxb;
    *m_printer->m_fout<<"\n\tAverage norm (x(LUxb) - y): " << sumNormLUxb / NUMBER_OF_ITERATIONS;
    *m_printer->m_fout<<"\n\n";
    *m_printer->m_fout<<"\n\tMax norm (x(Sqrt) - y):     " << maxNormSqrt;
    *m_printer->m_fout<<"\n\tMin norm (x(Sqrt) - y):     " << minNormSqrt;
    *m_printer->m_fout<<"\n\tAverage norm (x(Sqrt) - y): " << sumNormSqrt / NUMBER_OF_ITERATIONS;
    *m_printer->m_fout<<"\n\n";
    *m_printer->m_fout<<"\n\tMax norm (x(Relaxation) - y):     " << maxNormRelaxation;
    *m_printer->m_fout<<"\n\tMin norm (x(Relaxation) - y):     " << minNormRelaxation;
    *m_printer->m_fout<<"\n\tAverage norm (x(Relaxation) - y): " << sumNormRelaxation / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tAverage time for calculations using Gauss method : " << timeTotalGaussCalc / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tAverage time for LUP-decomposition calculation: " << timeTotalLUPdecompCalc / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tAverage time for solving system LUx = b~: " << timeTotalLUxbCalc / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tAverage time for calculations using sqrt method: " << timeTotalSqrtCalc / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tAverage time for calculations using relaxation method: " << timeTotalRelaxationCalc / NUMBER_OF_ITERATIONS;

    *m_printer->m_fout<<"\n*";
    *m_printer->m_fout<<"\n\tMax iteration number in relaxation method:     " << maxRelaxationIteartions;
    *m_printer->m_fout<<"\n\tMin iteration number in relaxation method:     " << minRelaxationIteartions;
    *m_printer->m_fout<<"\n\tAverage iteration number in relaxation method: " << sumRelaxationIteartions / NUMBER_OF_ITERATIONS;
}

Matrix getMatrixA1()
{
    std::vector<std::vector<double>> matrix{
        {N*N + 15, N - 1    , -1     , -2      },
        {N - 1   , -15 - N*N, -N + 4 , -4      },
        {-1      , -N + 4   , N*N + 8, -N      },
        {-2      , -4       , -N     , N*N + 10}
    };

    return Matrix(matrix);
}

Matrix getMatrixA2()
{
    std::vector<std::vector<double>> matrixA_{
        {1       , N + 1      , 2+N        , 3+N          , 4+N         , 5+N         , 6+N          , 7+N},
        {100*N   , 1000*N     , 10000*N    , 100000*N     , -1000*N     , -10000*N    , -100000*N    , 1},
        {N       , -1+N       , -2+N       , -3+N         , -4+N        , -5+N        , -6+N         , -7+N},
        {N-1000  , 10*N-1000  , 100*N-1000 , 1000*N-1000  , 10000*N-1000, -N          , -N+1         , -N+2},
        {-2*N    , 0          , -1         , -2           , -3          , -4          , -5           , -6},
        {N-2019  , -N + 2020  , N-2021     , -N+2022      , N-2023      , -N+2024     , N-2025       , -N+2026},
        {2*N-2000, 4*N-2005   , N*8 - 2010 , 16*N-2015    , 32*N-2020   , 2019*N      , -2020*N      , 2021*N},
        {1020-2*N, -2924+896*N, 1212+9808*N, -2736+98918*N, 1404-11068*N, -1523-8078*N, 2625-102119*N, -1327+1924*N},
    };

    return Matrix(matrixA_).getTransposedMatrix()*Matrix(matrixA_);
}

void Tasks::performTask9()
{
    m_A = getMatrixA1();
    m_printer->setFolderName(m_dirNameForTask9A1);
    performTask2(1);
    performTask3(1);
    performTask4(1);
    performTask5(1);
    performTask6(1);
    performTask7(1);

    m_A = getMatrixA2();
    m_printer->setFolderName(m_dirNameForTask9A2);
    performTask2(1);
    performTask3(1);
    performTask4(1);
    performTask5(1);
    performTask6(1);
    //performTask7(1);
}

void Tasks::performTask10()
{
    Matrix A2{getMatrixA2()};

    // Vectors b for matrix A2 and matrix with maximum conditional number
    Matrix b_A2{A2.getRowCount(), 1};
    Matrix b_maxCond{m_maxCondMatrix.getRowCount(), 1};

    // Let's say vector b for matrixes will look like b = {1,1,...}^T
    // Filling vector b for matrix A2 with 1
    for(size_t i{0}; i < b_A2.getRowCount(); ++i)
    {
        b_A2.setMatrixElement(i,0, 1);

    }

    // Filling vector b for matrix with the max conditional number with 1
    for(size_t i{0}; i < b_maxCond.getRowCount(); ++i)
    {
        b_maxCond.setMatrixElement(i,0, 1);

    }

    GaussColumnSelection gauss;

    // Getting vectors x for
    Matrix x_A2{gauss.solveSystem(A2, b_A2)};
    Matrix x_maxCond{gauss.solveSystem(m_maxCondMatrix, b_maxCond)};

    // Subtask 1 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    const double delta{1e-5};
    const size_t numberOfTests{10};
    m_printer->setFolderName(m_dirNameForTask10);
    m_printer->setFileName("task10_1.txt");
    for(size_t i{0}; i < numberOfTests; ++i)
    {
        // Getting the perturbation of the vector b of matrix A2
        for(size_t i{0}; i < b_A2.getRowCount(); ++i)
        {
            b_A2.setMatrixElement(i,0, b_A2.getMatrixElement(i,0) + delta);
        }

        // Getting the perturbation of the vector b of matrix with maximum conditional number
        for(size_t i{0}; i < b_maxCond.getRowCount(); ++i)
        {
            b_maxCond.setMatrixElement(i,0, b_maxCond.getMatrixElement(i,0) + delta);

        }

        double normA2{(gauss.solveSystem(A2, b_A2)+(-x_A2)).getNorm3()};
        double normMaxCond{(gauss.solveSystem(m_maxCondMatrix, b_maxCond)+(-x_maxCond)).getNorm3()};

        *m_printer->m_fout<<"\n\tRelative error for A2: "<<normA2/x_A2.getNorm3();
        *m_printer->m_fout<<"\tRelative error for matrix with maximum conditional number: "<<normMaxCond/x_maxCond.getNorm3();
    }
    /*
    // Subtask 2 /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Let's say vector b for matrixes will look like b = {1,1,...}^T
    // Filling vector b for matrix with the max conditional number with 1
    for(size_t i{0}; i < b_maxCond.getRowCount(); ++i)
    {
        b_maxCond.setMatrixElement(i,0, i);

    }

    Relaxation relaxation;
    const double W1{0.8};
    const double W2{1.0};
    const double W3{1.2};

//    std::vector<std::pair<size_t, double>> iterationsNormA2w1{};
//    std::vector<std::pair<size_t, double>> iterationsNormA2w2{};
//    std::vector<std::pair<size_t, double>> iterationsNormA2w3{};

    std::vector<std::pair<size_t, double>> iterationsNormMaxCondw1{};
    std::vector<std::pair<size_t, double>> iterationsNormMaxCondw2{};
    std::vector<std::pair<size_t, double>> iterationsNormMaxCondw3{};
    size_t iterations;

//    relaxation.solveSystem(A2, b_A2, W1, iterations, iterationsNormA2w1);
//    relaxation.solveSystem(A2, b_A2, W2, iterations, iterationsNormA2w2);
//    relaxation.solveSystem(A2, b_A2, W3, iterations, iterationsNormA2w3);

        relaxation.solveSystem(m_maxCondMatrix, b_maxCond, W1, iterations, iterationsNormMaxCondw1);
        relaxation.solveSystem(m_maxCondMatrix, b_maxCond, W2, iterations, iterationsNormMaxCondw2);
        relaxation.solveSystem(m_maxCondMatrix, b_maxCond, W3, iterations, iterationsNormMaxCondw3);

//    m_printer->setFileName("task10_2_A2_w1.txt");
//    for(size_t i{0}; i < iterationsNormA2w1.size(); ++i)
//    {
//        *m_printer->m_fout<<iterationsNormA2w1.at(i).first << " " << iterationsNormA2w1.at(i).second <<"\n";
//    }

//    m_printer->setFileName("task10_2_A2_w2.txt");
//    for(size_t i{0}; i < iterationsNormA2w2.size(); ++i)
//    {
//        *m_printer->m_fout<<iterationsNormA2w2.at(i).first << " " << iterationsNormA2w2.at(i).second <<"\n";
//    }

//    m_printer->setFileName("task10_2_A2_w3.txt");
//    for(size_t i{0}; i < iterationsNormA2w3.size(); ++i)
//    {
//        *m_printer->m_fout<<iterationsNormA2w3.at(i).first << " " << iterationsNormA2w3.at(i).second <<"\n";
//    }

    m_printer->setFileName("task10_2_maxCond_w1.txt");
    for(size_t i{0}; i < iterationsNormMaxCondw1.size(); ++i)
    {
        *m_printer->m_fout<<iterationsNormMaxCondw1.at(i).first << " " << iterationsNormMaxCondw1.at(i).second <<"\n";
    }

    m_printer->setFileName("task10_2_maxCond_w2.txt");
    for(size_t i{0}; i < iterationsNormMaxCondw1.size(); ++i)
    {
        *m_printer->m_fout<<iterationsNormMaxCondw2.at(i).first << " " << iterationsNormMaxCondw2.at(i).second <<"\n";
    }

    m_printer->setFileName("task10_2_maxCond_w3.txt");
    for(size_t i{0}; i < iterationsNormMaxCondw3.size(); ++i)
    {
        *m_printer->m_fout<<iterationsNormMaxCondw3.at(i).first << " " << iterationsNormMaxCondw3.at(i).second <<"\n";
    }
    */

}

