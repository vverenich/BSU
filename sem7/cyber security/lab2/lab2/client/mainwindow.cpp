#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QDebug>
#include <QTimer>
#include <QInputDialog>

#include <cryptopp/hex.h>
#include <cryptopp/modes.h>

#include <RSA.h>
#include "QLoginDialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    // uncomment if you are using Qt <  5.14
    //connect(socket, &QAbstractSocket::, this, &MainWindow::displayError);

    socket->connectToHost(QHostAddress::LocalHost,8080);

    if(socket->waitForConnected())
        ui->statusBar->showMessage("Connected to Server");
    else{
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }

    m_TimerPin = std::make_unique<QTimer>();
    connect(m_TimerPin.get(), &QTimer::timeout, this, &MainWindow::showPinWindow);

    QTimer::singleShot(0, this, &MainWindow::showLoginWindow);
}

MainWindow::~MainWindow()
{
    if(socket->isOpen())
        socket->close();
    delete ui;
}

void MainWindow::readSocket()
{
    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_14);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

    if(fileType=="attachment"){
        QString fileName = header.split(",")[1].split(":")[1];
        QString ext = fileName.split(".")[1];
        QString size = header.split(",")[2].split(":")[1].split(";")[0];

        if (QMessageBox::Yes == QMessageBox::question(this, "QTCPServer", QString("You are receiving an attachment from sd:%1 of size: %2 bytes, called %3. Do you want to accept it?").arg(socket->socketDescriptor()).arg(size).arg(fileName)))
        {
            QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("File (*.%1)").arg(ext));

            QFile file(filePath);
            if(file.open(QIODevice::WriteOnly)){
                file.write(buffer);
                QString message = QString("INFO :: Attachment from sd:%1 successfully stored on disk under the path %2").arg(socket->socketDescriptor()).arg(QString(filePath));
                emit newMessage(message);
            }else
                QMessageBox::critical(this,"QTCPServer", "An error occurred while trying to write the attachment.");
        }else{
            QString message = QString("INFO :: Attachment from sd:%1 discarded").arg(socket->socketDescriptor());
            emit newMessage(message);
        }
    }else if(fileType=="message"){
        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    } /*else if (fileType=="key") {
        m_Key.resize(CryptoPP::Serpent::DEFAULT_KEYLENGTH);
        for (size_t i{0}; i< buffer.size(); ++i) {
            *(m_Key.begin() + i) = buffer.at(i);
        }
        QString message = QString("%1 :: key received %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    } else if (fileType=="iv") {
        for (size_t i{0}; i< CryptoPP::Serpent::BLOCKSIZE; ++i) {
            m_Iv[i] = buffer.at(i);
        }
        QString message = QString("%1 :: iv received %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    } */else if (fileType=="file") {


        QByteArray keyByteArrayHex{""};
        for (size_t i{0}; i < CryptoPP::Serpent::DEFAULT_KEYLENGTH * 2; ++i) {
            keyByteArrayHex.push_back(buffer.at(i));
        }

        QByteArray ivByteArrayHex{""};
        for (size_t i{CryptoPP::Serpent::DEFAULT_KEYLENGTH * 2}; i < CryptoPP::Serpent::BLOCKSIZE * 2 + CryptoPP::Serpent::DEFAULT_KEYLENGTH * 2; ++i) {
            ivByteArrayHex.push_back(buffer.at(i));
        }

        QByteArray cipherByteArrayHex{""};
        for (size_t i{CryptoPP::Serpent::BLOCKSIZE * 2 + CryptoPP::Serpent::DEFAULT_KEYLENGTH * 2}; i < buffer.size(); ++i) {
            cipherByteArrayHex.push_back(buffer.at(i));
        }

        qDebug() << keyByteArrayHex << " size: " << keyByteArrayHex.size();
        qDebug() << ivByteArrayHex << " size: " << ivByteArrayHex.size();
        qDebug() << cipherByteArrayHex << " size: " << cipherByteArrayHex.size();
        qDebug() << buffer << " size: " << buffer.size();


        QByteArray keyByteArray{QByteArray::fromHex(keyByteArrayHex)};
        QByteArray ivByteArray{QByteArray::fromHex(ivByteArrayHex)};
        QByteArray cipherByteArray{QByteArray::fromHex(cipherByteArrayHex)};

        qDebug() << keyByteArray << " size: " << keyByteArray.size();
        qDebug() << ivByteArray << " size: " << ivByteArray.size();
        qDebug() << cipherByteArray << " size: " << cipherByteArray.size();
        qDebug() << buffer << " size: " << buffer.size();



        m_Key.resize(CryptoPP::Serpent::DEFAULT_KEYLENGTH);
        for (size_t i{0}; i < keyByteArray.size(); ++i) {
            *(m_Key.begin() + i) = static_cast<CryptoPP::byte>(keyByteArray.at(i));
        }

        for (size_t i{0}; i < ivByteArray.size(); ++i) {
            m_Iv[i] = static_cast<CryptoPP::byte>(ivByteArray.at(i));
        }

        std::string cipher{};
        for (size_t i{0}; i < cipherByteArray.size(); ++i) {
            cipher.push_back((cipherByteArray.at(i)));
        }

        QString message = QString("%1 :: encrypted file received").arg(socket->socketDescriptor());

        std::string recovered{};
        try
        {
            CryptoPP::CBC_Mode< CryptoPP::Serpent >::Decryption d;
            d.SetKeyWithIV(m_Key, m_Key.size(), m_Iv);

            // The StreamTransformationFilter removes
            //  padding as required.
            CryptoPP::StringSource ss3(cipher, true,
                             new CryptoPP::StreamTransformationFilter(d,
                                                            new CryptoPP::StringSink(recovered)
                                                            ) // StreamTransformationFilter
                             ); // StringSource

            std::cout << "recovered text: " << recovered << std::endl;
        }
        catch(const CryptoPP::Exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }


        emit newMessage(QString::fromStdString(recovered));
    }
}

