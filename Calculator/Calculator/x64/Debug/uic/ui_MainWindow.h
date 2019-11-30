/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QLineEdit *lineEdit_a;
    QLineEdit *lineEdit_b;
    QLineEdit *lineEdit_c;
    QRadioButton *radioButton_a;
    QRadioButton *radioButton_b;
    QRadioButton *radioButton_c;
    QRadioButton *radioButton_d;
    QGroupBox *groupBox;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_equal;

    void setupUi(QWidget *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(600, 400);
        lineEdit_a = new QLineEdit(MainWindowClass);
        lineEdit_a->setObjectName(QStringLiteral("lineEdit_a"));
        lineEdit_a->setGeometry(QRect(300, 80, 250, 30));
        lineEdit_b = new QLineEdit(MainWindowClass);
        lineEdit_b->setObjectName(QStringLiteral("lineEdit_b"));
        lineEdit_b->setGeometry(QRect(300, 160, 250, 30));
        lineEdit_c = new QLineEdit(MainWindowClass);
        lineEdit_c->setObjectName(QStringLiteral("lineEdit_c"));
        lineEdit_c->setGeometry(QRect(100, 240, 450, 30));
        radioButton_a = new QRadioButton(MainWindowClass);
        radioButton_a->setObjectName(QStringLiteral("radioButton_a"));
        radioButton_a->setGeometry(QRect(53, 160, 41, 19));
        radioButton_b = new QRadioButton(MainWindowClass);
        radioButton_b->setObjectName(QStringLiteral("radioButton_b"));
        radioButton_b->setGeometry(QRect(95, 160, 41, 19));
        radioButton_c = new QRadioButton(MainWindowClass);
        radioButton_c->setObjectName(QStringLiteral("radioButton_c"));
        radioButton_c->setGeometry(QRect(160, 160, 41, 19));
        radioButton_d = new QRadioButton(MainWindowClass);
        radioButton_d->setObjectName(QStringLiteral("radioButton_d"));
        radioButton_d->setGeometry(QRect(210, 160, 41, 19));
        groupBox = new QGroupBox(MainWindowClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 129, 211, 91));
        pushButton_reset = new QPushButton(MainWindowClass);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));
        pushButton_reset->setGeometry(QRect(300, 297, 93, 41));
        pushButton_exit = new QPushButton(MainWindowClass);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(450, 297, 93, 41));
        pushButton_equal = new QPushButton(MainWindowClass);
        pushButton_equal->setObjectName(QStringLiteral("pushButton_equal"));
        pushButton_equal->setGeometry(QRect(53, 240, 41, 28));
        groupBox->raise();
        lineEdit_a->raise();
        lineEdit_b->raise();
        lineEdit_c->raise();
        radioButton_a->raise();
        radioButton_b->raise();
        radioButton_c->raise();
        radioButton_d->raise();
        pushButton_reset->raise();
        pushButton_exit->raise();
        pushButton_equal->raise();

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
        radioButton_a->setText(QApplication::translate("MainWindowClass", "+", nullptr));
        radioButton_b->setText(QApplication::translate("MainWindowClass", "-", nullptr));
        radioButton_c->setText(QApplication::translate("MainWindowClass", "*", nullptr));
        radioButton_d->setText(QApplication::translate("MainWindowClass", "/", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindowClass", "\350\256\241\347\256\227", nullptr));
        pushButton_reset->setText(QApplication::translate("MainWindowClass", "\351\207\215\347\275\256(R)", nullptr));
        pushButton_exit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272(X)", nullptr));
        pushButton_equal->setText(QApplication::translate("MainWindowClass", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
