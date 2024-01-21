#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "letter.h"
#include <QMessageBox>
#include <QGridLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    MainWindow::setMinimumSize(900, 680);
    QGridLayout *current = new QGridLayout(this->centralWidget());

    ui->xScaleSpinBox->setValue(1);
    ui->yScaleSpinBox->setValue(1);
    ui->zScaleSpinBox->setValue(1);

    ui->xTransferSpinBox->setValue(0);
    ui->yTransferSpinBox->setValue(0);
    ui->zTransferSpinBox->setValue(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    ui->widget->check=1;
    ui->widget->update();
}

void MainWindow::on_pushButton_2_clicked() {
    ui->widget->check=2;
    ui->widget->update();
}

void MainWindow::on_pushButton_3_clicked() {
    ui->widget->check=3;
    ui->widget->update();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->x_scale=ui->xScaleSpinBox->value();

    ui->widget->y_scale=ui->yScaleSpinBox->value();

    ui->widget->z_scale=ui->zScaleSpinBox->value();

    ui->widget->check=4;
    ui->widget->update();
}

void MainWindow::on_pushButton_5_clicked()
{

    ui->widget->x_transfer=ui->xTransferSpinBox->value();

    ui->widget->y_transfer = ui->yTransferSpinBox->value();

    ui->widget->z_transfer=ui->zTransferSpinBox->value();

    ui->widget->check=5;
    ui->widget->update();
}

void MainWindow::on_pushButton_6_clicked() {

    if(ui->xRotationSpinBox->value() == 360){
        ui-> xRotationSpinBox->setValue(0);
    }

    ui->widget->check=6;
    ui->widget->angle= ui->xRotationSpinBox->value();
    ui->widget->update();
}

void MainWindow::on_pushButton_7_clicked() {

    if(ui->yRotationSpinBox->value() == 360){
        ui-> yRotationSpinBox->setValue(0);
    }

    ui->widget->check=7;
    ui->widget->angle= ui->yRotationSpinBox->value();
    ui->widget->update();
}

void MainWindow::on_pushButton_8_clicked() {

    if(ui->zRotationSpinBox->value() == 360){
        ui-> zRotationSpinBox->setValue(0);
    }
    ui->widget->check=8;
    ui->widget->angle= ui->zRotationSpinBox->value();
    ui->widget->update();
}

void MainWindow::on_pushButton_9_clicked() {
    ui->widget->check = 9;
    ui->widget->getVertexArray();
    ui->widget->drawFigure();
    ui->widget->update();

    ui->xScaleSpinBox->setValue(1);
    ui->yScaleSpinBox->setValue(1);
    ui->zScaleSpinBox->setValue(1);

    ui->xTransferSpinBox->setValue(0);
    ui->yTransferSpinBox->setValue(0);
    ui->zTransferSpinBox->setValue(0);

    ui-> xRotationSpinBox->setValue(0);
    ui-> yRotationSpinBox->setValue(0);
    ui-> zRotationSpinBox->setValue(0);
}


