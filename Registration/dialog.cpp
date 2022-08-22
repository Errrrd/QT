#include "dialog.h"

#include <QRegExp>
/*
 * Завдання:
 * Реалізувати валідацію наступних типів введених даних
 *
 * username
 * Може містити лише літери латинського алфавіту та дефіси.
 * Може складатися з кількох слів.
 * Слово не може починатися з дефісу.
 *
 * login
 * Може містити лише латинські літери, цифри, дефіси та підкреслення. Не може починатися з дефісу та підкреслення.
 *
 * password
 * Не може містити літери, відмінні від латинських.
 * Не може містити прогалини, переклади рядка, табуляцію тощо.
 * Перевірка безпеки повинен містити великі та маленькі літери латинського алфавіту, цифри та спецсимволи. Відстежити, чого не вистачає для безпеки.
 *
 * phone, domain, e-mail, credit card number, ip address
 * З'ясувати, як правильно валідувати кожне з цих полів у проф. Гугля.
 * Реалізувати валідацію.
 *
 * Будьте уважні! Айпі адреса - це не просто чотири числа, а номер кредитки - не просто 16 цифр!
 *
 * ------------------------------------------------- ---------
 * файли out.txt і users.csv закинути в папку з програмою... або вказати шлях.
 */
Dialog::Dialog(QWidget *parent)
    : QDialog(parent),
    layout(new QGridLayout(this)),
    labelLog(new QLabel("Messages")),
    accept(new QPushButton("accept")),
    log(new QTextEdit(this)),

    labelUsername(new QLabel("Username:\nLatin letters or/and '-'. One or some words")),
    username(new QLineEdit(this)),

    labelLogin(new QLabel("Login:\nLatin letters or/and numerals, '-', '_'")),
    login(new QLineEdit(this)),

    labelPassword(new QLabel("Password: \nMust be Latin letters (upper and lower case), \nnumerals and special characters (one or more)")),
    password(new QLineEdit(this)),

    labelRpassword(new QLabel("Repeat password:")),
    rpassword(new QLineEdit(this)),

    labelE_mail(new QLabel("e-mail:\nfor sample user@domain.com")),
    e_mail(new QLineEdit(this)),

    labelPhone(new QLabel("Phone number (11 numerals):\nfor sample 30445556677")),
    phone(new QLineEdit(this)),

    labelDomain(new QLabel("Domain:\nfor sample www.domain.com")),
    domain(new QLineEdit(this)),

    labelCredit_card(new QLabel("Credit card number: (4x4 numerals, one space parted):\nformat XXXX XXXX XXXX XXXX")),
    credit_card(new QLineEdit(this)),

    labelIP_address(new QLabel("ip address: (4 numbers from 0 to 255 )\nfor sample 123.3.0.55")),
    ip_address(new QLineEdit(this))
{
    layout->addWidget(labelUsername, 0, 0);
    layout->addWidget(username, 0, 1);
    layout->addWidget(labelLogin, 1, 0);
    layout->addWidget(login, 1, 1);
    layout->addWidget(labelPassword, 2, 0);
    layout->addWidget(password, 2, 1);
    layout->addWidget(labelRpassword, 3, 0);
    layout->addWidget(rpassword, 3, 1);
    layout->addWidget(labelE_mail, 4, 0);
    layout->addWidget(e_mail, 4, 1);
    layout->addWidget(labelPhone, 5, 0);
    layout->addWidget(phone, 5, 1);
    layout->addWidget(labelDomain, 6, 0);
    layout->addWidget(domain, 6, 1);
    layout->addWidget(labelCredit_card, 7, 0);
    layout->addWidget(credit_card, 7, 1);
    layout->addWidget(labelIP_address, 8, 0);
    layout->addWidget(ip_address, 8, 1);

    layout->addWidget(log, 10, 0, 12, 2);
    layout->addWidget(labelLog, 9, 0);

    layout->addWidget(accept, 9, 1);

    log->setReadOnly(true);

    connect(accept, SIGNAL(clicked()), SLOT(setAccept()));

}

Dialog::~Dialog()
{
    delete labelLog;
    delete accept;

    delete labelUsername;
    delete username;

    delete labelLogin;
    delete login;

    delete labelPassword;
    delete password;

    delete labelRpassword;
    delete rpassword;

    delete labelE_mail;
    delete e_mail;

    delete labelPhone;
    delete phone;

    delete labelDomain;
    delete domain;

    delete labelCredit_card;
    delete credit_card;

    delete labelIP_address;
    delete ip_address;

    delete layout;
    delete log;
}

