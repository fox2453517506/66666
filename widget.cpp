#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (username == "admin" && password == "1234") {
        mainWindow.show();
        this->close();

    } else {
        ui->label_4->setText( "Account or password error!");
        ui->label_4->setStyleSheet("QLabel { color : red; }");
    }
}


void Widget::on_pushButton_2_clicked()
{
    this->close();
}