void MainWindow::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;

    ui->statusBar->showMessage("Disconnected!");
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPClient", "The host was not found. Please check the host name and port settings.");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPClient", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
        default:
            QMessageBox::information(this, "QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}

void MainWindow::on_pushButton_sendMessage_clicked()
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString str = ui->lineEdit_message->text();

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_14);


            QByteArray header;
            QStringList list = str.split(':');

            if (list.at(0) == "file") {
                header.prepend(QString("fileType:file,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                header.resize(128);
            } else {
                header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
                header.resize(128);
            }


            QByteArray byteArray = str.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;

            ui->lineEdit_message->clear();
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

void MainWindow::on_pushButton_sendAttachment_clicked()
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString filePath = QFileDialog::getOpenFileName(this, ("Select an attachment"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json *.txt *.png *.jpg *.jpeg)"));

            if(filePath.isEmpty()){
                QMessageBox::critical(this,"QTCPClient","You haven't selected any attachment!");
                return;
            }

            QFile m_file(filePath);
            if(m_file.open(QIODevice::ReadOnly)){

                QFileInfo fileInfo(m_file.fileName());
                QString fileName(fileInfo.fileName());

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_14);

                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = m_file.readAll();
                byteArray.prepend(header);

                socketStream.setVersion(QDataStream::Qt_5_14);
                socketStream << byteArray;
            }else
                QMessageBox::critical(this,"QTCPClient","Attachment is not readable!");
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

void MainWindow::on_pushButton_generate_RSA_keys_clicked()
{
    RSA::generateKeys(m_PublicKey, m_PrivateKey, m_Modulus);

    std::string str{"I am Vlad"};
    std::cout << "\n" << "str: " << str;
    std::string encryptedStr = RSA::encrypt(str, m_PublicKey, m_Modulus);
    std::cout << "\n" << "encrypted: " << encryptedStr;
    std::string decryptedStr = RSA::decrypt(encryptedStr, m_PrivateKey, m_Modulus);
    std::cout << "\n" << "decrypted: " << decryptedStr;


    QString pubKey = QString::number(m_PublicKey) + "_" + QString::number(m_Modulus);

    if(socket)
    {
        if(socket->isOpen())
        {
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_14);

            QByteArray header;
            header.prepend(QString("fileType:rsa,fileName:null,fileSize:%1;").arg(pubKey.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = pubKey.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

void MainWindow::showLoginWindow()
{
    QLoginDialog dlg(this);

    if( dlg.exec() == QDialog::Accepted )
    {
        //qDebug() << "user： " << dlg.getUser();
        //qDebug() << "password " << dlg.getPassword();

        m_TimerPin->start(m_TimerInterval);
    }
}

void MainWindow::showPinWindow()
{
    QString text = QInputDialog::getText(this, "Pin", "Your PIN", QLineEdit::Password);
}

void MainWindow::displayMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}