void MainWindow::on_xScaleSpinBox_valueChanged(double arg1) {
    GLfloat conv[3][3] ;
    conv[0][0]=ui->xScaleSpinBox->value();
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=ui->yScaleSpinBox->value();
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=ui->zScaleSpinBox->value();

    QString str;

    str.append("Scale matrix: \n");
    for(int i=0; i < 3; i++)
    {
        str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_4_clicked();
}

void MainWindow::on_yScaleSpinBox_valueChanged(double arg1) {
    GLfloat conv[3][3] ;
    conv[0][0]=ui->xScaleSpinBox->value();
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=ui->yScaleSpinBox->value();
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=ui->zScaleSpinBox->value();

    QString str;

    str.append("Scale matrix: \n");
    for(int i=0; i < 3; i++)
    {
        str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_4_clicked();
}

void MainWindow::on_zScaleSpinBox_valueChanged(double arg1) {
    GLfloat conv[3][3] ;
    conv[0][0]=ui->xScaleSpinBox->value();
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=ui->yScaleSpinBox->value();
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=ui->zScaleSpinBox->value();

    QString str;

    str.append("Scale matrix: \n");
    for(int i=0; i < 3; i++)
    {
        str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_4_clicked();
}

void MainWindow::on_xTransferSpinBox_valueChanged(double arg1) {
    GLfloat conv[4][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;

    conv[3][0]=ui->xTransferSpinBox->value();
    conv[3][1]=ui->yTransferSpinBox->value();
    conv[3][2]=ui->zTransferSpinBox->value();

    QString str;

    str.append("Transfer matrix: \n");

    for(int i=0; i < 4; i++)
    {
       str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);

    MainWindow::on_pushButton_5_clicked();
}

void MainWindow::on_yTransferSpinBox_valueChanged(double arg1) {
    GLfloat conv[4][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;

    conv[3][0]=ui->xTransferSpinBox->value();
    conv[3][1]=ui->yTransferSpinBox->value();
    conv[3][2]=ui->zTransferSpinBox->value();

    QString str;

    str.append("Transfer matrix: \n");

    for(int i=0; i < 4; i++)
    {
       str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_5_clicked();
}

void MainWindow::on_zTransferSpinBox_valueChanged(double arg1) {
    GLfloat conv[4][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;

    conv[3][0]=ui->xTransferSpinBox->value();
    conv[3][1]=ui->yTransferSpinBox->value();
    conv[3][2]=ui->zTransferSpinBox->value();

    QString str;

    str.append("Transfer matrix: \n");

    for(int i=0; i < 4; i++)
    {
       str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_5_clicked();
}

void MainWindow::on_xRotationSpinBox_valueChanged(int arg1) {
    GLfloat conv[3][3] ;
    conv[0][0]=1;
    conv[0][1]=0;
    conv[0][2]=0;

    conv[1][0]=0;
    conv[1][1]=cos(ui->xRotationSpinBox->value()*(M_PI/180.0));
    conv[1][2]=-sin(ui->xRotationSpinBox->value()*(M_PI/180.0));

    conv[2][0]=0;
    conv[2][1]=sin(ui->xRotationSpinBox->value()*(M_PI/180.0));
    conv[2][2]=cos(ui->xRotationSpinBox->value()*(M_PI/180.0));

    QString str;

    str.append("X rotation matrix: \n");
    for(int i=0; i < 3; i++)
    {
       str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_6_clicked();
}

void MainWindow::on_yRotationSpinBox_valueChanged(int arg1) {
    GLfloat conv[3][3] ;
    conv[0][0]=cos(ui->yRotationSpinBox->value()*(M_PI/180.0));
    conv[0][1]=0;
    conv[0][2]=sin(ui->yRotationSpinBox->value()*(M_PI/180.0));

    conv[1][0]=0;
    conv[1][1]=1;
    conv[1][2]=0;

    conv[2][0]=-sin(ui->yRotationSpinBox->value()*(M_PI/180.0));
    conv[2][1]=0;
    conv[2][2]=cos(ui->yRotationSpinBox->value()*(M_PI/180.0));

    QString str;

    str.append("Y rotation matrix: \n");
    for(int i=0; i < 3; i++)
    {
       str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_7_clicked();
}

void MainWindow::on_zRotationSpinBox_valueChanged(int arg1){
    GLfloat conv[3][3] ;
    conv[0][0]=cos(ui->zRotationSpinBox->value()*(M_PI/180.0));;
    conv[0][1]=-sin(ui->zRotationSpinBox->value()*(M_PI/180.0));;
    conv[0][2]=0;

    conv[1][0]=sin(ui->zRotationSpinBox->value()*(M_PI/180.0));
    conv[1][1]=cos(ui->zRotationSpinBox->value()*(M_PI/180.0));
    conv[1][2]=0;

    conv[2][0]=0;
    conv[2][1]=0;
    conv[2][2]=1;

    QString str;

    str.append("Z rotation matrix: \n");
    for(int i=0; i < 3; i++)
    {
       str.append(QString::number(conv[i][0]) + "\t" + QString::number(conv[i][1]) + "\t" + QString::number(conv[i][2]) + " \n");
    }
    ui->outputLabel->setText(str);
    MainWindow::on_pushButton_8_clicked();
}
