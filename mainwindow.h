#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
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

    void on_btn_close_einzelansicht_clicked();

    void on_btn_mail_plain_clicked();

    void on_actionMediendatei_hinzuf_gen_triggered();

    void on_btn_add_media_clicked();

    void on_btn_close_einzelansicht_3_clicked();

    void on_btn_close_einzelansicht_2_clicked();

    void on_btn_datei_waehlen_clicked();

    void on_btn_save_media_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
