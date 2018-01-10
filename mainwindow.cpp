#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_media.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

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
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btn_close_einzelansicht_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_actionMediendatei_hinzuf_gen_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btn_mail_plain_clicked()
{

}


void MainWindow::on_btn_datei_waehlen_clicked()
{
    QString media_path;
    QFileDialogTester test;
    media_path = test.openFile();
    //Add media path to doc_id
}

void MainWindow::on_btn_save_media_clicked()
{

}
