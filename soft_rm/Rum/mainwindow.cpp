#include "stdafx.h"
#include "mainwindow.h"
#include "SyntaxHighlighter.hpp"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);

    sh = new sdSyntaxHighlighter(ui.teCode->document());
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderPreview()));
    autoPreview = true;
}

MainWindow::~MainWindow()
{
    if (sh != nullptr)
        delete sh;
    if (timer != nullptr)
    {
        timer->stop();
        delete timer;
    }
}

void MainWindow::compileAndRun()
{
    timer->stop();

    statusBar()->showMessage(tr("Parsing..."));
    if (proxy.Compile(ui.teCode->toPlainText()))
    {
        statusBar()->showMessage(tr("Rendering..."));

        proxy.SetMaxSteps(ui.maxSteps->value());

        ui.lInfo->setText("Scene description is valid.");
        ui.lInfo->setStyleSheet("QLabel {color: green; }");

        uint w = ui.widthSpin->value();
        uint h = ui.heightSpin->value();
        ui.lPicture->setPixmap(QPixmap::fromImage(proxy.Render(w,h)));

        statusBar()->showMessage(tr("Rendered scene."), 2000);        
    }
    else
    {
        ui.lInfo->setText(proxy.LastError());
        ui.lInfo->setStyleSheet("QLabel {color: red; }");

        statusBar()->showMessage(tr("Error while parsing."), 2000);
    }
}

void MainWindow::openCode()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Scene Description file (*.sdf);;All files (*.*)"));
    if (file != tr(""))
    {
        QFile qfile(file);

        if (!qfile.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, tr("Sphere Marcher"), tr("Cannot read file %1:\n %2").arg(file).arg(qfile.errorString()));
            statusBar()->showMessage(tr("Opening file failed :( %2").arg(qfile.errorString()), 2000);            
        }
        else
        {
            QTextStream content(&qfile);
            
            ui.teCode->setText(content.readAll());
            
            qfile.close();

            statusBar()->showMessage(tr("Opened file %1.").arg(file), 2000);
        }   
    }
}

void MainWindow::saveCode()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save"), "", tr("Scene Description file (*.sdf);;All files (*.*)"));
    ui.lInfo->setText(file);
    if (file != "")
    {
        QFile qfile(file);

        if (!qfile.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this, tr("Sphere Marcher"), tr("Cannot write file %1:\n %2").arg(file).arg(qfile.errorString()));
            statusBar()->showMessage(tr("Writing file failed :( %2").arg(qfile.errorString()), 2000);            
        }
        else
        {
            QTextStream content(&qfile);

            content << ui.teCode->toPlainText();

            qfile.close();

            statusBar()->showMessage(tr("Wrote to file %1.").arg(file), 2000);
        }   
    }
}

void MainWindow::saveImage()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save image"), "", tr("png (*.png);;jpg (*.jpg);;All files (*.*)"));
    if (file != tr(""))
    {
        ui.lPicture->pixmap()->save(file);
        statusBar()->showMessage(tr("Saved image to %1.").arg(file), 2000);
    }
}

void MainWindow::setBkgColor()
{
    QColor color = QColorDialog::getColor();
    const QString COLOR_STYLE("QPushButton {background-color : %1;}");
    ui.bkgColorButton->setStyleSheet(COLOR_STYLE.arg(color.name()));
    ui.teCode->append(COLOR_STYLE.arg(color.name()));
}

void MainWindow::startTimer()
{
    timer->stop();
    timer->start(2550);
}

void MainWindow::renderPreview()
{
    timer->stop();

    statusBar()->showMessage(tr("Parsing..."));
    if (proxy.Compile(ui.teCode->toPlainText()))
    {
        statusBar()->showMessage(tr("Rendering preview..."));

        proxy.SetMaxSteps(64);

        ui.lInfo->setText("Scene description is valid.");
        ui.lInfo->setStyleSheet("QLabel {color: green; }");

        ui.lPicture->setScaledContents(true);
        ui.lPreview->setPixmap(QPixmap::fromImage(proxy.Render(300,160)));

        statusBar()->showMessage(tr("Rendered scene."), 2000);        
    }
    else
    {
        ui.lInfo->setText(proxy.LastError());
        ui.lInfo->setStyleSheet("QLabel {color: red; }");
        statusBar()->showMessage(tr("Error while parsing."), 2000);
    }
}