void Dialog::setAccept() {
    bool valid = true;
    QFile file("../Registration/out.txt"); // set path for files
    QFile infile("../Registration/users.csv"); // set path for files
    QFile users("../Registration/users.csv"); // set path for files

    if (!file.open(QIODevice::Append | QIODevice::Text)){
        log->append("out.txt file not found");

        return;
    }
    if (!infile.open(QIODevice::ReadOnly | QIODevice::Text)){
        log->append("users.csv file not found");
        return;
    }
    if (!users.open(QIODevice::Append | QIODevice::Text)){
        log->append("users.csv file not found");
        return;
    }
    QString str;
    QString csv;
    QTextStream out(&str);
    QTextStream out1(&csv);
    QTextStream fout(&file);
    QTextStream fout1(&users);
    QTextStream fin(&infile);

    accept->blockSignals(true);

    log->append("Progress\n");

    valid *= setUsername(out, out1);

    valid *= setLogin(out, out1, fin);

    valid *= setPassword(out, out1);

    valid *= setRpassword();

    valid *= setE_mail(out, out1);

    valid *= setPhone(out, out1);

    valid *= setDomain(out, out1);

    valid *= setCreditCard(out, out1);

    valid *= setIP(out, out1);

    if(valid) {
        log->append("\nvalidate");
        out << "\n";
        out1 << "\n";
        fout << str;
        fout1 << csv;
    }
    accept->blockSignals(valid);
    username->setReadOnly(valid);
    login->setReadOnly(valid);
    password->setReadOnly(valid);
    rpassword->setReadOnly(valid);
    e_mail->setReadOnly(valid);
    phone->setReadOnly(valid);
    domain->setReadOnly(valid);
    credit_card->setReadOnly(valid);
    ip_address->setReadOnly(valid);
}

bool Dialog::setUsername(QTextStream &out, QTextStream &out1) {
    QRegExp rx("^(([A-Za-z])+)((([-]|[ ])([A-Za-z]+))*)$");
    QString user = username->text();
    bool correct = true;

    correct = user.contains(rx);
    if (correct) {
        log->append("valid username");
        out << "Username:" << user << "\n";
        out1<< user << "; ";
    } else {
        log->append("invalid username");
    }
    return correct;
}

bool Dialog::setLogin(QTextStream &out, QTextStream &out1, QTextStream &fin) {
    QRegExp rx("^([A-Za-z0-9])(([A-Za-z0-9_-])*)$");
    QString tmp_login = login->text();
    QString csvfile(fin.readAll());
    QString rxStr = "([;]|[,])([ ]*)(";
    QRegExp rxLog;
    bool correct = true;


    correct = tmp_login.contains(rx);
    if (correct) {
        rxStr.append(tmp_login);
        rxStr.append(")([ ]*)([;]|[,])");
        rxLog.setPattern(rxStr);

        correct = !csvfile.contains(rxLog);
        if( correct ) {
            log->append("valid login");
            out << "Login:" << tmp_login << "\n";
            out1<< tmp_login << "; ";
        } else {
            log->append("This login was used.\n Set up is other login");
        }
    } else {
        log->append("invalid login");
    }
    return correct;
}

bool Dialog::setPassword(QTextStream &out, QTextStream &out1) {
    QRegExp rx("^([!-~]{4,})$");
    QString pass = password->text();
    QByteArray pass1;
    QString salt = "paralipomenon";
    bool correct = true;
    QByteArray hashpass;

    pass1.append(pass.toStdString().c_str());
    pass1.append(salt.toStdString().c_str());
    hashpass = QCryptographicHash::hash(pass1, QCryptographicHash::Md5);

    correct = pass.contains(rx);
    if( correct ) {
        rx.setPattern("[a-z]");
        correct *= correct&&pass.contains(rx);
        rx.setPattern("[A-Z]");
        correct = correct&&pass.contains(rx);
        rx.setPattern("[0-9]");
        correct = correct&&pass.contains(rx);
        rx.setPattern("[!-/:-@[-`{-~]");
        correct = correct&&pass.contains(rx);
    }
    if (correct) {
        log->append("valid password");
        out << "Password:" << hashpass << "\n";
        out1 << "\"" << hashpass << "\"" << "; ";
    } else {
        log->append("invalid password");
    }
    return correct;
}

bool Dialog::setRpassword() {
    QString pass = password->text();
    QString rpass = rpassword->text();
    bool correct = (pass == rpass);

    if (correct) {
        log->append("repeated password correct");
    } else {
        log->append("repeated password incorrect");
    }
    return correct;
}

