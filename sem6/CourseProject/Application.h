#ifndef APPLICATION_H
#define APPLICATION_H

#include <thread>
#include <memory>

#include <QDebug>
#include <QtCharts>
#include <QtCore>

#include "Model.h"

class Application : public QObject {
    Q_OBJECT

  public slots:
    void run();

  signals:
    void finished();

  public:
    Application() = delete;
    Application(QObject* parent = nullptr);

  private:
    void initializeModel();
    void initializeCharts();

    void updateCharts();

  private:
    Model m_Model{};

    QMainWindow m_MainWindow{};
    QChartView  m_ChartView{};

    QBarSeries m_BarSeriesGood{};
    QBarSeries m_BarSeriesDamaged{};
    QBarSeries m_BarSeriesDestroyed{};
    QBarSeries m_BarSeriesUnderRepair{};

    QBarSet m_BarSetGood{"GOOD"};
    QBarSet m_BarSetDamaged{"DAMAGED"};
    QBarSet m_BarSetDestroyed{"DESTROYED"};
    QBarSet m_BarSetUnderRepair{"UNDER_REPAIR"};
};

#endif // APPLICATION_H
