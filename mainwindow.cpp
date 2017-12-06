#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAusleihen_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionKatalog_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionNeuer_Katalogeintrag_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}