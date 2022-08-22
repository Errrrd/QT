#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QUdpSocket>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLineEdit>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QUdpSocket *socketRec;
    QVBoxLayout *layout;
    QPlainTextEdit *log;
    QLineEdit *message;

    void connection();
    void isOnline();

private slots:
    void receiveInfo();
    void sendMessage();


public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
