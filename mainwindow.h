#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
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

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void onNewConnection();
    void onReadyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTcpSocket *clientSocket;
};

#endif // MAINWINDOW_H
