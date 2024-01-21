#include <memory>
#include <iomanip>

#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QtCharts>
#include <QChart>

std::mt19937 mt{ static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()
        ) };

std::unique_ptr<QMainWindow> chartWindow1{nullptr};
std::unique_ptr<QLineSeries> chartSeries1{nullptr};
std::unique_ptr<QChartView> chartView1{nullptr};
std::unique_ptr<QValueAxis> chartAxisX1{nullptr};
std::unique_ptr<QValueAxis> chartAxisY1{nullptr};

std::unique_ptr<QMainWindow> chartWindow2{nullptr};
std::unique_ptr<QLineSeries> chartSeries2{nullptr};
std::unique_ptr<QChartView> chartView2{nullptr};
std::unique_ptr<QValueAxis> chartAxisX2{nullptr};
std::unique_ptr<QValueAxis> chartAxisY2{nullptr};

std::unique_ptr<QMainWindow> chartWindow3{nullptr};
std::unique_ptr<QLineSeries> chartSeries3{nullptr};
std::unique_ptr<QChartView> chartView3{nullptr};
std::unique_ptr<QValueAxis> chartAxisX3{nullptr};
std::unique_ptr<QValueAxis> chartAxisY3{nullptr};

void makePlot(std::unique_ptr<QMainWindow>& window, std::unique_ptr<QLineSeries>& lineSeries,
              std::unique_ptr<QChartView>& view, std::unique_ptr<QValueAxis>& axisX,
              std::unique_ptr<QValueAxis>& axisY, const std::vector<double>& points,
              const QString& name)
{
    window = std::make_unique<QMainWindow>();
    window->resize(800, 600);
    double minElement{std::numeric_limits<double>::max()};
    double maxElement{std::numeric_limits<double>::min()};
    double currentElement{};

    lineSeries = std::make_unique<QLineSeries>();
    lineSeries->setName(name);

    for (size_t i{0}; i < points.size(); ++i) {
        currentElement = points.at(i);
        minElement = std::min(minElement, currentElement);
        maxElement = std::max(maxElement, currentElement);

        lineSeries->append(i, currentElement);
    }

    view = std::make_unique<QChartView>();
    view->chart()->addSeries(lineSeries.get());
    view->setRenderHint(QPainter::Antialiasing);

    axisX = std::make_unique<QValueAxis>();
    axisX->setRange(0, points.size());
    axisY = std::make_unique<QValueAxis>();
    axisY->setRange(minElement, maxElement);

    view->chart()->setAxisX(axisX.get());
    view->chart()->setAxisY(axisY.get());

    window->setCentralWidget(view.get());
    window->show();
}

void calculatePI(const double D, const double l, const double N, std::vector<double>& vector)
{
    size_t n = 0;

    std::uniform_real_distribution<> corner{-M_PI, M_PI};
    std::uniform_real_distribution<> start_position{0, D};

    vector.resize(N);
    for (size_t i{0}; i < N ; ++i) {
        auto end_position = std::cos(corner(mt)) * l + start_position(mt);
        if (end_position <= 0 || end_position >= D) {
            ++n;
        }

        //vector.at(i) = static_cast<double>(n) / N;
        vector.at(i) = std::abs(( 2 * l * N / D / n ));
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const double c_D = 4;
    //const double c_l = 2;
    const size_t c_N = 1200000;
    const size_t c_FirstSkipped{1000000};

    // l = 1
    std::vector<double> series1{};
    calculatePI(c_D, 1.0, c_N, series1);
    std::vector<double> series1_n(c_N - c_FirstSkipped);
    std::copy(series1.begin() + c_FirstSkipped, series1.end(), series1_n.begin());
    makePlot(chartWindow1, chartSeries1, chartView1, chartAxisX1, chartAxisY1, series1_n, "1.0");
    // l = 2
    std::vector<double> series2{};
    calculatePI(c_D, 2.0, c_N, series2);
    std::vector<double> series2_n(c_N - c_FirstSkipped);
    std::copy(series2.begin() + c_FirstSkipped, series2.end(), series2_n.begin());
    makePlot(chartWindow2, chartSeries2, chartView2, chartAxisX2, chartAxisY2, series2_n, "2.0");
    // l = 3
    std::vector<double> series3{};
    calculatePI(c_D, 3.0, c_N, series3);
    std::vector<double> series3_n(c_N - c_FirstSkipped);
    std::copy(series3.begin() + c_FirstSkipped, series3.end(), series3_n.begin());
    makePlot(chartWindow3, chartSeries3, chartView3, chartAxisX3, chartAxisY3, series3_n, "3.0");

    return a.exec();
}
