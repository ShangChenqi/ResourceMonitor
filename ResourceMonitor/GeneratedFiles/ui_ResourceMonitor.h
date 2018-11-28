/********************************************************************************
** Form generated from reading UI file 'ResourceMonitor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESOURCEMONITOR_H
#define UI_RESOURCEMONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_ResourceMonitorClass
{
public:
    QTabWidget *tabWidget;
    QWidget *simple;
    QWidget *widget;
    QWidget *widget_2;
    QLabel *label4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QWidget *detailed;
    QCustomPlot *widget_3;
    QLabel *label_down;
    QLabel *label_on;
    QLabel *labelDown;
    QLabel *labelOn;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *labelCpu;
    QLabel *label_4;
    QLabel *labelMemory;
    QWidget *setting;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *submit;
    QSpacerItem *horizontalSpacer;
    QPushButton *quit;
    QLabel *label5;
    QLabel *label6;
    QCheckBox *dataSave;
    QCheckBox *highDensity;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label7;
    QComboBox *cpuLine;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label8;
    QComboBox *memoryLine;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label9;
    QComboBox *downSpeedLine;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label10;
    QComboBox *onSpeedLine;

    void setupUi(QDialog *ResourceMonitorClass)
    {
        if (ResourceMonitorClass->objectName().isEmpty())
            ResourceMonitorClass->setObjectName(QStringLiteral("ResourceMonitorClass"));
        ResourceMonitorClass->resize(600, 402);
        tabWidget = new QTabWidget(ResourceMonitorClass);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 0, 601, 401));
        simple = new QWidget();
        simple->setObjectName(QStringLiteral("simple"));
        widget = new QWidget(simple);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 80, 150, 150));
        widget_2 = new QWidget(simple);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(350, 80, 150, 150));
        label4 = new QLabel(simple);
        label4->setObjectName(QStringLiteral("label4"));
        label4->setGeometry(QRect(290, 252, 291, 15));
        label4->setScaledContents(true);
        layoutWidget = new QWidget(simple);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 250, 191, 20));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label1 = new QLabel(layoutWidget);
        label1->setObjectName(QStringLiteral("label1"));

        horizontalLayout_2->addWidget(label1);

        label2 = new QLabel(layoutWidget);
        label2->setObjectName(QStringLiteral("label2"));

        horizontalLayout_2->addWidget(label2);

        label3 = new QLabel(layoutWidget);
        label3->setObjectName(QStringLiteral("label3"));

        horizontalLayout_2->addWidget(label3);

        tabWidget->addTab(simple, QString());
        detailed = new QWidget();
        detailed->setObjectName(QStringLiteral("detailed"));
        widget_3 = new QCustomPlot(detailed);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(10, 25, 581, 251));
        label_down = new QLabel(detailed);
        label_down->setObjectName(QStringLiteral("label_down"));
        label_down->setGeometry(QRect(160, 300, 30, 30));
        label_down->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/C:/Users/54628/Downloads/down.png")));
        label_down->setScaledContents(true);
        label_on = new QLabel(detailed);
        label_on->setObjectName(QStringLiteral("label_on"));
        label_on->setGeometry(QRect(350, 300, 30, 30));
        label_on->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/C:/Users/54628/Downloads/on.png")));
        label_on->setScaledContents(true);
        labelDown = new QLabel(detailed);
        labelDown->setObjectName(QStringLiteral("labelDown"));
        labelDown->setGeometry(QRect(340, 310, 91, 16));
        labelDown->setScaledContents(true);
        labelOn = new QLabel(detailed);
        labelOn->setObjectName(QStringLiteral("labelOn"));
        labelOn->setGeometry(QRect(470, 310, 111, 16));
        labelOn->setScaledContents(true);
        label = new QLabel(detailed);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 302, 30, 30));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/Resources/down.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(detailed);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(430, 302, 30, 30));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/Resources/on.png")));
        label_2->setScaledContents(true);
        label_3 = new QLabel(detailed);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(80, 302, 30, 30));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/Resources/cpu.png")));
        label_3->setScaledContents(true);
        labelCpu = new QLabel(detailed);
        labelCpu->setObjectName(QStringLiteral("labelCpu"));
        labelCpu->setGeometry(QRect(120, 310, 54, 12));
        label_4 = new QLabel(detailed);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setEnabled(true);
        label_4->setGeometry(QRect(190, 302, 30, 30));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/Resources/memory.png")));
        label_4->setScaledContents(true);
        labelMemory = new QLabel(detailed);
        labelMemory->setObjectName(QStringLiteral("labelMemory"));
        labelMemory->setGeometry(QRect(230, 310, 54, 12));
        tabWidget->addTab(detailed, QString());
        setting = new QWidget();
        setting->setObjectName(QStringLiteral("setting"));
        layoutWidget1 = new QWidget(setting);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(180, 310, 241, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        submit = new QPushButton(layoutWidget1);
        submit->setObjectName(QStringLiteral("submit"));

        horizontalLayout->addWidget(submit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        quit = new QPushButton(layoutWidget1);
        quit->setObjectName(QStringLiteral("quit"));

        horizontalLayout->addWidget(quit);

        label5 = new QLabel(setting);
        label5->setObjectName(QStringLiteral("label5"));
        label5->setGeometry(QRect(130, 30, 141, 21));
        label6 = new QLabel(setting);
        label6->setObjectName(QStringLiteral("label6"));
        label6->setGeometry(QRect(130, 140, 141, 21));
        dataSave = new QCheckBox(setting);
        dataSave->setObjectName(QStringLiteral("dataSave"));
        dataSave->setGeometry(QRect(160, 60, 221, 16));
        dataSave->setChecked(true);
        highDensity = new QCheckBox(setting);
        highDensity->setObjectName(QStringLiteral("highDensity"));
        highDensity->setGeometry(QRect(160, 100, 251, 16));
        layoutWidget2 = new QWidget(setting);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(84, 180, 201, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label7 = new QLabel(layoutWidget2);
        label7->setObjectName(QStringLiteral("label7"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label7->sizePolicy().hasHeightForWidth());
        label7->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label7);

        cpuLine = new QComboBox(layoutWidget2);
        cpuLine->setObjectName(QStringLiteral("cpuLine"));
        cpuLine->setMaxVisibleItems(10);

        horizontalLayout_3->addWidget(cpuLine);

        layoutWidget3 = new QWidget(setting);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(312, 180, 171, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label8 = new QLabel(layoutWidget3);
        label8->setObjectName(QStringLiteral("label8"));

        horizontalLayout_4->addWidget(label8);

        memoryLine = new QComboBox(layoutWidget3);
        memoryLine->setObjectName(QStringLiteral("memoryLine"));

        horizontalLayout_4->addWidget(memoryLine);

        layoutWidget4 = new QWidget(setting);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(76, 240, 211, 22));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label9 = new QLabel(layoutWidget4);
        label9->setObjectName(QStringLiteral("label9"));

        horizontalLayout_5->addWidget(label9);

        downSpeedLine = new QComboBox(layoutWidget4);
        downSpeedLine->setObjectName(QStringLiteral("downSpeedLine"));

        horizontalLayout_5->addWidget(downSpeedLine);

        layoutWidget5 = new QWidget(setting);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(304, 240, 181, 22));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label10 = new QLabel(layoutWidget5);
        label10->setObjectName(QStringLiteral("label10"));

        horizontalLayout_6->addWidget(label10);

        onSpeedLine = new QComboBox(layoutWidget5);
        onSpeedLine->setObjectName(QStringLiteral("onSpeedLine"));

        horizontalLayout_6->addWidget(onSpeedLine);

        tabWidget->addTab(setting, QString());

        retranslateUi(ResourceMonitorClass);

        tabWidget->setCurrentIndex(1);
        cpuLine->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ResourceMonitorClass);
    } // setupUi

    void retranslateUi(QDialog *ResourceMonitorClass)
    {
        ResourceMonitorClass->setWindowTitle(QApplication::translate("ResourceMonitorClass", "ResourceMonitor", Q_NULLPTR));
        label4->setText(QApplication::translate("ResourceMonitorClass", "TextLabel", Q_NULLPTR));
        label1->setText(QApplication::translate("ResourceMonitorClass", "Memory:", Q_NULLPTR));
        label2->setText(QApplication::translate("ResourceMonitorClass", "3.0", Q_NULLPTR));
        label3->setText(QApplication::translate("ResourceMonitorClass", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(simple), QApplication::translate("ResourceMonitorClass", "Tab 1", Q_NULLPTR));
        label_down->setText(QString());
        label_on->setText(QString());
        labelDown->setText(QApplication::translate("ResourceMonitorClass", "TextLabel", Q_NULLPTR));
        labelOn->setText(QApplication::translate("ResourceMonitorClass", "TextLabel", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        labelCpu->setText(QApplication::translate("ResourceMonitorClass", "TextLabel", Q_NULLPTR));
        label_4->setText(QString());
        labelMemory->setText(QApplication::translate("ResourceMonitorClass", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(detailed), QApplication::translate("ResourceMonitorClass", "\351\241\265", Q_NULLPTR));
        submit->setText(QApplication::translate("ResourceMonitorClass", "Submit", Q_NULLPTR));
        quit->setText(QApplication::translate("ResourceMonitorClass", "Reset", Q_NULLPTR));
        label5->setText(QApplication::translate("ResourceMonitorClass", "setting", Q_NULLPTR));
        label6->setText(QApplication::translate("ResourceMonitorClass", "setting2", Q_NULLPTR));
        dataSave->setText(QApplication::translate("ResourceMonitorClass", "Add data to file", Q_NULLPTR));
        highDensity->setText(QApplication::translate("ResourceMonitorClass", "Gride line high density display", Q_NULLPTR));
        label7->setText(QApplication::translate("ResourceMonitorClass", "Cpu line", Q_NULLPTR));
        label8->setText(QApplication::translate("ResourceMonitorClass", "Memory line", Q_NULLPTR));
        label9->setText(QApplication::translate("ResourceMonitorClass", "Down speed line", Q_NULLPTR));
        label10->setText(QApplication::translate("ResourceMonitorClass", "On speed line", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(setting), QApplication::translate("ResourceMonitorClass", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ResourceMonitorClass: public Ui_ResourceMonitorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESOURCEMONITOR_H
