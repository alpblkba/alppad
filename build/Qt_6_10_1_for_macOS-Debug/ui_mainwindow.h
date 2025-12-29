/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "noteslistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *newButton;
    QPushButton *delButton;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    NotesListWidget *notesListWidget;
    QTextEdit *textEdit;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1430, 902);
        verticalLayout = new QVBoxLayout(MainWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        newButton = new QPushButton(MainWindow);
        newButton->setObjectName("newButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/new.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        newButton->setIcon(icon);
        newButton->setIconSize(QSize(40, 40));
        newButton->setFlat(true);

        horizontalLayout->addWidget(newButton);

        delButton = new QPushButton(MainWindow);
        delButton->setObjectName("delButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/delete.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        delButton->setIcon(icon1);
        delButton->setIconSize(QSize(40, 40));
        delButton->setFlat(true);

        horizontalLayout->addWidget(delButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(MainWindow);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        splitter->setChildrenCollapsible(false);
        notesListWidget = new NotesListWidget(splitter);
        notesListWidget->setObjectName("notesListWidget");
        splitter->addWidget(notesListWidget);
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName("textEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMinimumSize(QSize(350, 350));
        textEdit->setFrameShape(QFrame::Shape::NoFrame);
        splitter->addWidget(textEdit);

        verticalLayout->addWidget(splitter);

        verticalLayout->setStretch(1, 1);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "alppad", nullptr));
        newButton->setText(QString());
        delButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
