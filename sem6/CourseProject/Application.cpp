#include "Application.h"

#include <iostream>

#include <QBarSeries>
#include <QBarSet>

Application::Application(QObject *parent) : QObject(parent)
{
    initializeCharts();
    initializeModel();
}

void Application::run()
{
    char answer;
    std::cout << "\nChoose option:\n1)continue\n2)finish\nyour answer: ";
    std::cin >> answer;

    if (answer == '1') {
        m_Model.liveTheDay();

        m_BarSetGood.remove(0, m_BarSetGood.count());
        m_BarSetDamaged.remove(0, m_BarSetDamaged.count());
        m_BarSetDestroyed.remove(0, m_BarSetDestroyed.count());
        m_BarSetUnderRepair.remove(0, m_BarSetUnderRepair.count());

        for (const auto& city : m_Model.m_Objects) {
            size_t good{};
            size_t damaged{};
            size_t destroyed{};
            size_t underRepair{};

            for (const auto& obj : city) {
                if (obj.m_State == LargeObjectState::GOOD) {
                    ++good;
                } else if (obj.m_State == LargeObjectState::DAMAGED) {
                    ++damaged;
                } else if (obj.m_State == LargeObjectState::DESTROYED) {
                    ++destroyed;
                } else if (obj.m_State == LargeObjectState::UNDER_REPAIR) {
                    ++underRepair;
                }
            }

            m_BarSetGood.append(good);
            m_BarSetDamaged.append(damaged);
            m_BarSetDestroyed.append(destroyed);
            m_BarSetUnderRepair.append(underRepair);
        }

        m_BarSeriesGood.append(&m_BarSetGood);
        m_BarSeriesDamaged.append(&m_BarSetDamaged);
        m_BarSeriesDestroyed.append(&m_BarSetDestroyed);
        m_BarSeriesUnderRepair.append(&m_BarSetUnderRepair);

        updateCharts();

    } else if (answer == '2') {
        emit finished();
        return;
    }

    for (size_t i {0}; i < m_BarSetGood.count(); ++i) {
        std::cout << "\t" << m_BarSetGood.at(i);
    }
    std::cout << "\n";

    for (size_t i {0}; i < m_BarSetDamaged.count(); ++i) {
        std::cout << "\t" << m_BarSetDamaged.at(i);
    }
    std::cout << "\n";

    for (size_t i {0}; i < m_BarSetDestroyed.count(); ++i) {
        std::cout << "\t" << m_BarSetDestroyed.at(i);
    }
    std::cout << "\n";

    for (size_t i {0}; i < m_BarSetUnderRepair.count(); ++i) {
        std::cout << "\t" << m_BarSetUnderRepair.at(i);
    }
    std::cout << "\n";

    std::cout << "\n\nEnter smth to continue ...";
    std::cin >> answer;

    QTimer::singleShot(1000, this, SLOT(run()));
}

void Application::initializeModel()
{
    std::cout << "\nEnter number of cities with parks: ";
    size_t numberOfCities{};
    std::cin >> numberOfCities;

    m_Model.m_Objects.resize(numberOfCities);

    for (size_t city{0}; city < numberOfCities; ++city) {
        std::cout << "\n\tEnter number of objects in city " << city << ": ";
        size_t numberOfobjectsInCity{};
        std::cin >> numberOfobjectsInCity;
        m_Model.m_Objects.at(city).resize(numberOfobjectsInCity);
    }
}

void Application::initializeCharts()
{
    m_ChartView.setRenderHint(QPainter::Antialiasing);
    m_ChartView.chart()->setAnimationDuration(1000);
    m_ChartView.chart()->setAnimationOptions(QChart::SeriesAnimations);
    m_ChartView.chart()->setTheme(QChart::ChartThemeLight);

    m_ChartView.chart()->addSeries(&m_BarSeriesGood);
    m_ChartView.chart()->addSeries(&m_BarSeriesDamaged);
    m_ChartView.chart()->addSeries(&m_BarSeriesDestroyed);
    m_ChartView.chart()->addSeries(&m_BarSeriesUnderRepair);

    m_MainWindow.move(10, 10);
    m_MainWindow.resize(800, 1000);
    m_MainWindow.setCentralWidget(&m_ChartView);
    m_MainWindow.show();
}

void Application::updateCharts()
{
    m_ChartView.chart()->removeSeries(&m_BarSeriesGood);
    m_ChartView.chart()->removeSeries(&m_BarSeriesDamaged);
    m_ChartView.chart()->removeSeries(&m_BarSeriesDestroyed);
    m_ChartView.chart()->removeSeries(&m_BarSeriesUnderRepair);
    m_ChartView.chart()->addSeries(&m_BarSeriesGood);
    m_ChartView.chart()->addSeries(&m_BarSeriesDamaged);
    m_ChartView.chart()->addSeries(&m_BarSeriesDestroyed);
    m_ChartView.chart()->addSeries(&m_BarSeriesUnderRepair);
    m_ChartView.chart()->createDefaultAxes();
}