bool Dialog::setE_mail(QTextStream &out, QTextStream &out1) {
    QRegExp rx("^([a-z0-9])(([a-z0-9_-])*)([@])((([a-z0-9]+)([_a-z0-9]*)(((-?)[a-z0-9]+)*)([.])?)+)([a-z0-9]+)$");
    QString mail = e_mail->text();
    bool correct = true;

    correct = mail.contains(rx);
    if (correct) {
        log->append("valid e-mail");
        out << "Domain:" << mail << "\n";
        out1<< mail << "; ";
    } else {
        log->append("invalid e-mail");
    }
    return correct;
}

bool Dialog::setPhone(QTextStream &out, QTextStream &out1) {
    QRegExp rx("^[0-9]{11,11}$");
    QString ph = phone->text();
    bool correct = true;

    correct = ph.contains(rx);
    if (correct) {
        log->append("valid phone");
        out << "Phone:" << "+" << ph << "\n";
        out1<< ph << "; ";
    } else {
        log->append("invalid phone");
    }
    return correct;
}

bool Dialog::setDomain(QTextStream &out, QTextStream &out1) {
    QRegExp rx("^((([a-z0-9]+)([_a-z0-9]*)(((-?)[a-z0-9]+)*)([.])?)+)([a-z0-9]+)$");
    QString dom = domain->text();
    bool correct = true;

    if( dom != "" ) {
        correct = dom.contains(rx);
    }
    if (correct) {
        log->append("valid domain");
        out << "Domain:" << dom << "\n";
        out1<< dom << "; ";
    } else {
        log->append("invalid domain");
    }
    return correct;
}

bool Dialog::setCreditCard(QTextStream &out, QTextStream &out1) {
    QRegExp rx("^([0-9]{4,4}([ ])[0-9]{4,4}([ ])[0-9]{4,4}([ ])[0-9]{4,4})$");
    QString card = credit_card->text();

    bool correct = true;

    correct = card.contains(rx);
    correct = (card[0].isDigit() && card[0].digitValue() > 0);
    if (correct) {
        int sum1, sum2, sum3, sum4, sum5, sum6, sum7, sum8;

        sum1 = (2 * card[0].digitValue());
        sum1 = sum1 % 10 + sum1 / 10 + card[1].digitValue();
        sum2 = (2 * card[2].digitValue());
        sum1 += sum2 % 10 + sum2 / 10 + card[3].digitValue();
        sum3 = (2 * card[5].digitValue());
        sum1 += sum3 % 10 + sum3 / 10 + card[6].digitValue();
        sum4 = (2 * card[7].digitValue());
        sum1 += sum4 % 10 + sum4 / 10 + card[8].digitValue();
        sum5 = (2 * card[10].digitValue());
        sum1 += sum5 % 10 + sum5 / 10 + card[11].digitValue();
        sum6 = (2 * card[12].digitValue());
        sum1 += sum6 % 10 + sum6 / 10 + card[13].digitValue();
        sum7 = (2 * card[15].digitValue());
        sum1 += sum7 % 10 + sum7 / 10 + card[16].digitValue();
        sum8 = (2 * card[17].digitValue());
        sum1 += sum8 % 10 + sum8 / 10 + card[18].digitValue();

//        sum2 = sum1/10 + 48;
//        sum3 = sum1%10 + 48;
//        QChar c1(sum2);
//        QChar c2(sum3);
//        QString s;

//        s.append(c1);
//        s.append(c2);
//        log->append(s);
        correct = (sum1 % 10 == 0);
    }
    if (correct) {
        log->append("valid credit card");
        out << "Credit card:" << card << "\n";
        out1 << "\"" << card << "\"" << "; ";
    } else {
        log->append("invalid credit card");
    }
    return correct;
}

bool Dialog::setIP(QTextStream &out, QTextStream &out1) {
    QRegExp rx("^([0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3})$");
    QString ipt = ip_address->text();

    bool correct = true;

    correct = ipt.contains(rx);
    if (correct) {
        ushort ip = 0;
        for( int i = 0; i <= 15 && correct; i++ ) {
            ushort dec = ipt[i].digitValue();

            if ( ipt[i].isDigit() ) {
                ip = ip * 10 + dec;
            } else {
                correct = (ip <= 255);
                ip = 0;
            }
        }
    }
    if (correct) {
        log->append("valid ip");
        out << "IP:" << ipt << "\n";
        out1 << ipt << "; ";
    } else {
        log->append("invalid IP");
    }
    return correct;
}
