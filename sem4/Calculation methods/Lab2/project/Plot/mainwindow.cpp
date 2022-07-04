#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::makePlot()
{
    // Let's find some point that belong to the function plot in range [A, B]
    auto A{-6.0};
    auto B{6.0};

    double maxF{std::numeric_limits<double>::min()};
    double minF{std::numeric_limits<double>::max()};

    QLineSeries *func1Series = new QLineSeries();
    QLineSeries *func2Series = new QLineSeries();
    for(auto x = A; x <= B; x += 0.01)
    {
        auto a = std::pow(x, 9)+ M_PI;
        auto b = std::cos(std::log(x*x + 1));
        auto c = std::exp(x*x);
        double d = x * 2;

        double f1 = a * b / c;

        maxF = std::max(std::max(f1, maxF), d);
        minF = std::min(std::min(f1, minF), d);


        func1Series->append(x, f1);
        func2Series->append(x, d);
    }


    // Let's make the plot itself
    QChartView *m_chartView_ptr = new QChartView();
    m_chartView_ptr->chart()->addSeries(func1Series);
    m_chartView_ptr->chart()->addSeries(func2Series);

    QValueAxis *m_chartAxisX_ptr = new QValueAxis();
    m_chartAxisX_ptr->setRange(A, B);

    QValueAxis *m_chartAxisY_ptr = new QValueAxis();
    m_chartAxisY_ptr->setRange(minF, maxF);


    m_chartView_ptr->chart()->setAxisX(m_chartAxisX_ptr);
    m_chartView_ptr->chart()->setAxisY(m_chartAxisY_ptr);


    this->setCentralWidget(m_chartView_ptr);
}

MainWindow::~MainWindow()
{
    delete ui;
}



