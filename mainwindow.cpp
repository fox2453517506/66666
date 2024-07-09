#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tcpSocket(new QTcpSocket(this))
    , tcpServer(new QTcpServer(this))
    , clientSocket(nullptr)
{
    ui->setupUi(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::onNewConnection);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() // Connect to client
{
    QString address = ui->lineEdit->text();
    quint16 port = ui->lineEdit_2->text().toUShort();
    tcpSocket->connectToHost(address, port);

    if (tcpSocket->waitForConnected(3000)) {
        ui->textBrowser->append("Client connected successfully");
    } else {
        ui->textBrowser->append("Client connection failed");
    }
}

void MainWindow::on_pushButton_2_clicked() // Start server
{
    quint16 port = ui->lineEdit_2->text().toUShort();
    if (tcpServer->listen(QHostAddress::Any, port)) {
        ui->textBrowser->append("Server started successfully");
    } else {
        ui->textBrowser->append("Server start failed");
    }
}

void MainWindow::on_pushButton_3_clicked() // Send message
{
    QString message = ui->lineEdit_4->text();
    if (clientSocket && clientSocket->isOpen()) {
        clientSocket->write(message.toUtf8());
        ui->textBrowser_2->append("Message sent: " + message);
    } else {
        ui->textBrowser_2->append("No client connected");
    }
}


void MainWindow::on_pushButton_4_clicked() // Clear receive window
{
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
}


void MainWindow::onNewConnection()
{
    clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    ui->textBrowser->append("Client connection established");
}

void MainWindow::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        QString message = QString::fromUtf8(socket->readAll());
        ui->textBrowser->append("Message received: " + message);
    }
}
