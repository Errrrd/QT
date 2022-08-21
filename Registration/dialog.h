#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextEdit>
#include <QRegularExpression>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGridLayout>
#include <QCryptographicHash>
//#include <bits/functional_hash.h>

class Dialog : public QDialog
{
    Q_OBJECT

private:
    QGridLayout *layout;

    QLabel *labelLog;
    QPushButton *accept;
    QTextEdit *log;

    QLabel *labelUsername;
    QLineEdit *username;
    QLabel *labelLogin;
    QLineEdit *login;
    QLabel *labelPassword;
    QLineEdit *password;
    QLabel *labelRpassword;
    QLineEdit *rpassword;
    QLabel *labelE_mail;
    QLineEdit *e_mail;
    QLabel *labelPhone;
    QLineEdit *phone;
    QLabel *labelDomain;
    QLineEdit *domain;
    QLabel *labelCredit_card;
    QLineEdit *credit_card;
    QLabel *labelIP_address;
    QLineEdit *ip_address;

private slots:
    void setAccept();

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    bool setUsername(QTextStream &out, QTextStream &out1);

    bool setLogin(QTextStream &out, QTextStream &out1, QTextStream &fout2);

    bool setPassword(QTextStream &out, QTextStream &out1);

    bool setRpassword();

    bool setE_mail(QTextStream &out, QTextStream &out1);

    bool setPhone(QTextStream &out, QTextStream &out1);

    bool setDomain(QTextStream &out, QTextStream &out1);

    bool setCreditCard(QTextStream &out, QTextStream &out1);

    bool setIP(QTextStream &out, QTextStream &out1);
};
#endif // DIALOG_H
