#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QString>

#include "smtp.h"
#include "bearbeiter.h"
#include "katalogeintrag.h"
#include "add_media.h"
#include "sqlconnector.h"
#include "person.h"
#include "autor.h"

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
    void on_loadpushButton_clicked();

    void on_actionHome_triggered();

    void on_actionBestellungen_triggered();

    void on_durchsuchenpushButton_clicked();

    void slotSelectionChangeHome(const QItemSelection &, const QItemSelection &);

    void slotSelectionChange(const QItemSelection &, const QItemSelection &);

    void on_actionNeuer_Katalogeintrag_triggered();

    void on_addNewButton_clicked();

    void on_autorpushButton_clicked();

    void on_pushButton_clicked();

    void on_actionKatalogeintrag_editieren_triggered();

    void browseButtonClicked();

    void on_prevButton_clicked();

    void on_nextButton_clicked();

    void on_editierenfindButton_clicked();

    void on_editierenfindButton_2_clicked();

    void on_editierenfindButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_updateButton_clicked();

    void on_deleteButton_clicked();

    void on_actionKatalog_durchsuchen_triggered();

    void on_btn_search_suchendoc_clicked();

    void on_pushButtonSpeichern_clicked();

    void on_pushButtonBNeuerBearbeiter_clicked();

    void on_actionBearbeiter_in_triggered();

    void browseButtonClicked2();

    void populateUI2();

    void on_pushButton_4_clicked();

    void on_clearpushButton_clicked();

    void on_actionMediendatei_hinzuf_gen_triggered();

    void on_btn_datei_waehlen_media_clicked();

    void on_btn_save_media_2_clicked();

    void on_actionE_Mail_triggered();

    void sendMail();

    void mailSent(QString);

    void browse();

    void onEmail();


private:
    Ui::MainWindow *ui;
    Bearbeiter *bcontroller;
    Bearbeiter currentBearbeiter;
    QList<Bearbeiter> list2;
    Person currentPerson;
    QList<Person> list3;
    Katalogeintrag currentKatalogeintrag;
    QList<Katalogeintrag> list;
    int totalRecord;
    int currentIndex;
    void populateRecord();
    void populateUI();
    QStringList files;
};

#endif // MAINWINDOW_H
