#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "letter.h"
#include <QDoubleSpinBox>
//#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
     ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();


    void on_xScaleSpinBox_valueChanged(double arg1);

    void on_yScaleSpinBox_valueChanged(double arg1);

    void on_zScaleSpinBox_valueChanged(double arg1);


    void on_xTransferSpinBox_valueChanged(double arg1);

    void on_yTransferSpinBox_valueChanged(double arg1);

    void on_zTransferSpinBox_valueChanged(double arg1);

    void on_xRotationSpinBox_valueChanged(int arg1);

    void on_yRotationSpinBox_valueChanged(int arg1);

    void on_zRotationSpinBox_valueChanged(int arg1);

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
