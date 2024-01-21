#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cryptopp/osrng.h>
#include <cryptopp/serpent.h>

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void newMessage(QString);
private slots:
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();
    void on_pushButton_generate_RSA_keys_clicked();

    void showLoginWindow();
    void showPinWindow();
private:
    Ui::MainWindow *ui;

    QTcpSocket* socket;

    int m_PublicKey{};
    double m_PrivateKey{};
    int m_Modulus{};

    CryptoPP::SecByteBlock m_Key{};
    CryptoPP::byte m_Iv[CryptoPP::Serpent::BLOCKSIZE];

    std::unique_ptr<QTimer> m_TimerPin{nullptr};
    std::chrono::milliseconds m_TimerInterval{30000};

};

#endif // MAINWINDOW_H
