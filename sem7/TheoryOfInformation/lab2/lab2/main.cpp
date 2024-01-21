#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <map>
#include <cmath>
#include <iostream>

// Functions needed to perform task
double factorial(int i)
{
    if (i == 0) return 1;
    else return i * factorial(i - 1);
}

double getEntropy(const double p)
{
    return -p * std::log(p)/std::log(2.0) - (1 - p) * std::log(1 - p)/std::log(2.0);
}

double getBottomLimitOfETypeSeq(const double H, const double e, const double n)
{
    return std::pow(2.0, -1.0 * double(double(n) * (H + e)));
}

double getTopLimitOfETypeSeq(const double H, const double e, const double n)
{
    return std::pow(2, -1.0 * n * (H - e));
}

size_t getNumberOfAllETypeSeq(const double e, const double p, const double n)
{
    double sum{0.0};
    for (int i = 1; i < n + 1; i++)
    {
        double e1 = e / std::log((1 - p) / p)/std::log(2.0);
        double currentE = std::abs(i / double(n) - p);
        if (currentE <= e1)
        {
            double factN = (factorial(n) / (factorial(i) * factorial(n - i)));
            sum += factN;
        }
    }

    return sum;
}

double getSumOfProbsOfAllETypeSeq(const double e, const double p, const size_t n)
{
    double totalP{ 0.0 };
    for (size_t i = 1; i < n + 1; i++)
    {
        double e1 = e / std::log((1 - p) / p)/std::log(2.0);
        double currentE = std::abs(i / double(n) - p);
        if (currentE <= e1)
        {
            double factN = (factorial(n) / (factorial(i) * factorial(n - i)));
            totalP += factN * (pow(p, i)) * (pow(1.0 - p, n - i));
        }
    }

    return totalP;
}

double getFractionOfAllExistingSeq(const size_t n, double sum)
{
    return sum / (std::pow(2, n));
}

// Tasks
void executeTask1(const double p)
{
    std::cout << "================================= TASK1 =====================================================\n";
    auto H = getEntropy(p);
    std::cout << "Энтропия H(X) двоичной случайной величины X (вероятность выпадения чёрного шарика): " << H << "\n";
    std::cout << "=============================================================================================\n";
}

void executeTask2(const double H, const double e, const double n, const double p)
{
    std::cout << "================================= TASK2 =====================================================\n";
    double minLimitCount = getBottomLimitOfETypeSeq(H, e, n);
    double maxLimitCount = getTopLimitOfETypeSeq(H, e, n);
    std::cout << "Нижняя граница для вероятности появления e-типичной последовательности: " << minLimitCount << "\n";
    std::cout << "Верхняя граница для вероятности появления e-типичной последовательности: " << maxLimitCount << "\n";
    std::cout << "Число всех e-типичных последовательностей: " << getNumberOfAllETypeSeq(e, p, n) << "\n";
    std::cout << "=============================================================================================\n";
}

void executeTask3(const double e, const double p,const double n)
{
    std::cout << "================================= TASK3 =====================================================\n";
    auto sum = getNumberOfAllETypeSeq(e, p, n);
    std::cout << "Число всех e-типичных последовательностей: " << sum << "\n";
    std::cout << "Доля всех e-типичных последовательностей относительно всех возможных последовательностей: "
              << getFractionOfAllExistingSeq(n, sum) << "\n";
    std::cout << "Сумма вероятностей всех e-типичных последовательностей: " << getSumOfProbsOfAllETypeSeq(e, p, n) << "\n";
    std::cout << "=============================================================================================\n";
}

void executeTask4(const std::vector<uint32_t>& arrayN, const double p, const double e)
{
    std::cout << "================================= TASK4 =====================================================\n";
    for (const auto& i : arrayN) {
        std::cout << "N is equal to " << i << "\n";
        executeTask2(getEntropy(p), e, i, p);
        executeTask3(e, p, i);
    }
    std::cout << "=============================================================================================\n";
}

void executeTask5(const double p, const double e)
{
    std::cout << "================================= TASK5 =====================================================\n";
    for (size_t n{0}; n < 1000; ++n) {
        if (getSumOfProbsOfAllETypeSeq(e, p, n) > 1 - e) {
            std::cout << "n0 = " << n << '\n';

            n = 1001;
        }
    }
    std::cout << "=============================================================================================\n";
}

int main()
{
    // Parameters
    const double p{1.0 / 3.0};
    const double e{0.138};
    const std::vector<uint32_t> c_VectorN{10, 100, 500, 1000, 2000};

    executeTask1(p);
    executeTask2(getEntropy(p), e, c_VectorN.at(0), p);
    executeTask3(e, p, c_VectorN.at(0));
    executeTask4(c_VectorN, p, e);
    executeTask5(p, e);

    return 0;
}
