#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtNetwork/QTcpSocket>
#include <QHttp>

class Widget : public QWidget
{
    Q_OBJECT

private:
    QTcpSocket *socket;
    QVBoxLayout *layout;
    QPlainTextEdit *log;
    QLineEdit *message;


private slots:
    void socketConnect();
    void socketRead();
    void socketDisconnect();
    void sendMessage();

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
