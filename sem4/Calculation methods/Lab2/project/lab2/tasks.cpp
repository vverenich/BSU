#include "tasks.h"

Tasks::Tasks()
{

}

std::vector<std::vector<std::complex<double>>> matrixVectorA1{{ 1,-2, 1, 0,-1, 1,-2, 2, 0,-2},
                                                              { 0, 2, 0, 0, 2, 1,-1,-1,-1,-2},
                                                              { 0, 1, 0,-1, 1,-1, 0,-1, 1,-1},
                                                              {-2,-1, 2,-1, 0, 0, 0, 0, 1, 0},
                                                              { 1,-2, 0, 1, 0,-2,-1, 0, 2, 2},
                                                              {-2,-2, 0,-2, 0, 1, 1,-2, 1, 1},
                                                              {-1,-2,-1,-1,-2,-1,-2, 1,-1, 2},
                                                              {-2, 1, 2,-2, 0, 2, 1,-1,-2, 2},
                                                              { 0, 1, 0, 1, 1,-2, 2, 0, 1, 1},
                                                              { 0, 0, 2,-1,-1, 0,-2, 2,-1,-1}};


std::vector<std::vector<std::complex<double>>> matrixVectorA2{{-1, 1,-1, 0,-1, 0,-1, 1, 1,-1, 0,-1,-1, 1, 0, 0, 1, 1, 1, 1},
                                                              {-1, 0,-1, 1,-1, 0, 0, 0, 0,-1, 0, 0,-1, 1, 0,-1, 1,-1,-1, 0},
                                                              { 1, 0,-1, 1, 0, 1,-1,-1,-1, 0,-1,-1, 1,-1, 1, 1,-1, 1,-1, 0},
                                                              {-1, 1, 0, 0,-1, 0, 0,-1, 0,-1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 0},
                                                              { 1, 0,-1, 0, 0,-1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0,-1, 0, 0, 1},
                                                              { 0, 0, 0, 0,-1, 1, 1, 0, 0, 1, 1, 0,-1, 0, 1, 1, 0, 1, 0, 0},
                                                              {-1, 0, 1, 1, 1,-1,-1, 0,-1, 1,-1,-1,-1, 0,-1, 0, 0, 0,-1, 1},
                                                              { 0, 0,-1,-1, 0, 1, 1, 1, 1,-1, 0, 0,-1, 1, 1, 1, 1, 0, 0,-1},
                                                              { 0, 0, 1, 1, 0, 1, 1, 0, 1,-1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
                                                              { 0,-1, 0, 0, 1, 0,-1, 0,-1, 0,-1, 0,-1, 0, 1,-1, 0, 0, 1, 1},
                                                              { 1,-1, 1,-1,-1,-1, 1, 0,-1, 0, 1, 1,-1, 0, 1, 1, 1, 0, 0, 0},
                                                              { 0, 1, 0, 0,-1, 0, 1, 0, 1, 0, 0, 1, 1,-1,-1, 0,-1, 1, 1,-1},
                                                              {-1,-1,-1,-1, 0, 1,-1, 0, 0,-1, 0, 0, 0, 1, 1, 0, 0, 0,-1, 0},
                                                              {-1, 0, 1, 0,-1, 0, 0, 1,-1, 1, 1,-1, 1, 1, 1,-1, 1,-1,-1, 0},
                                                              { 1,-1, 0,-1,-1, 0,-1,-1, 0, 0, 1, 0, 1, 1,-1, 1, 0, 0,-1, 0},
                                                              {-1,-1, 1, 0,-1, 1, 1,-1, 1, 0, 0,-1, 1,-1,-1, 0, 0, 1, 1, 1},
                                                              { 0, 0,-1, 0, 0, 0, 0,-1, 1, 1, 0,-1, 1,-1, 0, 0, 0,-1,-1, 1},
                                                              {-1, 0,-1,-1,-1, 1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1, 0,-1, 0,-1},
                                                              {-1, 0, 1, 0, 0, 0, 0,-1, 1,-1, 1,-1, 0,-1,-1, 1, 0, 1, 0, 0},
                                                              { 0,-1,-1, 1,-1, 1,-1,-1,-1, 1, 1,-1, 0,-1,-1, 0, 1, 0,-1,-1}};

//    Task 1
//    Write a program that finds the maximum modulo eigenvalue (a pair of maximum modulo
//    eigenvalues) and the corresponding eigenvector(s) of matrix 𝐴 with maximum
//    possible precision (within normal double numbers). Apply the program to the following inputs. In the report
//    describe in detail the method of determining the case and the criterion for stopping iterations. Conduct a Pilot Study
//    the speed of your program depending on the dimension of the matrix, using a matrix with random
//    numbers. Plot the running time versus dimension graph. Compute Asymptotic Complexity
//    the algorithm you have implemented.


std::pair<std::complex<double>, std::complex<double>> getTwoMaxModuloEigenvalues(const Matrix &matrix, std::vector<Matrix> &xk)
{
    // Creating the matrix itself
    Matrix A{std::move(matrix)};

    // This container will contain the next vectors:
    // x_k = A^k * x0, x_k+1 = A^(k+1) * x0, x_k+2 = A^(k+2) * x0
    //std::vector<Matrix> xk(3);
    xk.resize(3);

    // At the beginning vector x_k is filled with ones
    xk[0] = Matrix{A.getRowCount(),1};
    for (size_t i{0}; i < xk[0].getRowCount(); ++i)
    {
        for (size_t j{0}; j < xk[0].getColumnCount(); ++j)
        {
            xk[0].setMatrixElement(i, j, i);
        }
    }

    xk[1] = Matrix{A * xk[0]};
    xk[2] = Matrix{A * xk[1]};

    // The matrix that has two vectors(x_k, x_k+1) above as the columns
    Matrix A1_{xk[0].getRowCount(), static_cast<unsigned>(xk.size() - 1)};

    // Vector of coefficients
    Matrix c{static_cast<unsigned>(xk.size()) - 1, 1};

    // Two dominant eigenvalues(can be the same)
    std::complex<double> lambda1{0};
    std::complex<double> lambda2{0};

    std::complex<double> discriminant{};

    const double EPSILON{1e-3};
    size_t i{0};

    while( (A * xk[2] + (-lambda1) * xk[2]).getNorm3() > EPSILON  && i < 1000)
    {
        ++i;

        xk[0] = static_cast<std::complex<double>>(1) / xk[2].getNorm3() *xk[2];
        xk[1] = A * xk[0];
        xk[2] = A * xk[1];

        // So we've got x_k, x_k+1, x_k+2.
        // Update A_ = [x_k | x_k+1 | x_k+2]
        for(size_t j{0}; j < A1_.getColumnCount(); ++j)
        {
            for(size_t i{0}; i < A1_.getRowCount(); ++i)
            {
                A1_.setMatrixElement(i, j, xk[j].getMatrixElement(i,0));
            }
        }

        // In order to find the eigenvalues we have to solve the following equation:
        // t^2 + c1 * t + c0 = 0 .
        // In order to find c1 and c0 we have to solve the following equation:
        // A_^T * A_ * c = A_^T * -x_k ,
        // where c = (c0, c1)^T
        // Let's say A1 = A_^T * A_
        //           b  = A_^T * -x_k
        Matrix transposedA1{A1_.getTransposedMatrix()};
        Matrix A1{transposedA1 * A1_};
        Matrix b1{transposedA1 * (static_cast<std::complex<double>>(-1) * xk.back())};


        Gauss gauss;
        c = gauss.solveSystem(A1, b1);

        // Finally we've find c vector and we can solve the equation t^2 + c1 * t + c0 = 0 .
        // Let's find the discriminant
        discriminant = c.getMatrixElement(1,0) * c.getMatrixElement(1,0) - static_cast<std::complex<double>>(4) * c.getMatrixElement(0,0);


        // Finding the eigenvalues
        std::complex<double> x1 = (-c.getMatrixElement(1,0) + sqrt(discriminant)) / static_cast<std::complex<double>>(2);
        std::complex<double> x2 = (-c.getMatrixElement(1,0) - sqrt(discriminant)) / static_cast<std::complex<double>>(2);

        // The case when eigwnvalues are complex
        if(real(discriminant) < 0)
        {
            lambda1 = x1;
            xk[2] = lambda1 * xk[1] + xk[2];
            continue;
        }

        // The case when eigenvalues have different signs and they are not complex
        else if( -EPSILON <= std::abs(x1 + x2) && std::abs(x1 + x2) <= EPSILON)
        {
            lambda1 = x1;
            lambda2 = x2;
        }

        // The case when eigenvalues are equal
        else if( -EPSILON <= std::abs(x1 - x2) && std::abs(x1 - x2) <= EPSILON)
        {
            lambda1 = x1;
            lambda2 = x2;
        }
        else {
            // Update lambda
            lambda1 = std::max(x1, x2, [](std::complex<double> a, std::complex<double> b)
                                              {
                                                  return std::abs(a) < std::abs(b);
                                              });
        }
    }

    if(!(-EPSILON <= imag(lambda1) && imag(lambda1) <= EPSILON))
    {
        lambda2 = lambda1 - std::complex<double>(0, 2 * imag(lambda1));
    }

    return std::make_pair(lambda1, lambda2);
}

void determineTheCase(const std::complex<double> &lambda1, const std::complex<double> &lambda2)
{
    // Determining the case.
    const double EPSILON{1e-3};

    // Case 1:
    if(!(-EPSILON <= imag(lambda1) && imag(lambda1) <= EPSILON))
    {
        std::cout << "\nThis is the case where: |lambda_1| = |lambda_2| > |lambda3|... and lambda_1 is the complex number.";
    }

    // Case 2:
    else if(-EPSILON <= std::abs(lambda1 - lambda2) && std::abs(lambda1 - lambda2) <= EPSILON)
    {
        std::cout << "\nThis is the case where: |lambda_1| = |lambda_2| = |lambda_3| = ... and lambda_1 = lambda_2";
    }

    // Case 3:
    else if(-EPSILON <= std::abs(lambda1 + lambda2) && std::abs(lambda1 + lambda2) <= EPSILON)
    {
        std::cout << "\nThis is the case where: |lambda_1| = |lambda_2| > |lambda_3| ... and lambda_1 = -lambda_2";
    }

    // Case 4:
    else
    {
        std::cout << "\nThis is the case where: |lambda_1| > |lambda_2| >= |lambda_3| ...";
    }
}

std::pair<Matrix, Matrix> findEigenvectors(const std::pair<std::complex<double>, std::complex<double>> &l, const Matrix &u,const Matrix &Au)
{

    Matrix v1{u.getRowCount(), 1};
    Matrix v2{u.getRowCount(), 1};

    const double EPSILON{1e-3};
    // Complex numbers as the eigenvalues
    if(-EPSILON <= imag(l.first * l.second) && imag(l.first * l.second) <= EPSILON)
    {
        v1 = Au + -(l.second * u);
        v2 = Au + -(l.first * u);
    }
    //
    else if (-EPSILON <= std::abs(l.first + l.second) && std::abs(l.first + l.second) <= EPSILON) //собственные значения кратные либо различны по значению
    {
        v1 = Au + -(-l.first * u);
        v1 = Au + -(l.first * u);
    }

    else
    {
        v1 = Au;
    }

    return std::make_pair(v1, v2);
}

void Tasks::performTask1()
{
    std::cout << "\n\n";
    std::cout << "\n--------------------------------------------";
    std::cout << "\n                  TASK 1                    ";
    std::cout << "\n--------------------------------------------";

    std::vector<std::vector<std::complex<double>>> matrixVector{{1, 2, 0},
                                                                {-2, 1, 2},
                                                                {1, 3, 1}};


    // The first matrix from task
    std::cout << "\nFirst matrix.\n";
    Matrix A1{matrixVectorA1};

    std::vector<Matrix> xk1{};

    // Getting eignvalues
    auto eigenvalues{getTwoMaxModuloEigenvalues(A1, xk1)};
    auto lambda1 = eigenvalues.first;
    auto lambda2 = eigenvalues.second;

    // Determining the case
    determineTheCase(lambda1, lambda2);

    // Getting the eigenvectors
    auto vectors{findEigenvectors(eigenvalues, xk1[0], xk1[1])};

    std::cout << "\n";
    std::cout << "\nThe eigenvalue:\n";
    std::cout << std::setprecision(8)<<lambda1;
    std::cout << "\n";
    std::cout << "\nThe eigenvector:\n";
    std::cout << std::setprecision(8)<<vectors.first;

    if(!(std::abs(lambda1) > std::abs(lambda2) || lambda1 == lambda2))
    {
        std::cout << "\n";
        std::cout << "\nThe eigenvalue:";
        std::cout << std::setprecision(8)<<lambda2;
        std::cout << "\n";
        std::cout << "\nThe eigenvector:";
        std::cout << std::setprecision(8)<<vectors.second;
    }

    // The second one
    std::cout << "\nSecond matrix.\n";
    Matrix A2{matrixVectorA2};

    std::vector<Matrix> xk2{};

    // Getting eignvalues
    eigenvalues = getTwoMaxModuloEigenvalues(A2, xk2);
    lambda1 = eigenvalues.first;
    lambda2 = eigenvalues.second;

    // Determining the case
    determineTheCase(lambda1, lambda2);

    // Getting the eigenvectors
    vectors = findEigenvectors(eigenvalues, xk2[0], xk2[1]);

    std::cout << "\n";
    std::cout << "\nThe eigenvalue:\n";
    std::cout << std::setprecision(8)<<lambda1;
    std::cout << "\n";
    std::cout << "\nThe eigenvector:\n";
    std::cout << std::setprecision(8)<<vectors.first;

    if(!(std::abs(lambda1) > std::abs(lambda2) || lambda1 == lambda2))
    {
        std::cout << "\n";
        std::cout << "\nThe eigenvalue:";
        std::cout << std::setprecision(8)<<lambda2;
        std::cout << "\n";
        std::cout << "\nThe eigenvector:";
        std::cout << std::setprecision(8)<<vectors.second;
    }

    std::cout << "\n\nCalculating of max modulo eigenvalues in random matrixes ...";

    std::ofstream fout("timeTask1.txt");

    const size_t NUMBER_OF_RANDOM_MATRIXES{30};
    for(size_t i{2}; i <= NUMBER_OF_RANDOM_MATRIXES; ++i)
    {
        // Calculating eigenvalues
        m_timer.reset();

        Matrix A{Matrix::getRandomMatrix(i, i)};
        std::vector<Matrix> xk{};
        // Getting eignvalues
        auto eigenvalues{getTwoMaxModuloEigenvalues(A, xk)};
        // Getting the eigenvectors
        auto vectors{findEigenvectors(eigenvalues, xk[0], xk[1])};

        auto timeInterval{m_timer.elapsed()};

        // Printing eigenvalues of matrix A nad eigenvalues
        fout << timeInterval <<"\n";
    }

}

//    Task 2
//    Write a program that implements the 𝑄𝑅-algorithm for finding all values of the indicators 𝐴 with the maximum possible
//    tomorrow. Apply the program to the matrices from the first task. Conducted experimental study of the speed
//    the work of your site depending on the dimension of the matrix program, using a matrix with random numbers for tests.
//    Construct a graph of the dependence of the running time on the dimension. Compute Asymptotic Useful Use
//    algorithm
void Tasks::performTask2()
{
    std::cout << "\n\n";
    std::cout << "\n--------------------------------------------";
    std::cout << "\n                  TASK 2                    ";
    std::cout << "\n--------------------------------------------";

    // Creating the matrixes
    Matrix A1{matrixVectorA1};
    Matrix A2{matrixVectorA2};

    // Transformation to Hessenberg form
    A1.toHessenbergForm();
    A2.toHessenbergForm();

    // Printing results for the first matrix
    std::cout << "\nEigenvalues for the first matrix in task:";
    auto eigenvaluesA1 = A1.getEigenvaluesQRalgorithm();

    for(const auto &i: eigenvaluesA1)
    {
        std::cout <<"\n"<< i;
    }

    std::cout << "\n";

    // Printing results for the second matrix
    std::cout << "\nEigenvalues for the second matrix in task:";
    auto eigenvaluesA2 = A2.getEigenvaluesQRalgorithm();

    for(const auto &i: eigenvaluesA2)
    {
        std::cout <<"\n"<< i;
    }

    std::cout << "\n\nCalculating of eigenvalues in random matrixes ...";

    std::ofstream fout("timeTask2.txt");

    const size_t NUMBER_OF_RANDOM_MATRIXES{20};
    for(size_t i{2}; i <= NUMBER_OF_RANDOM_MATRIXES; ++i)
    {
        // Calculating eigenvalues
        m_timer.reset();

        Matrix A{Matrix::getRandomMatrix(i, i)};
        A.toHessenbergForm();
        auto eigenValues{A.getEigenvaluesQRalgorithm()};

        auto timeInterval{m_timer.elapsed()};

        // Printing eigenvalues of matrix A nad eigenvalues
        fout << timeInterval <<"\n";
    }
}

//    Task 3
//    Given a nonlinear equation:
//
//    (x^9 + pi) * cos(ln(x^2 + 1)) / e^(x^2) − x / 2022 = 0.
//
//    Separate all its roots. Justify (it is not necessary to prove strictly) the uniqueness
//    of each root on the segment, the absence other roots. Using the bisection method, narrow
//    the segments of separation of the roots to a size of no more than 10^(−4). Newton's method
//    to find everything roots as accurately as possible. Include the number of iterations of
//    both methods in the report

void narrowSegmentBisectionMethod(double &a, double &b, std::function<double(double)> f)
{
    const double EPSILON{1e-5};
    size_t count{0};
    while(std::abs(b - a) > 2 * EPSILON)
    {
        double x = (a + b) / 2;
        if(f(x) * f(a) < 0)
        {
            b = x;
        }
        else
        {
            a = x;
        }
        ++count;
    }

    std::cout << "\nNumber of iterations in Bisection method: " << count;
}

double solveEquationNewtonMethod(double x0, std::function<double(double)> F, std::function<double(double)> f)
{
    const double EPSILON{1e-8};
    double xPrevious{x0-1};
    double xCurrent{x0};
    size_t count{0};
    while(std::abs(xPrevious - xCurrent) >= EPSILON)
    {
        xPrevious = xCurrent;
        xCurrent = xCurrent - F(xCurrent) / f(xCurrent);
        ++count;
    }

    std::cout << "\nNumber of iterations in Newton method: " << count;

    return xCurrent;
}

// The function from the task
double F(double x)
{
    return (std::pow(x, 9) + M_PI) * std::cos(std::log(x*x + 1)) / std::exp(x*x) - x / 2022.0;
}

// The derivative of the function from the task
double f(double x)
{
    return -(2 * std::exp(-x*x) * (std::pow(x, 9) + M_PI) * x * std::sin(std::log(x*x + 1))
            / (x*x + 1)) - 2 * std::exp(-x*x) * (std::pow(x, 9) + M_PI) * x
            * std::cos(std::log(x*x +1)) + 9 * std::exp(-x*x) * std::pow(x, 8)
            * cos (std::log(x*x + 1)) - 1 / 2022;
}

void Tasks::performTask3()
{
    std::cout << "\n\n";
    std::cout << "\n--------------------------------------------";
    std::cout << "\n                  TASK 3                    ";
    std::cout << "\n--------------------------------------------";

    double a, b;

    // 1st solution x1 - [-3.0; -1.5]
    std::cout << "\n\nCalculating x1...";
    a = -3.0;
    b = -1.5;
    narrowSegmentBisectionMethod(a, b, F);
    std::cout << "\nThe segment after Bisection method: [" << std::setprecision(8) << a << ", " << b << "]";
    double x1 = solveEquationNewtonMethod(b, F, f);
    std::cout << "\nThe solution: "<< std::setprecision(12) << x1;
    std::cout << "\nCalculating of x1 finished.";

    // 2nd solution x2 - [-1.5; 0]
    std::cout << "\n\nCalculating x2...";
    a = -1.5;
    b = 0;
    narrowSegmentBisectionMethod(a, b, F);
    std::cout << "\nThe segment after Bisection method: [" << std::setprecision(8) << a << ", " << b << "]";
    double x2 = solveEquationNewtonMethod(b, F, f);
    std::cout << "\nThe solution: "<< std::setprecision(12) << x2;
    std::cout << "\nCalculating of x2 finished.";

    // 3rd solution x3 - [1.5; 2.5]
    std::cout << "\n\nCalculating x3...";
    a = 1.5;
    b = 2.5;
    narrowSegmentBisectionMethod(a, b, F);
    std::cout << "\nThe segment after Bisection method: [" << std::setprecision(8) << a << ", " << b << "]";
    double x3 = solveEquationNewtonMethod(b, F, f);
    std::cout << "\nThe solution: "<< std::setprecision(12) << x3;
    std::cout << "\nCalculating of x3 finished.";

    std::cout << "\n\n";
}

