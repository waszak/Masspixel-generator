/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 29. May 17:44:38 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QDial>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionOpen;
    QAction *actionSave_code;
    QAction *actionExit;
    QAction *actionSave;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter_2;
    QTextEdit *teCode;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QToolBox *tbPanel;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *lPreview;
    QCommandLinkButton *renderButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *lInfo;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label;
    QSpinBox *widthSpin;
    QLabel *label_2;
    QSpinBox *heightSpin;
    QSpacerItem *verticalSpacer_3;
    QFrame *line;
    QLabel *label_4;
    QPushButton *bkgColorButton;
    QLabel *label_5;
    QDial *maxSteps;
    QLCDNumber *lcdNumber;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *lPicture;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImage;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(874, 548);
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave_code = new QAction(MainWindowClass);
        actionSave_code->setObjectName(QString::fromUtf8("actionSave_code"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        splitter_2 = new QSplitter(tab);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        teCode = new QTextEdit(splitter_2);
        teCode->setObjectName(QString::fromUtf8("teCode"));
        teCode->setStyleSheet(QString::fromUtf8("background-color: rgb(63, 63, 63);\n"
"color: rgb(220, 220, 204);\n"
"selection-background-color: rgb(65,54,60);\n"
"selection-color: rgb(236,188,188);"));
        teCode->setFrameShape(QFrame::NoFrame);
        teCode->setFrameShadow(QFrame::Plain);
        splitter_2->addWidget(teCode);
        groupBox = new QGroupBox(splitter_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tbPanel = new QToolBox(groupBox);
        tbPanel->setObjectName(QString::fromUtf8("tbPanel"));
        tbPanel->setStyleSheet(QString::fromUtf8("#toolBox::tab:selected { font: bold; color: #4FA600;height: 26px;} /* selected tab */\n"
"#toolBox::tab:!selected { font: bold; color: rgb(85,85,84);height: 26px;} /* non-selected tab */\n"
"#toolBox{\n"
"border: 0px transparent;\n"
"}\n"
"\n"
"#toolBox::tab:QToolButton{\n"
"border: 1px transparent;\n"
"border-top-left-radius: 6px;\n"
"border-top-right-radius: 6px;\n"
"background-color: rgb(234, 234, 234); /* Button background color no need to write long code */\n"
"}"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 360, 377));
        verticalLayout_2 = new QVBoxLayout(page_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lPreview = new QLabel(page_4);
        lPreview->setObjectName(QString::fromUtf8("lPreview"));
        lPreview->setMinimumSize(QSize(180, 180));
        lPreview->setMaximumSize(QSize(15000, 180));
        lPreview->setStyleSheet(QString::fromUtf8(""));
        lPreview->setFrameShape(QFrame::StyledPanel);
        lPreview->setFrameShadow(QFrame::Plain);
        lPreview->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lPreview);

        renderButton = new QCommandLinkButton(page_4);
        renderButton->setObjectName(QString::fromUtf8("renderButton"));

        verticalLayout_2->addWidget(renderButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        lInfo = new QLabel(page_4);
        lInfo->setObjectName(QString::fromUtf8("lInfo"));

        verticalLayout_2->addWidget(lInfo);

        tbPanel->addItem(page_4, QString::fromUtf8("Render"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 158, 201));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label = new QLabel(page_2);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setScaledContents(true);

        gridLayout_2->addWidget(label, 3, 0, 1, 1);

        widthSpin = new QSpinBox(page_2);
        widthSpin->setObjectName(QString::fromUtf8("widthSpin"));
        widthSpin->setMinimum(10);
        widthSpin->setMaximum(1600);
        widthSpin->setValue(600);

        gridLayout_2->addWidget(widthSpin, 1, 4, 1, 1);

        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setScaledContents(true);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        heightSpin = new QSpinBox(page_2);
        heightSpin->setObjectName(QString::fromUtf8("heightSpin"));
        heightSpin->setMinimum(10);
        heightSpin->setMaximum(1200);
        heightSpin->setValue(320);

        gridLayout_2->addWidget(heightSpin, 3, 4, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 8, 0, 1, 1);

        line = new QFrame(page_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 4, 0, 1, 1);

        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        bkgColorButton = new QPushButton(page_2);
        bkgColorButton->setObjectName(QString::fromUtf8("bkgColorButton"));
        bkgColorButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        bkgColorButton->setAutoDefault(false);
        bkgColorButton->setFlat(false);

        gridLayout_2->addWidget(bkgColorButton, 5, 4, 1, 1);

        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 6, 0, 1, 1);

        maxSteps = new QDial(page_2);
        maxSteps->setObjectName(QString::fromUtf8("maxSteps"));
        maxSteps->setMinimum(1);
        maxSteps->setMaximum(200);
        maxSteps->setPageStep(10);
        maxSteps->setValue(64);
        maxSteps->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(maxSteps, 7, 0, 1, 1);

        lcdNumber = new QLCDNumber(page_2);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setNumDigits(3);
        lcdNumber->setProperty("intValue", QVariant(64));

        gridLayout_2->addWidget(lcdNumber, 7, 4, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        tbPanel->addItem(page_2, QString::fromUtf8("Raymarcher Settings"));

        verticalLayout_5->addWidget(tbPanel);

        splitter_2->addWidget(groupBox);

        horizontalLayout_2->addWidget(splitter_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea = new QScrollArea(tab_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::Box);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 98, 33));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lPicture = new QLabel(scrollAreaWidgetContents);
        lPicture->setObjectName(QString::fromUtf8("lPicture"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lPicture->sizePolicy().hasHeightForWidth());
        lPicture->setSizePolicy(sizePolicy1);
        lPicture->setAutoFillBackground(true);
        lPicture->setFrameShape(QFrame::StyledPanel);
        lPicture->setFrameShadow(QFrame::Plain);
        lPicture->setTextFormat(Qt::PlainText);
        lPicture->setScaledContents(false);
        lPicture->setIndent(0);

        verticalLayout->addWidget(lPicture);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 874, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuImage = new QMenu(menuBar);
        menuImage->setObjectName(QString::fromUtf8("menuImage"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuImage->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_code);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuImage->addAction(actionSave);

        retranslateUi(MainWindowClass);
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindowClass, SLOT(openCode()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindowClass, SLOT(saveImage()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindowClass, SLOT(close()));
        QObject::connect(actionSave_code, SIGNAL(triggered()), MainWindowClass, SLOT(saveCode()));
        QObject::connect(renderButton, SIGNAL(released()), MainWindowClass, SLOT(compileAndRun()));
        QObject::connect(bkgColorButton, SIGNAL(released()), MainWindowClass, SLOT(setBkgColor()));
        QObject::connect(maxSteps, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(teCode, SIGNAL(textChanged()), MainWindowClass, SLOT(startTimer()));

        tabWidget->setCurrentIndex(0);
        tbPanel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Sphere Marcher", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave_code->setText(QApplication::translate("MainWindowClass", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_code->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindowClass", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        teCode->setDocumentTitle(QString());
        groupBox->setTitle(QString());
        lPreview->setText(QString());
        renderButton->setText(QApplication::translate("MainWindowClass", "Render Scene", 0, QApplication::UnicodeUTF8));
        lInfo->setText(QString());
        tbPanel->setItemText(tbPanel->indexOf(page_4), QApplication::translate("MainWindowClass", "Render", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindowClass", "Render Size:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowClass", "Height:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindowClass", "Width:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindowClass", "Background color:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        bkgColorButton->setToolTip(QApplication::translate("MainWindowClass", "Background color, click to choose", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bkgColorButton->setText(QString());
        label_5->setText(QApplication::translate("MainWindowClass", "Max steps:", 0, QApplication::UnicodeUTF8));
        tbPanel->setItemText(tbPanel->indexOf(page_2), QApplication::translate("MainWindowClass", "Raymarcher Settings", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindowClass", "Scene Description Code", 0, QApplication::UnicodeUTF8));
        lPicture->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindowClass", "Rendered", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", 0, QApplication::UnicodeUTF8));
        menuImage->setTitle(QApplication::translate("MainWindowClass", "Render", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
