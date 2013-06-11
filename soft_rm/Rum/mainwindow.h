#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

#include "Proxy.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

private slots:
    void compileAndRun();
    void openCode();
    void saveCode();
    void saveImage();
    void setBkgColor();
    void startTimer();
    void renderPreview();

private:
    Ui::MainWindowClass ui;
    Proxy proxy;
    QSyntaxHighlighter *sh;
    QTimer* timer;
    bool autoPreview;
};

#endif // MAINWINDOW_H
