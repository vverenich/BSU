#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void linearCongruentMethodGeneration(QVector<double>& x, QVector<double>& y, int M, int n,
                                     unsigned a, unsigned c, unsigned beta)
{
    double* b = new double[n];

    b[0] = beta % M;
    x[0] = b[0];
    for(int i = 1; i < n; ++i)
    {
        b[i] = (double)((a * (int)b[i-1] + c) % M);
        if(i != n - 1){
            x[i] = b[i];
        }

        y[i-1] = b[i];
    }

    delete[] b;
}

void macLarenMarsagliaMethodGeneration(QVector<double>& firstSequenceX, QVector<double>& firstSequenceY,
                                       QVector<double>& finalSequenceX, QVector<double>& finalSequenceY,
                                       int M, int n, int K)
{
    M = 30000;
    unsigned a = 458753;
    unsigned c = 19;
    unsigned long beta{ 458752 };

    /*
    unsigned a = 6055;
    unsigned c = 19;
    unsigned long beta{ 6054 };
    */
    linearCongruentMethodGeneration(firstSequenceX,firstSequenceY, M, n, a, c, beta);

    QVector<double> table(K);
    for(int i = 0; i < K; ++i)
    {
        table[i] = firstSequenceX[i];
    }

    for(int i = 0; i < n-1; ++i)
    {
        double randomNumber = firstSequenceX[i];
        int index = (int)randomNumber % K;
        double result = table[index];
        table[index] = randomNumber;

        finalSequenceX[i] = result;
        if(i != 0)
        {
            finalSequenceY[i-1] = result;
        }
    }

    finalSequenceY[n-2] = finalSequenceX[n-2];

}

void MainWindow::makePlots(/*const QVector<double>& x, const QVector<double>& y*/)
{
    unsigned M;
    unsigned a = 12109;
    unsigned c = 19;
    unsigned long beta{ 12108 };

    //Generation of the first sample by the linear congruent method.
    M = 72;
    unsigned n1 { 200 };
    QVector<double> x1(n1-1), y1(n1-1);
    linearCongruentMethodGeneration(x1,y1, M, n1, a, c, beta);

    //Generation of the second sample by the linear congruent method.
    M = 1009 * (2*2*2*2) * 18;
    unsigned n2 {M};
    QVector<double> x2(n2-1), y2(n2-1);
    linearCongruentMethodGeneration(x2,y2, M, n2, a, c, beta);

    //Generation of the sample using MacLaren-Marsaglia Method
    //M = 30000;
    unsigned n3 = 32769;
    unsigned K = 128;
    // sample of the first generator
    QVector<double> x3(n3-1), y3(n3-1);
    // sample of the final generator
    QVector<double> x4(n3-1), y4(n3-1);
    macLarenMarsagliaMethodGeneration(x3, y3, x4, y4, M, n3, K);


    ///////////////////////////////////////////////////////////////////
    // create scatter plot for the Liniar Congruentual Method
    // with M < 103 and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setData(x1, y1);

    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, n1);
    ui->customPlot->yAxis->setRange(0, n1);
    ui->customPlot->replot();

    ///////////////////////////////////////////////////////////////////

    // create scatter plot for the Liniar Congruentual Method
    // with big M and assign data to it:
    ui->customPlot2->addGraph();
    ui->customPlot2->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot2->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot2->graph(0)->setData(x2, y2);

    // give the axes some labels:
    ui->customPlot2->xAxis->setLabel("x");
    ui->customPlot2->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->customPlot2->xAxis->setRange(0, n2);
    ui->customPlot2->yAxis->setRange(0, n2);
    ui->customPlot2->replot();

    ///////////////////////////////////////////////////////////////////

    // create scatter plot for the for the Liniar Congruentual Method to generate numbers for
    // MacLaren Marsaglia Method
    ui->customPlot3->addGraph();
    ui->customPlot3->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot3->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot3->graph(0)->setData(x3, y3);

    // give the axes some labels:
    ui->customPlot3->xAxis->setLabel("x");
    ui->customPlot3->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->customPlot3->xAxis->setRange(0, n3);
    ui->customPlot3->yAxis->setRange(0, n3);
    ui->customPlot3->replot();

    ///////////////////////////////////////////////////////////////////

    // create scatter plot for the for the MacLaren Marsaglia Method
    ui->customPlot4->addGraph();
    ui->customPlot4->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot4->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot4->graph(0)->setData(x4, y4);

    // give the axes some labels:
    ui->customPlot4->xAxis->setLabel("x");
    ui->customPlot4->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->customPlot4->xAxis->setRange(0, n3);
    ui->customPlot4->yAxis->setRange(0, n3);
    ui->customPlot4->replot();

    ///////////////////////////////////////////////////////////////////
}
