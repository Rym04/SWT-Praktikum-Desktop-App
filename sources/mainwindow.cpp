#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //SMTP Button
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    //Konstruktor SQL Controller
    sqlController=new SQLController();

    //Katalogeintrag editieren Button
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
    connect(ui->prevButton, SIGNAL(clicked()), this, SLOT(prevButtonClicked()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(updateButtonClicked()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    connect(ui->addNewButton, SIGNAL(clicked()), this, SLOT(addNewButtonClicked()));
    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(findButtonClicked()));
    connect(ui->findButton_2, SIGNAL(clicked()), this, SLOT(findButtonClicked_2()));
    connect(ui->findButton_3, SIGNAL(clicked()), this, SLOT(findButtonClicked_3()));

    //Ausblenden bestimmter LineEdits
    ui->dokumentidLineEdit->setEnabled(false);
    ui->dokumentidLineEdit_2->setEnabled(false);
    ui->aenderungsdatumLineEdit->setEnabled(false);
    ui->aenderungsdatumLineEdit_2->setEnabled(false);
    ui->autoridLineEdit_2->setEnabled(false);

    //Katalogeintrag editieren füllen
    browseButtonClicked();
}
//Destruktor vom MainWindow
MainWindow::~MainWindow()
{
    sqlController->closeConnection();
    delete sqlController;
    delete ui;
}
// Screen: Katalogeintrag editieren
// UI mit Inhalt füllen
void MainWindow::populateUI()
{
   ui->dokumentidLineEdit->setText(QString::number(currentKatalogeintrag.getdokumentId()));
   ui->jahrLineEdit->setText(QString::number(currentKatalogeintrag.getjahr()));
   ui->revisionLineEdit->setText(QString::number(currentKatalogeintrag.getrevision()));
   ui->buchbandLineEdit->setText(QString::number(currentKatalogeintrag.getbuchband()));
   ui->auflageLineEdit->setText(QString::number(currentKatalogeintrag.getauflage()));
   ui->zustandLineEdit->setText(QString::number(currentKatalogeintrag.getzustand()));
   ui->copyrightLineEdit->setText(currentKatalogeintrag.getcopyright());
   ui->dokumentartLineEdit->setText(currentKatalogeintrag.getdokumentart());
   ui->zeitschriftLineEdit->setText(currentKatalogeintrag.getzeitschrift());
   ui->erscheinungsortLineEdit->setText(currentKatalogeintrag.geterscheinungsort());
   ui->konferenzLineEdit->setText(currentKatalogeintrag.getkonferenz());
   ui->verlagLineEdit->setText(currentKatalogeintrag.getverlag());
   ui->seitenLineEdit->setText(currentKatalogeintrag.getseiten());
   ui->bestandLineEdit->setText(QString::number(currentKatalogeintrag.getbestand()));
   ui->titelsammelbandLineEdit->setText(currentKatalogeintrag.gettitelSammelband());
   ui->aenderungsdatumLineEdit->setText(currentKatalogeintrag.getaenderungsdatum());
   ui->titelLineEdit->setText(currentKatalogeintrag.gettitel());
   ui->untertitelLineEdit->setText(currentKatalogeintrag.getuntertitel());
   ui->beschreibungLineEdit->setText(currentKatalogeintrag.getbeschreibung());
   ui->notizenLineEdit->setText(currentKatalogeintrag.getnotizen());
   ui->kommentarLineEdit->setText(currentKatalogeintrag.getkommentar());
   ui->totalCountLineEdit->setText(QString::number(totalRecord));
   ui->countLineEdit->setText(QString::number(currentIndex+1));
   ui->autorLineEdit->setText(sqlController->anzeigenAutor(currentKatalogeintrag.getdokumentId()));
   ui->dokumentidLineEdit_2->setText(QString::number(maxKatalogeintrag));
   ui->autoridLineEdit_2->setText(QString::number(maxAutorid));
}
//Datensatz X von Y, Navigation von den Datensätzen
void MainWindow::populateRecord()
{
   currentIndex=ui->countLineEdit->text().toInt()-1;
   if(totalRecord!=0 && currentIndex < totalRecord){
      currentKatalogeintrag=list.at(currentIndex);
      populateUI();
   }
}
//UI mit Inhalt füllen, Button Zurücksetzen der Datensätze
void MainWindow::browseButtonClicked()
{
   maxKatalogeintrag=sqlController->maxKatalogeintrag();
   maxAutorid=sqlController->maxAutorid();
   list=sqlController->anzeigenKatalogeintrag();
   totalRecord=list.size();
   if(totalRecord!=0){
      currentIndex=0;
      currentKatalogeintrag=list.at(currentIndex);
      populateUI();
      ui->nextButton->setEnabled(true);
      ui->prevButton->setEnabled(true);
   }
}
//Button Datensatz neu hinzufügen
void MainWindow::addNewButtonClicked()
{
   Katalogeintrag k;
   k.setdokumentId(ui->dokumentidLineEdit_2->text().toInt());
   k.setjahr(ui->jahrLineEdit_2->text().toInt());
   k.setrevision(ui->revisionLineEdit_2->text().toInt());
   k.setbuchband(ui->buchbandLineEdit_2->text().toInt());
   k.setauflage(ui->auflageLineEdit_2->text().toInt());
   k.setzustand(ui->zustandLineEdit_2->text().toInt());
   k.setcopyright(ui->copyrightLineEdit_2->text());
   k.setdokumentart(ui->dokumentartLineEdit_2->text());
   k.setzeitschrift(ui->zeitschriftLineEdit_2->text());
   k.seterscheinungsort(ui->erscheinungsortLineEdit_2->text());
   k.setkonferenz(ui->konferenzLineEdit_2->text());
   k.setverlag(ui->verlagLineEdit_2->text());
   k.setseiten(ui->seitenLineEdit_2->text());
   k.setbestand(ui->bestandLineEdit_2->text().toInt());
   k.settitelSammelband(ui->titelsammelbandLineEdit_2->text());
   k.setaenderungsdatum(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
   k.settitel(ui->titelLineEdit_2->text());
   k.setuntertitel(ui->untertitelLineEdit_2->text());
   k.setbeschreibung(ui->beschreibungLineEdit_2->text());
   k.setnotizen(ui->notizenLineEdit_2->text());
   k.setkommentar(ui->kommentarLineEdit_2->text());
   int result=sqlController->hinzufuegenKatalogeintrag(k);
   if(result==1)
      QMessageBox::information(this, tr("Neuer Katalogeintrag"),tr("Der Katalogeintrag wurde hinzugefügt"),QMessageBox::Ok );
   else
      QMessageBox::warning(this, tr("Neuer Katalogeintrag"),tr("Der Katalogeintrag wurde nicht hinzugefügt"),QMessageBox::Ok );

   //Autor hinzufuegen falls nicht vorhanden
   Autor a;
   a.setautor(ui->autorLineEdit_2->text());
   sqlController->hinzufuegenAutor(a);

   //DokumentAutor hinzufuegen falls nicht vorhanden
   k.setdokumentId(ui->dokumentidLineEdit_2->text().toInt());
   a.setautorId(ui->autoridLineEdit_2->text().toInt());
   sqlController->hinzufuegenKatalogeintragAutor(k,a);

   browseButtonClicked();
}
//Button Eintrag ändern
void MainWindow::updateButtonClicked()
{
   Katalogeintrag k;
   k.setdokumentId(ui->dokumentidLineEdit->text().toInt());
   k.setjahr(ui->jahrLineEdit->text().toInt());
   k.setrevision(ui->revisionLineEdit->text().toInt());
   k.setbuchband(ui->buchbandLineEdit->text().toInt());
   k.setauflage(ui->auflageLineEdit->text().toInt());
   k.setzustand(ui->zustandLineEdit->text().toInt());
   k.setcopyright(ui->copyrightLineEdit->text());
   k.setdokumentart(ui->dokumentartLineEdit->text());
   k.setzeitschrift(ui->zeitschriftLineEdit->text());
   k.seterscheinungsort(ui->erscheinungsortLineEdit->text());
   k.setkonferenz(ui->konferenzLineEdit->text());
   k.setverlag(ui->verlagLineEdit->text());
   k.setseiten(ui->seitenLineEdit->text());
   k.setbestand(ui->bestandLineEdit->text().toInt());
   k.settitelSammelband(ui->titelsammelbandLineEdit->text());
   k.setaenderungsdatum(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
   k.settitel(ui->titelLineEdit->text());
   k.setuntertitel(ui->untertitelLineEdit->text());
   k.setbeschreibung(ui->beschreibungLineEdit->text());
   k.setnotizen(ui->notizenLineEdit->text());
   k.setkommentar(ui->kommentarLineEdit->text());
   int result=sqlController->editierenKatalogeintrag(k);
   if(result==0)
      QMessageBox::information(this, tr("Katalogeintrag geändert"),tr("Der Katalogeintrag wurde erfolgreich geändert"),QMessageBox::Ok );
   else
      QMessageBox::warning(this, tr("Katalogeintrag nicht geändert"),tr("Der Katalogeintrag wurde nicht geändert!"),QMessageBox::Ok );
   browseButtonClicked();
}
//Button Eintrag löschen
void MainWindow::deleteButtonClicked()
{
   int result=sqlController->loeschenKatalogeintrag(ui->dokumentidLineEdit->text().toInt());
   if(result==1)
      QMessageBox::information(this, tr("Katalogeintrag gelöscht"),tr("Der Katalogeintrag wurde erfolgreich gelöscht"),QMessageBox::Ok );
   else
      QMessageBox::warning(this, tr("Katalogeintrag nicht gelöscht"),
         tr("Der Katalogeintrag wurde nicht gelöscht!"),QMessageBox::Ok );
   browseButtonClicked();
}
//Button Suchen nach ID
void MainWindow::findButtonClicked()
{
   list=sqlController->suchenKatalogeintragbyid(ui->dokumentidFindLineEdit->text().toInt());
   totalRecord=list.size();
   if(totalRecord!=0){
      currentIndex=0;
      currentKatalogeintrag=list.at(currentIndex);
      populateUI();
      ui->nextButton->setEnabled(true);
      ui->prevButton->setEnabled(true);
   }
   else {
       QMessageBox::warning(this, tr("Suche erfolgslos"),
          tr("Bei der Suche wurden keine Einträge gefunden"),QMessageBox::Ok );
       browseButtonClicked();
   }
}
//Button Suchen nach Titel
void MainWindow::findButtonClicked_2()
{
   list=sqlController->suchenKatalogeintragbytitel(ui->titelFindLineEdit->text());
   totalRecord=list.size();
   if(totalRecord!=0){
      currentIndex=0;
      currentKatalogeintrag=list.at(currentIndex);
      populateUI();
      ui->nextButton->setEnabled(true);
      ui->prevButton->setEnabled(true);
   }
   else {
       QMessageBox::warning(this, tr("Suche erfolgslos"),
          tr("Bei der Suche wurden keine Einträge gefunden"),QMessageBox::Ok );
       browseButtonClicked();
   }
}
//Button Suchen nach Autor
void MainWindow::findButtonClicked_3()
{
   list=sqlController->suchenKatalogeintragbyautor(ui->autorFindLineEdit->text());
   totalRecord=list.size();
   if(totalRecord!=0){
      currentIndex=0;
      currentKatalogeintrag=list.at(currentIndex);
      populateUI();
      ui->nextButton->setEnabled(true);
      ui->prevButton->setEnabled(true);
   }
   else {
       QMessageBox::warning(this, tr("Suche erfolgslos"),
          tr("Bei der Suche wurden keine Einträge gefunden"),QMessageBox::Ok );
       browseButtonClicked();
   }
}
//Button Zurück um zwischen den Datensätzen zu navigieren
void MainWindow::prevButtonClicked()
{
   currentIndex--;
   if(currentIndex<0)
      currentIndex=totalRecord-1;
   ui->countLineEdit->setText(QString::number(currentIndex+1));
   populateRecord();
}
//Button Nächster um zwischen den Datensätzen zu navigieren
void MainWindow::nextButtonClicked()
{
   currentIndex++;
   if(currentIndex>=totalRecord)
      currentIndex=0;
   ui->countLineEdit->setText
      (QString::number(currentIndex+1));
   populateRecord();
}
// Screen Katalogeinträge editieren


// SMTP Funktionen
// Anhaenge hinzufuegen
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}
/* Mail Senden */
void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
/* Mail gesendet */
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "QT SMTP" ), tr( "Nachricht gesendet!\n\n" ) );
}
/* Mail Funktionen ENDE */

/* MainWindow Funktionen START */
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

void MainWindow::on_actionE_Mail_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}
/* MainWindow Funktionen ENDE */
