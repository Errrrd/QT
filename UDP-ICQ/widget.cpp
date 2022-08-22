#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      socketRec(new QUdpSocket(this)),
      layout(new QVBoxLayout(this)),
      log(new QPlainTextEdit(this)),
      message(new QLineEdit(this))
{
    layout->addWidget(log);
    layout->addWidget(message);

    log->setReadOnly(true);
    message->setFocus();

    connect(socketRec, SIGNAL(readyRead()), SLOT(receiveInfo()));
    connect(message, SIGNAL(returnPressed()), SLOT(sendMessage()));

    socketRec->bind(QHostAddress::Any, 1234);
    log->appendPlainText("Receiver ready");
    connection();
}

Widget::~Widget()
{
    socketRec->writeDatagram("!disc Erd", QHostAddress::Broadcast, 1234);
    qDebug()<<"!disc Erd";
}

void Widget::receiveInfo(){
    qint64 size = socketRec->pendingDatagramSize();//получаем размер датаграммы
    char data[size];
    char reper[6] = {'!','c','o', 'n', 'n', ' '};
    QString stU8;

    socketRec->readDatagram(data, size);//считываем датаграмму
    qDebug()<< data;
    if(size > 6) {
        bool conn = true;

        for(int i=0; i<6; i++ ){
            conn = conn*(data[i] == reper[i]);
        }

        if(conn) {
            isOnline();
        }
    }

    stU8 = QString::fromUtf8(data);
    log->appendPlainText(stU8);
//    log->appendPlainText(data);
}

void Widget::sendMessage() {
    QByteArray data;

    data.append("Erd: ");
    data.append(message->text().toUtf8().data());

    socketRec->writeDatagram(data, QHostAddress::LocalHost, 1234);
    message->clear();
}

void Widget::connection() {
    socketRec->writeDatagram("!conn Erd", QHostAddress::Broadcast, 1234);
    qDebug("!conn Erd");
}

void Widget::isOnline(){
    socketRec->writeDatagram("!onln Erd", QHostAddress::Broadcast, 1234);//подставить адрем вошедшего...
    qDebug("!onln Erd");
}
