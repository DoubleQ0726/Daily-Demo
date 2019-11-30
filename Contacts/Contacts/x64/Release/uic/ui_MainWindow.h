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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QPushButton *pushButton_input;
    QPushButton *pushButton_save;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_new;
    QPushButton *pushButton_update;
    QPushButton *pushButton_delete;
    QGroupBox *groupBox;
    QLabel *label_name;
    QLabel *label_number;
    QLabel *label_group;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_number;
    QComboBox *comboBox;
    QTableWidget *tableWidget;
    QPushButton *pushButton_clear;

    void setupUi(QWidget *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(600, 400);
        pushButton_input = new QPushButton(MainWindowClass);
        pushButton_input->setObjectName(QStringLiteral("pushButton_input"));
        pushButton_input->setGeometry(QRect(480, 37, 93, 28));
        pushButton_save = new QPushButton(MainWindowClass);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(480, 87, 93, 28));
        pushButton_exit = new QPushButton(MainWindowClass);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(480, 137, 93, 28));
        pushButton_new = new QPushButton(MainWindowClass);
        pushButton_new->setObjectName(QStringLiteral("pushButton_new"));
        pushButton_new->setGeometry(QRect(480, 207, 93, 28));
        pushButton_update = new QPushButton(MainWindowClass);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));
        pushButton_update->setGeometry(QRect(480, 257, 93, 28));
        pushButton_delete = new QPushButton(MainWindowClass);
        pushButton_delete->setObjectName(QStringLiteral("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(480, 307, 93, 28));
        groupBox = new QGroupBox(MainWindowClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 30, 381, 141));
        label_name = new QLabel(groupBox);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(20, 30, 72, 15));
        label_number = new QLabel(groupBox);
        label_number->setObjectName(QStringLiteral("label_number"));
        label_number->setGeometry(QRect(20, 90, 72, 15));
        label_group = new QLabel(groupBox);
        label_group->setObjectName(QStringLiteral("label_group"));
        label_group->setGeometry(QRect(230, 30, 72, 15));
        lineEdit_name = new QLineEdit(groupBox);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(70, 30, 113, 21));
        lineEdit_number = new QLineEdit(groupBox);
        lineEdit_number->setObjectName(QStringLiteral("lineEdit_number"));
        lineEdit_number->setGeometry(QRect(70, 90, 113, 21));
        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(270, 60, 87, 22));
        tableWidget = new QTableWidget(MainWindowClass);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(50, 201, 381, 161));
        pushButton_clear = new QPushButton(MainWindowClass);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(480, 357, 93, 28));

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
        pushButton_input->setText(QApplication::translate("MainWindowClass", "\350\275\275\345\205\245(L)", nullptr));
        pushButton_save->setText(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230(S)", nullptr));
        pushButton_exit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272(X)", nullptr));
        pushButton_new->setText(QApplication::translate("MainWindowClass", "\346\226\260\345\273\272(N)", nullptr));
        pushButton_update->setText(QApplication::translate("MainWindowClass", "\346\233\264\346\226\260(U)", nullptr));
        pushButton_delete->setText(QApplication::translate("MainWindowClass", "\345\210\240\351\231\244(D)", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindowClass", "\350\201\224\347\263\273\344\272\272", nullptr));
        label_name->setText(QApplication::translate("MainWindowClass", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_number->setText(QApplication::translate("MainWindowClass", "<html><head/><body><p>\345\217\267\347\240\201\357\274\232</p></body></html>", nullptr));
        label_group->setText(QApplication::translate("MainWindowClass", "\347\276\244\347\273\204\357\274\232", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindowClass", "\346\234\252\345\210\206\347\273\204", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindowClass", "\345\220\214\344\272\213", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindowClass", "\346\234\213\345\217\213", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindowClass", "\345\256\266\344\272\272", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindowClass", "\345\220\214\345\255\246", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindowClass", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindowClass", "\345\217\267\347\240\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindowClass", "\347\273\204\345\210\253", nullptr));
        pushButton_clear->setText(QApplication::translate("MainWindowClass", "\346\270\205\351\231\244(C)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
