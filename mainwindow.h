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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
