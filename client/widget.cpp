#include "widget.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      socket(new QTcpSocket(this)),
      layout(new QVBoxLayout(this)),
      log(new QPlainTextEdit),
      message(new QLineEdit(this))
{
    layout->addWidget(log);
    layout->addWidget(message);

    log->setReadOnly(true);
    message->setFocus();

    connect(socket, SIGNAL(connected()), SLOT(socketConnect()));
    connect(socket, SIGNAL(readyRead()), SLOT(socketRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(socketDisconnect()));
    connect(message, SIGNAL(returnPressed()), SLOT(sendMessage()));

    //socket->connectToHost("172.16.1.108", 5678);
    socket->connectToHost("dragons.org", 80);

}

Widget::~Widget()
{

}

void Widget::socketConnect() {
    log->appendPlainText("connect");
    socket->write("GET / HTTP/1.1\nhost: dragons.org\n\n");
}

void Widget::socketRead() {
    log->appendPlainText(socket->readAll());
    log->appendPlainText("ready");
}

void Widget::socketDisconnect() {
    log->appendPlainText("disconnect");
}

void Widget::receiveMessage() {
    QString data;

    //socket->write(data.toUtf8());
    //message->clear();
}

void Widget::sendMessage() {
    QString data= message->text();

    socket->write(data.toUtf8());
    message->clear();
}
