/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pic;
    QPushButton *open;
    QPushButton *closeCam;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QComboBox *PortBox;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QPushButton *pushButton_sd;
    QPushButton *pushButton_sdz;
    QPushButton *pushButton_jd;
    QPushButton *pushButton_jdz;
    QLabel *QR1;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *QR2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QLabel *QR3;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QComboBox *PortBox_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QProgressBar *progressBar_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_dz1;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_dz1_2;
    QPushButton *pushButton_12;
    QLineEdit *lineEdit_5;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(975, 590);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(480, 110, 291, 321));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QStringLiteral(""));
        pic = new QPushButton(centralWidget);
        pic->setObjectName(QStringLiteral("pic"));
        pic->setGeometry(QRect(633, 12, 93, 28));
        open = new QPushButton(centralWidget);
        open->setObjectName(QStringLiteral("open"));
        open->setGeometry(QRect(433, 12, 93, 28));
        closeCam = new QPushButton(centralWidget);
        closeCam->setObjectName(QStringLiteral("closeCam"));
        closeCam->setGeometry(QRect(533, 12, 93, 28));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(325, 12, 101, 28));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(155, 15, 171, 21));
        PortBox = new QComboBox(centralWidget);
        PortBox->setObjectName(QStringLiteral("PortBox"));
        PortBox->setGeometry(QRect(0, 10, 87, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 10, 51, 28));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(190, 180, 271, 21));
        progressBar->setValue(24);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(190, 100, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(530, 100, 160, 22));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        pushButton_sd = new QPushButton(centralWidget);
        pushButton_sd->setObjectName(QStringLiteral("pushButton_sd"));
        pushButton_sd->setGeometry(QRect(30, 100, 41, 28));
        pushButton_sdz = new QPushButton(centralWidget);
        pushButton_sdz->setObjectName(QStringLiteral("pushButton_sdz"));
        pushButton_sdz->setGeometry(QRect(80, 100, 51, 28));
        pushButton_jd = new QPushButton(centralWidget);
        pushButton_jd->setObjectName(QStringLiteral("pushButton_jd"));
        pushButton_jd->setGeometry(QRect(420, 100, 41, 28));
        pushButton_jdz = new QPushButton(centralWidget);
        pushButton_jdz->setObjectName(QStringLiteral("pushButton_jdz"));
        pushButton_jdz->setGeometry(QRect(470, 100, 51, 28));
        QR1 = new QLabel(centralWidget);
        QR1->setObjectName(QStringLiteral("QR1"));
        QR1->setGeometry(QRect(-10, 210, 151, 101));
        QR1->setStyleSheet(QStringLiteral("background-color: rgb(83, 83, 83);"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(150, 220, 93, 28));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(150, 270, 93, 28));
        QR2 = new QLabel(centralWidget);
        QR2->setObjectName(QStringLiteral("QR2"));
        QR2->setGeometry(QRect(0, 340, 131, 61));
        QR2->setStyleSheet(QStringLiteral("background-color: rgb(83, 83, 83);"));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(150, 370, 93, 28));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(150, 340, 93, 28));
        QR3 = new QLabel(centralWidget);
        QR3->setObjectName(QStringLiteral("QR3"));
        QR3->setGeometry(QRect(-10, 440, 151, 101));
        QR3->setStyleSheet(QStringLiteral("background-color: rgb(83, 83, 83);"));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(150, 500, 93, 28));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(150, 450, 93, 28));
        PortBox_2 = new QComboBox(centralWidget);
        PortBox_2->setObjectName(QStringLiteral("PortBox_2"));
        PortBox_2->setGeometry(QRect(670, 50, 87, 31));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(700, 100, 51, 21));
        lineEdit_2->setAlignment(Qt::AlignCenter);
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(160, 190, 93, 28));
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(150, 310, 93, 28));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(160, 410, 93, 28));
        progressBar_2 = new QProgressBar(centralWidget);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setGeometry(QRect(370, 240, 271, 21));
        progressBar_2->setValue(24);
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(480, 330, 251, 21));
        pushButton_dz1 = new QPushButton(centralWidget);
        pushButton_dz1->setObjectName(QStringLiteral("pushButton_dz1"));
        pushButton_dz1->setGeometry(QRect(750, 330, 111, 28));
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(480, 370, 251, 21));
        pushButton_dz1_2 = new QPushButton(centralWidget);
        pushButton_dz1_2->setObjectName(QStringLiteral("pushButton_dz1_2"));
        pushButton_dz1_2->setGeometry(QRect(750, 370, 111, 28));
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(750, 410, 111, 28));
        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(610, 410, 121, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(530, 410, 72, 15));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(490, 300, 371, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 975, 26));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\213\215\347\205\247\345\271\263\345\217\260\346\216\247\345\210\266\350\275\257\344\273\266", nullptr));
        label->setText(QString());
        pic->setText(QApplication::translate("MainWindow", "\350\275\254\346\215\242", nullptr));
        open->setText(QApplication::translate("MainWindow", "\345\275\225\345\210\266", nullptr));
        closeCam->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\351\237\263\350\247\206\351\242\221\345\220\210\346\210\220", nullptr));
        lineEdit->setText(QApplication::translate("MainWindow", "tc2.png", nullptr));
        pushButton->setText(QString());
        pushButton_sd->setText(QApplication::translate("MainWindow", "\351\200\237\345\272\246", nullptr));
        pushButton_sdz->setText(QApplication::translate("MainWindow", "0", nullptr));
        pushButton_jd->setText(QApplication::translate("MainWindow", "\350\247\222\345\272\246", nullptr));
        pushButton_jdz->setText(QApplication::translate("MainWindow", "0", nullptr));
        QR1->setText(QString());
        pushButton_3->setText(QApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        QR2->setText(QString());
        pushButton_6->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        pushButton_5->setText(QApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
        QR3->setText(QString());
        pushButton_8->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        pushButton_7->setText(QApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
        lineEdit_2->setText(QApplication::translate("MainWindow", "0", nullptr));
        pushButton_9->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        pushButton_10->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        pushButton_11->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        pushButton_dz1->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\350\247\206\351\242\221\345\234\260\345\235\200", nullptr));
        lineEdit_4->setText(QString());
        pushButton_dz1_2->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\351\237\263\351\242\221\345\234\260\345\235\200", nullptr));
        pushButton_12->setText(QApplication::translate("MainWindow", "\345\220\210\345\271\266", nullptr));
        lineEdit_5->setText(QApplication::translate("MainWindow", "30", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\357\274\232", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
