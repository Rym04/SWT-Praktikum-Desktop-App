#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include <QList>
#include "smtp.h"
#include "../headers/katalogeintrag.h"
#include "../headers/sqlconnector.h"
#include "../headers/autor.h"
#include "QDateEdit"
#include "QDateTime"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAusleihen_triggered();

    void on_actionKatalog_triggered();

    void on_actionNeuer_Katalogeintrag_triggered();

    void on_actionHome_triggered();

    void on_actionE_Mail_triggered();

    void sendMail();

    void mailSent(QString);

    void browse();

    void browseButtonClicked();

    void addNewButtonClicked();

    void updateButtonClicked();

    void deleteButtonClicked();

    void findButtonClicked();

    void findButtonClicked_2();

    void findButtonClicked_3();

    void prevButtonClicked();

    void nextButtonClicked();

    void on_btn_datei_waehlen_media_clicked();

    void on_actionMediendatei_hinzuf_gen_triggered();

    void on_btn_save_media_2_clicked();

    void on_updateButton_clicked();

private:
    Ui::MainWindow *ui;
    QStringList files;
    Katalogeintrag currentKatalogeintrag;
    int maxKatalogeintrag;
    int maxAutorid;
    SQLController *sqlController;
    QList<Katalogeintrag> list;
    int totalRecord;
    int currentIndex;
    void populateRecord();
    void populateUI();
};

#endif // MAINWINDOW_H
