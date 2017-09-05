/********************************************************************************
** Form generated from reading UI file 'plotdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDIALOG_H
#define UI_PLOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PlotDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_7;
    QLabel *lblStartTime;
    QLabel *lblEndTime;
    QLabel *lblTimeDifference;
    QLabel *lblStartValue;
    QLabel *lblEndValue;
    QLabel *lblValueDifference;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *lblGradient;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSavePDF;
    QPushButton *btnSavePNG;
    QPushButton *btnLoadFile;
    QPushButton *btnAddFile;
    QCheckBox *chkTracer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PlotDialog)
    {
        if (PlotDialog->objectName().isEmpty())
            PlotDialog->setObjectName(QStringLiteral("PlotDialog"));
        PlotDialog->resize(800, 640);
        verticalLayout_2 = new QVBoxLayout(PlotDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);

        verticalLayout_2->addLayout(verticalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(9, 0, 9, -1);
        label_2 = new QLabel(PlotDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label = new QLabel(PlotDialog);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        label_7 = new QLabel(PlotDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 0, 2, 1, 1);

        lblStartTime = new QLabel(PlotDialog);
        lblStartTime->setObjectName(QStringLiteral("lblStartTime"));
        sizePolicy.setHeightForWidth(lblStartTime->sizePolicy().hasHeightForWidth());
        lblStartTime->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lblStartTime, 1, 0, 1, 1);

        lblEndTime = new QLabel(PlotDialog);
        lblEndTime->setObjectName(QStringLiteral("lblEndTime"));
        sizePolicy.setHeightForWidth(lblEndTime->sizePolicy().hasHeightForWidth());
        lblEndTime->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lblEndTime, 1, 1, 1, 1);

        lblTimeDifference = new QLabel(PlotDialog);
        lblTimeDifference->setObjectName(QStringLiteral("lblTimeDifference"));
        sizePolicy.setHeightForWidth(lblTimeDifference->sizePolicy().hasHeightForWidth());
        lblTimeDifference->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lblTimeDifference, 1, 2, 1, 1);

        lblStartValue = new QLabel(PlotDialog);
        lblStartValue->setObjectName(QStringLiteral("lblStartValue"));
        sizePolicy.setHeightForWidth(lblStartValue->sizePolicy().hasHeightForWidth());
        lblStartValue->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lblStartValue, 2, 0, 1, 1);

        lblEndValue = new QLabel(PlotDialog);
        lblEndValue->setObjectName(QStringLiteral("lblEndValue"));
        sizePolicy.setHeightForWidth(lblEndValue->sizePolicy().hasHeightForWidth());
        lblEndValue->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lblEndValue, 2, 1, 1, 1);

        lblValueDifference = new QLabel(PlotDialog);
        lblValueDifference->setObjectName(QStringLiteral("lblValueDifference"));
        sizePolicy.setHeightForWidth(lblValueDifference->sizePolicy().hasHeightForWidth());
        lblValueDifference->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lblValueDifference, 2, 2, 1, 1);

        label_11 = new QLabel(PlotDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_11, 3, 0, 1, 1);

        label_12 = new QLabel(PlotDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_12, 3, 1, 1, 1);

        lblGradient = new QLabel(PlotDialog);
        lblGradient->setObjectName(QStringLiteral("lblGradient"));
        sizePolicy.setHeightForWidth(lblGradient->sizePolicy().hasHeightForWidth());
        lblGradient->setSizePolicy(sizePolicy);
        lblGradient->setFont(font);

        gridLayout->addWidget(lblGradient, 3, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(9, -1, 9, -1);
        btnSavePDF = new QPushButton(PlotDialog);
        btnSavePDF->setObjectName(QStringLiteral("btnSavePDF"));

        horizontalLayout->addWidget(btnSavePDF);

        btnSavePNG = new QPushButton(PlotDialog);
        btnSavePNG->setObjectName(QStringLiteral("btnSavePNG"));

        horizontalLayout->addWidget(btnSavePNG);

        btnLoadFile = new QPushButton(PlotDialog);
        btnLoadFile->setObjectName(QStringLiteral("btnLoadFile"));

        horizontalLayout->addWidget(btnLoadFile);

        btnAddFile = new QPushButton(PlotDialog);
        btnAddFile->setObjectName(QStringLiteral("btnAddFile"));

        horizontalLayout->addWidget(btnAddFile);

        chkTracer = new QCheckBox(PlotDialog);
        chkTracer->setObjectName(QStringLiteral("chkTracer"));

        horizontalLayout->addWidget(chkTracer);

        buttonBox = new QDialogButtonBox(PlotDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        horizontalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(PlotDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PlotDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PlotDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PlotDialog);
    } // setupUi

    void retranslateUi(QDialog *PlotDialog)
    {
        PlotDialog->setWindowTitle(QApplication::translate("PlotDialog", "Dialog", 0));
        label_2->setText(QApplication::translate("PlotDialog", "Start Point", 0));
        label->setText(QApplication::translate("PlotDialog", "End Point", 0));
        label_7->setText(QApplication::translate("PlotDialog", "Gradient", 0));
        lblStartTime->setText(QString());
        lblEndTime->setText(QString());
        lblTimeDifference->setText(QString());
        lblStartValue->setText(QString());
        lblEndValue->setText(QString());
        lblValueDifference->setText(QString());
        label_11->setText(QString());
        label_12->setText(QString());
        lblGradient->setText(QString());
        btnSavePDF->setText(QApplication::translate("PlotDialog", "Save PDF", 0));
        btnSavePNG->setText(QApplication::translate("PlotDialog", "Save PNG", 0));
        btnLoadFile->setText(QApplication::translate("PlotDialog", "Load CSV", 0));
        btnAddFile->setText(QApplication::translate("PlotDialog", "Add CSV", 0));
        chkTracer->setText(QApplication::translate("PlotDialog", "Show Tracer", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotDialog: public Ui_PlotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDIALOG_H
