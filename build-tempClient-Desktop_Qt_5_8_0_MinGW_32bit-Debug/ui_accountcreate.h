/********************************************************************************
** Form generated from reading UI file 'accountcreate.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTCREATE_H
#define UI_ACCOUNTCREATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_accountCreate
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *accountCreate)
    {
        if (accountCreate->objectName().isEmpty())
            accountCreate->setObjectName(QStringLiteral("accountCreate"));
        accountCreate->resize(233, 220);
        centralwidget = new QWidget(accountCreate);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(90, 10, 113, 21));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 40, 113, 21));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 70, 113, 21));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(90, 100, 113, 21));
        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(90, 130, 113, 21));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 71, 20));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 40, 81, 20));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(-20, 70, 101, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(0, 100, 81, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 130, 71, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 160, 80, 21));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(70, 190, 80, 21));
        accountCreate->setCentralWidget(centralwidget);

        retranslateUi(accountCreate);

        QMetaObject::connectSlotsByName(accountCreate);
    } // setupUi

    void retranslateUi(QMainWindow *accountCreate)
    {
        accountCreate->setWindowTitle(QApplication::translate("accountCreate", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("accountCreate", "Username", Q_NULLPTR));
        label_2->setText(QApplication::translate("accountCreate", "Email Address", Q_NULLPTR));
        label_3->setText(QApplication::translate("accountCreate", "First Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("accountCreate", "Last Name", Q_NULLPTR));
        label_5->setText(QApplication::translate("accountCreate", "Password", Q_NULLPTR));
        pushButton->setText(QApplication::translate("accountCreate", "Create Account", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("accountCreate", "Login", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class accountCreate: public Ui_accountCreate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTCREATE_H
