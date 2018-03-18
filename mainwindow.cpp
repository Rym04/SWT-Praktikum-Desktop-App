#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Signal Slot Connect
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    //Ausblenden bestimmter LineEdits
    ui->dokumentidLineEdit->setEnabled(false);
    ui->aenderungsdatumLineEdit->setEnabled(false);
    ui->dokumentidLineEdit_2->setEnabled(false);
    ui->aenderungsdatumLineEdit_2->setEnabled(false);
    ui->lineEditBId->setEnabled(false);

    //Konstruktor Bearbeiter
    bcontroller=new Bearbeiter();

    //Aufruf um das UI zu füllen
    MainWindow::populateUI();
    browseButtonClicked();

    //Screen Bearbeiter vorladen
    list2=bcontroller->anzeigenBearbeiter2();
    list3=bcontroller->anzeigenPerson();

    //Screen Home bei Start füllen
    on_loadpushButton_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete bcontroller;
}

//Toolbar START
void MainWindow::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    //Screen Home bei Wechsel füllen
    on_loadpushButton_clicked();
}

void MainWindow::on_actionBestellungen_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionNeuer_Katalogeintrag_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionKatalogeintrag_editieren_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
    browseButtonClicked();
}
void MainWindow::on_actionKatalog_durchsuchen_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_actionBearbeiter_in_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
    browseButtonClicked2();
    ui->comboBoxBAuswaehlen->setModel(bcontroller->anzeigenBearbeiter());
}
void MainWindow::on_actionMediendatei_hinzuf_gen_triggered()
{
    ui->stackedWidget->setCurrentIndex(6);
}
void MainWindow::on_actionE_Mail_triggered()
{
    ui->stackedWidget->setCurrentIndex(7);
    onEmail();
}


//Toolbar ENDE

//Allgemeine Funktionen START
void MainWindow::populateUI()
{
    //Screen Neuer Katalogeintrag
    ui->dokumentidLineEdit->setText(QString::number(bcontroller->maxKatalogeintrag()));

    //Screen Katalogeintrag editieren
    ui->totalCountLineEdit->setText(QString::number(totalRecord));
    ui->countLineEdit->setText(QString::number(currentIndex+1));
    ui->dokumentidLineEdit_2->setText(QString::number(currentKatalogeintrag.dokumentId));
    ui->jahrLineEdit_2->setText(QString::number(currentKatalogeintrag.jahr));
    ui->revisionLineEdit_2->setText(QString::number(currentKatalogeintrag.revision));
    ui->buchbandLineEdit_2->setText(QString::number(currentKatalogeintrag.buchband));
    ui->auflageLineEdit_2->setText(QString::number(currentKatalogeintrag.auflage));
    ui->zustandLineEdit_2->setText(QString::number(currentKatalogeintrag.zustand));
    ui->copyrightLineEdit_2->setText(currentKatalogeintrag.copyright);
    ui->dokumentartLineEdit_2->setText(currentKatalogeintrag.dokumentart);
    ui->zeitschriftLineEdit_2->setText(currentKatalogeintrag.zeitschrift);
    ui->erscheinungsortLineEdit_2->setText(currentKatalogeintrag.erscheinungsort);
    ui->konferenzLineEdit_2->setText(currentKatalogeintrag.konferenz);
    ui->verlagLineEdit_2->setText(currentKatalogeintrag.verlag);
    ui->seitenLineEdit_2->setText(currentKatalogeintrag.seiten);
    ui->bestandLineEdit_2->setText(QString::number(currentKatalogeintrag.bestand));
    ui->titelsammelbandLineEdit_2->setText(currentKatalogeintrag.titelSammelband);
    ui->aenderungsdatumLineEdit_2->setText(currentKatalogeintrag.aenderungsdatum);
    ui->titelLineEdit_2->setText(currentKatalogeintrag.titel);
    ui->untertitelLineEdit_2->setText(currentKatalogeintrag.untertitel);
    ui->beschreibungLineEdit_2->setText(currentKatalogeintrag.beschreibung);
    ui->notizenLineEdit_2->setText(currentKatalogeintrag.notizen);
    ui->kommentarLineEdit_2->setText(currentKatalogeintrag.kommentar);
    ui->autorlistWidget_2->clear();
    ui->autorlistWidget_2->addItems(bcontroller->anzeigenAutor2(ui->dokumentidLineEdit_2->text().toInt()));
}
void MainWindow::populateUI2()
{
    //Screen Bearbeiter
    //ui->comboBoxBAuswaehlen->setModel(bcontroller->anzeigenBearbeiter());
    ui->lineEditBId->setText(QString::number(currentBearbeiter.bearbeiterId));
    ui->lineEditBLogin->setText(currentBearbeiter.benutzername);
    ui->lineEditBEmailSignatur->setText(currentBearbeiter.emailSignatur);
    ui->lineEditBAnrede->setText(currentPerson.anrede);
    ui->lineEditBAkadGrad->setText(currentPerson.akademischerGrad);
    ui->lineEditBVorname->setText(currentPerson.vorname);
    ui->lineEditBNachname->setText(currentPerson.nachname);
    ui->lineEditBInstitut->setText(currentPerson.institut);
    ui->lineEditBUni->setText(currentPerson.universitaet);
    ui->lineEditBStr->setText(currentPerson.strasse);
    ui->lineEditBHausnr->setText(QString::number(currentPerson.hausnummer));
    ui->lineEditBPlz->setText(QString::number(currentPerson.plz));
    ui->lineEditBOrt->setText(currentPerson.ort);
    ui->lineEditBLand->setText(currentPerson.land);
    ui->lineEditBEMail->setText(currentPerson.email);
}

//Allgemeine Funktionen ENDE

//Screen Home START
void MainWindow::on_loadpushButton_clicked()
{
    Connect conn;
    QSqlQueryModel * mod = new QSqlQueryModel();

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT bestellungid, bestelldatum, bearbeitungsstatus, vorname, nachname, strasse, hausnummer, plz, stadt, email, dokumentid, titel FROM bestellung, ausleihender, dokument WHERE dokument.dokumentid = bestellung.dokument_dokumentid AND ausleihender.ausleihenderid = bestellung.ausleihender_ausleihenderid AND bearbeitungsstatus='Your Order is being processed' ORDER BY bestelldatum");

    qry->exec();
    mod->setQuery(*qry);
    ui->hometableView->setModel(mod);

    //Signal erzeugen, wenn eine Zeile des angezeigten Ergebnisses angeklickt wird
    connect(ui->hometableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
                 SLOT(slotSelectionChangeHome(const QItemSelection &, const QItemSelection &)));
}
//Screen Home ENDE

//Screen Ausleihen START
void MainWindow::on_durchsuchenpushButton_clicked()
{
    Connect conn;
    QSqlQueryModel * mod = new QSqlQueryModel();

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    QString s;
    s = "SELECT bestellungid, bestelldatum, bearbeitungsstatus, vorname, nachname, strasse, hausnummer, plz, stadt, email, grund, dokument.dokumentid, titel, autor FROM bestellung, ausleihender, dokument, autor, dokument_autor WHERE dokument.dokumentid = bestellung.dokument_dokumentid AND ausleihender.ausleihenderid = bestellung.ausleihender_ausleihenderid AND dokument.dokumentid = dokument_autor.dokumentid AND autor.autorid = dokument_autor.autorid AND autor.autor LIKE CONCAT('%', :a, '%') AND titel LIKE CONCAT('%', :t, '%') ";
    //Bearbeitungsstatus
    if (ui->radioButtonAngefragt->isChecked())
        s+= "AND bearbeitungsstatus='Your Order is being processed' ";
    if (ui->radioButtonAbgelehnt->isChecked())
        s+= "AND bearbeitungsstatus='Your Order has been declined' ";
    if (ui->radioButtonVersendet->isChecked())
        s+= "AND bearbeitungsstatus='Your Order has been dispatched' ";
    //Ausleihdatum
    /*if (!(ui->dateEdit->text().isEmpty())) //falls in Datumsmaske etwas steht
    {
        QDate d1;
        d1 = ui->dateEdit->date().toString();
        s+= "AND bestelldatum >= " + d1 + " ";
    }*/
    /*if (!(ui->dateEdit_2->text().isEmpty())) //falls in Datumsmaske etwas steht
    {
        QString d2;
        d2 = ui->dateEdit_2->text();
        s+= "AND bestelldatum <= " + d1;
    }*/
    //Erscheinungsjahr
    if (!(ui->AusleihenJahrlineEdit->text().isEmpty()))
    {
        QString jahr1 = ui->AusleihenJahrlineEdit->text();
        s+= "AND jahr >= " + jahr1 + " ";
    }
    if (!(ui->AusleihenJahrlineEdit_2->text().isEmpty()))
    {
        QString jahr2 = ui->AusleihenJahrlineEdit_2->text();
        s+= "AND jahr <= " + jahr2 + " ";
    }
    s += "ORDER BY bestelldatum ";

    QString t;
    t = ui->AusleihentitellineEdit->text();
    QString a;
    a = ui->AusleihenAutorlineEdit->text();

    qry->prepare(s);
    qry->bindValue(":t", t);
    qry->bindValue(":a", a);

    qry->exec();
    mod->setQuery(*qry);

    ui->tableViewAusleihenErgebnis->setModel(mod);

    //Signal erzeugen, wenn eine Zeile des angezeigten Ergebnisses angeklickt wird
    connect(ui->tableViewAusleihenErgebnis->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
                 SLOT(slotSelectionChange(const QItemSelection &, const QItemSelection &)));

}
//Screen Ausleihen ENDE

//Sub-Screen (Ausleihe) Einzelansicht START
void MainWindow::slotSelectionChangeHome(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList selection = ui->hometableView->selectionModel()->selectedRows();//in selection wird der Index der ausgewählten Zeile gespeichert
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::slotSelectionChange(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList selection = ui->tableViewAusleihenErgebnis->selectionModel()->selectedRows();//in selection wird der Index der ausgewählten Zeile gespeichert
    ui->stackedWidget->setCurrentIndex(8);
}

//Sub-Screen (Ausleihe) Einzelansicht ENDE

//Screen Neuer Katalogeintrag START
void MainWindow::on_addNewButton_clicked()
{
    Connect conn;
    conn.connClose();
    conn.connOpen();

    QSqlQuery * qry = new QSqlQuery(conn.db);

    QString s;
    s = "INSERT INTO dokument ( jahr, revision, buchband, ausfertigung, zustand, copyright, dokumentart, zeitschrift, ort, konferenz, verlag, seiten, bestand, titel_sammelband, aenderungsdatum, titel, untertitel, beschreibung, notizen, kommentar )VALUES (:jahr,:revision,:buchband,:ausfertigung,:zustand,:copyright,:dokumentart,:zeitschrift,:ort,:konferenz,:verlag,:seiten,:bestand,:titel_sammelband,:aenderungsdatum,:titel,:untertitel,:beschreibung,:notizen,:kommentar)";

    Katalogeintrag k;
    k.jahr = ui->jahrLineEdit->text().toInt();
    k.revision = ui->revisionLineEdit->text().toInt();
    k.buchband = ui->buchbandLineEdit->text().toInt();
    k.auflage = ui->auflageLineEdit->text().toInt();
    k.zustand = ui->zustandLineEdit->text().toInt();
    k.copyright = ui->copyrightLineEdit->text();
    k.dokumentart = ui->dokumentartLineEdit->text();
    k.zeitschrift = ui->zeitschriftLineEdit->text();
    k.erscheinungsort = ui->erscheinungsortLineEdit->text();
    k.konferenz = ui->konferenzLineEdit->text();
    k.verlag = ui->verlagLineEdit->text();
    k.seiten = ui->seitenLineEdit->text();
    k.bestand = ui->bestandLineEdit->text().toInt();
    k.titelSammelband = ui->titelsammelbandLineEdit->text();
    k.aenderungsdatum = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
    k.titel = ui->titelLineEdit->text();
    k.untertitel = ui->untertitelLineEdit->text();
    k.beschreibung = ui->beschreibungLineEdit->text();
    k.notizen = ui->notizenLineEdit->text();
    k.kommentar = ui->kommentarLineEdit->text();

    qry->prepare(s);
    qry->bindValue(":jahr", k.jahr);
    qry->bindValue(":revision", k.revision);
    qry->bindValue(":buchband", k.buchband);
    qry->bindValue(":ausfertigung", k.auflage);
    qry->bindValue(":zustand", k.zustand);
    qry->bindValue(":copyright", k.copyright);
    qry->bindValue(":dokumentart", k.dokumentart);
    qry->bindValue(":zeitschrift", k.zeitschrift);
    qry->bindValue(":ort", k.erscheinungsort);
    qry->bindValue(":konferenz", k.konferenz);
    qry->bindValue(":verlag", k.verlag);
    qry->bindValue(":seiten", k.seiten);
    qry->bindValue(":bestand", k.bestand);
    qry->bindValue(":titel_sammelband", k.titelSammelband);
    qry->bindValue(":aenderungsdatum", k.aenderungsdatum);
    qry->bindValue(":titel", k.titel);
    qry->bindValue(":untertitel", k.untertitel);
    qry->bindValue(":beschreibung", k.beschreibung);
    qry->bindValue(":notizen", k.notizen);
    qry->bindValue(":kommentar", k.kommentar);

    if(qry->exec())
        QMessageBox::information(this, tr("Katalogeintrag hinzugefügt"),tr("Der Katalogeintrag wurde erfolgreich hinzugefügt"),QMessageBox::Ok );
    else
        QMessageBox::warning(this, tr("Katalogeintrag nicht hinzugefügt"),tr("Der Katalogeintrag wurde nicht hinzugefügt!"),QMessageBox::Ok );

    QSqlQuery * qry2 = new QSqlQuery(conn.db);

    QString s2;
    s2 = "INSERT INTO autor ( autor ) SELECT * FROM (SELECT :autor) AS tmp WHERE NOT EXISTS (SELECT autor FROM autor WHERE autor = :autor) LIMIT 1";

    for (int i = 0; i < ui->autorlistWidget->count(); i++) {
        Autor a;
        a.autor = ui->autorlistWidget->item(i)->text();
        qry2->prepare(s2);
        qry2->bindValue(":autor", a.autor);

        qry2->exec();
    }

    QSqlQuery * qry3 = new QSqlQuery(conn.db);
    QString s3;
    s3 = "SELECT autorid FROM autor WHERE autor=:autor";

    QSqlQuery * qry4 = new QSqlQuery(conn.db);
    QString s4;
    s4 = "INSERT INTO dokument_autor (dokumentid, autorid) VALUES(:dokumentid, :autorid)";

    for (int i = 0; i < ui->autorlistWidget->count(); i++) {
        Autor a;
        Katalogeintrag k;
        a.autor = ui->autorlistWidget->item(i)->text();
        k.dokumentId = ui->dokumentidLineEdit->text().toInt();

        qry3->prepare(s3);
        qry3->bindValue(":autor", a.autor);
        qry3->exec();

        if (qry3->next())
            a.autorId = qry3->value(0).toInt();

        qry4->prepare(s4);
        qry4->bindValue(":dokumentid", k.dokumentId);
        qry4->bindValue(":autorid", a.autorId);

        qry4->exec();
    }
}

void MainWindow::on_autorpushButton_clicked()
{
    ui->autorlistWidget->addItem("Autorname");
    for (int i = 0; i < ui->autorlistWidget->count(); i++) {
        ui->autorlistWidget->item(i)->setFlags(ui->autorlistWidget->item(i)->flags() | Qt::ItemIsEditable);
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDeleteAll(ui->autorlistWidget->selectedItems());
}

void MainWindow::on_clearpushButton_clicked()
{
    ui->jahrLineEdit->clear();
    ui->revisionLineEdit->clear();
    ui->buchbandLineEdit->clear();
    ui->auflageLineEdit->clear();
    ui->zustandLineEdit->clear();
    ui->copyrightLineEdit->clear();
    ui->dokumentartLineEdit->clear();
    ui->zeitschriftLineEdit->clear();
    ui->erscheinungsortLineEdit->clear();
    ui->konferenzLineEdit->clear();
    ui->verlagLineEdit->clear();
    ui->seitenLineEdit->clear();
    ui->bestandLineEdit->clear();
    ui->titelsammelbandLineEdit->clear();
    ui->titelLineEdit->clear();
    ui->untertitelLineEdit->clear();
    ui->beschreibungLineEdit->clear();
    ui->notizenLineEdit->clear();
    ui->kommentarLineEdit->clear();
}

//Screen Neuer Katalogeintrag ENDE

//Screen Katalogeintrag editieren START
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
   list=bcontroller->anzeigenKatalogeintrag();
   totalRecord=list.size();
   if(totalRecord!=0){
      currentIndex=0;
      currentKatalogeintrag=list.at(currentIndex);
      populateUI();
      ui->nextButton->setEnabled(true);
      ui->prevButton->setEnabled(true);
   }
}
void MainWindow::browseButtonClicked2()
{
    currentBearbeiter=list2.at(ui->comboBoxBAuswaehlen->currentIndex());
    currentPerson=list3.at(ui->comboBoxBAuswaehlen->currentIndex());
    populateUI2();
}

//Button Zurück um zwischen den Datensätzen zu navigieren
void MainWindow::on_prevButton_clicked()
{
    currentIndex--;
    if(currentIndex<0)
       currentIndex=totalRecord-1;
    ui->countLineEdit->setText(QString::number(currentIndex+1));
    populateRecord();
}
//Button Nächster um zwischen den Datensätzen zu navigieren
void MainWindow::on_nextButton_clicked()
{
    currentIndex++;
    if(currentIndex>=totalRecord)
       currentIndex=0;
    ui->countLineEdit->setText
       (QString::number(currentIndex+1));
    populateRecord();
}
//Suche nach dokumentid
void MainWindow::on_editierenfindButton_clicked()
{
    list=bcontroller->suchenKatalogeintragbyid(ui->dokumentidFindLineEdit->text().toInt());
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
//Suche nach dokumenttitel
void MainWindow::on_editierenfindButton_2_clicked()
{
    list=bcontroller->suchenKatalogeintragbytitel(ui->titelFindLineEdit->text());
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
//Suche nach Autor
void MainWindow::on_editierenfindButton_3_clicked()
{
    list=bcontroller->suchenKatalogeintragbyautor(ui->autorFindLineEdit->text());
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
//Weiteren Autor hinzufügen
void MainWindow::on_pushButton_2_clicked()
{
    ui->autorlistWidget_2->addItem("Autorname");
    for (int i = 0; i < ui->autorlistWidget_2->count(); i++) {
        ui->autorlistWidget_2->item(i)->setFlags(ui->autorlistWidget_2->item(i)->flags() | Qt::ItemIsEditable);
    }
}
//Ausgewählten Autor entfernen
void MainWindow::on_pushButton_3_clicked()
{
    qDeleteAll(ui->autorlistWidget_2->selectedItems());
}
//UPDATE
void MainWindow::on_updateButton_clicked()
{
    Connect conn;
    conn.connClose();
    conn.connOpen();

    QSqlQuery * qry = new QSqlQuery(conn.db);

    QString s;
    s = "UPDATE dokument SET jahr=:jahr, revision=:revision, buchband=:buchband,ausfertigung=:auflage,zustand=:zustand,copyright=:copyright,dokumentart=:dokumentart,zeitschrift=:zeitschrift,ort=:ort,konferenz=:konferenz,verlag=:verlag,seiten=:seiten,bestand=:bestand,titel_sammelband=:titelSammelband,aenderungsdatum=:aenderungsdatum,titel=:titel,untertitel=:untertitel,beschreibung=:beschreibung,notizen=:notizen,kommentar=:kommentar WHERE dokumentid=:dokumentid";

    Katalogeintrag k;
    k.jahr = ui->jahrLineEdit_2->text().toInt();
    k.revision = ui->revisionLineEdit_2->text().toInt();
    k.buchband = ui->buchbandLineEdit_2->text().toInt();
    k.auflage = ui->auflageLineEdit_2->text().toInt();
    k.zustand = ui->zustandLineEdit_2->text().toInt();
    k.copyright = ui->copyrightLineEdit_2->text();
    k.dokumentart = ui->dokumentartLineEdit_2->text();
    k.zeitschrift = ui->zeitschriftLineEdit_2->text();
    k.erscheinungsort = ui->erscheinungsortLineEdit_2->text();
    k.konferenz = ui->konferenzLineEdit_2->text();
    k.verlag = ui->verlagLineEdit_2->text();
    k.seiten = ui->seitenLineEdit_2->text();
    k.bestand = ui->bestandLineEdit_2->text().toInt();
    k.titelSammelband = ui->titelsammelbandLineEdit_2->text();
    k.aenderungsdatum = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
    k.titel = ui->titelLineEdit_2->text();
    k.untertitel = ui->untertitelLineEdit_2->text();
    k.beschreibung = ui->beschreibungLineEdit_2->text();
    k.notizen = ui->notizenLineEdit_2->text();
    k.kommentar = ui->kommentarLineEdit_2->text();
    k.dokumentId = ui->dokumentidLineEdit_2->text().toInt();

    qry->prepare(s);
    qry->bindValue(":jahr", k.jahr);
    qry->bindValue(":revision", k.revision);
    qry->bindValue(":buchband", k.buchband);
    qry->bindValue(":auflage", k.auflage);
    qry->bindValue(":zustand", k.zustand);
    qry->bindValue(":copyright", k.copyright);
    qry->bindValue(":dokumentart", k.dokumentart);
    qry->bindValue(":zeitschrift", k.zeitschrift);
    qry->bindValue(":ort", k.erscheinungsort);
    qry->bindValue(":konferenz", k.konferenz);
    qry->bindValue(":verlag", k.verlag);
    qry->bindValue(":seiten", k.seiten);
    qry->bindValue(":bestand", k.bestand);
    qry->bindValue(":titelSammelband", k.titelSammelband);
    qry->bindValue(":aenderungsdatum", k.aenderungsdatum);
    qry->bindValue(":titel", k.titel);
    qry->bindValue(":untertitel", k.untertitel);
    qry->bindValue(":beschreibung", k.beschreibung);
    qry->bindValue(":notizen", k.notizen);
    qry->bindValue(":kommentar", k.kommentar);
    qry->bindValue(":dokumentid", k.dokumentId);

    if(qry->exec())
        QMessageBox::information(this, tr("Katalogeintrag geändert"),tr("Der Katalogeintrag wurde erfolgreich geändert"),QMessageBox::Ok );
    else
        QMessageBox::warning(this, tr("Katalogeintrag nicht geändert"),tr("Der Katalogeintrag wurde nicht geändert!"),QMessageBox::Ok );

    QSqlQuery * qry5 = new QSqlQuery(conn.db);
    QString s5;
    s5 = "DELETE FROM dokument_autor WHERE dokumentid=:dokumentid";
    qry5->prepare(s5);
    qry5->bindValue(":dokumentid", k.dokumentId);
    qry5->exec();

    QSqlQuery * qry2 = new QSqlQuery(conn.db);
    QString s2;
    s2 = "INSERT INTO autor ( autor ) SELECT * FROM (SELECT :autor) AS tmp WHERE NOT EXISTS (SELECT autor FROM autor WHERE autor = :autor) LIMIT 1";

    for (int i = 0; i < ui->autorlistWidget_2->count(); i++) {
        Autor a;
        a.autor = ui->autorlistWidget_2->item(i)->text();
        qry2->prepare(s2);
        qry2->bindValue(":autor", a.autor);

        qry2->exec();
    }

    QSqlQuery * qry3 = new QSqlQuery(conn.db);
    QString s3;
    s3 = "SELECT autorid FROM autor WHERE autor=:autor";

    QSqlQuery * qry4 = new QSqlQuery(conn.db);
    QString s4;
    s4 = "INSERT INTO dokument_autor (dokumentid, autorid) VALUES(:dokumentid, :autorid)";

    for (int i = 0; i < ui->autorlistWidget_2->count(); i++) {
        Autor a;
        Katalogeintrag k;
        a.autor = ui->autorlistWidget_2->item(i)->text();
        k.dokumentId = ui->dokumentidLineEdit_2->text().toInt();

        qry3->prepare(s3);
        qry3->bindValue(":autor", a.autor);
        qry3->exec();

        if (qry3->next())
            a.autorId = qry3->value(0).toInt();

        qry4->prepare(s4);
        qry4->bindValue(":dokumentid", k.dokumentId);
        qry4->bindValue(":autorid", a.autorId);

        qry4->exec();
    }

    browseButtonClicked();
}
//LÖSCHEN
void MainWindow::on_deleteButton_clicked()
{
    Connect conn;
    conn.connClose();
    conn.connOpen();

    QSqlQuery * qry = new QSqlQuery(conn.db);
    QString s;
    s = "DELETE FROM dokument_autor WHERE dokumentid=:dokumentid";

    qry->prepare(s);
    qry->bindValue(":dokumentid", ui->dokumentidLineEdit_2->text().toInt());
    qry->exec();

    QSqlQuery * qry2 = new QSqlQuery(conn.db);
    QString s2;
    s2 = "DELETE FROM dokument WHERE dokumentid=:dokumentid";

    qry2->prepare(s2);
    qry2->bindValue(":dokumentid", ui->dokumentidLineEdit_2->text().toInt());

    if(qry2->exec())
        QMessageBox::information(this, tr("Katalogeintrag gelöscht"),tr("Der Katalogeintrag wurde erfolgreich gelöscht"),QMessageBox::Ok );
    else
        QMessageBox::warning(this, tr("Katalogeintrag nicht gelöscht"),tr("Der Katalogeintrag wurde nicht gelöscht!"),QMessageBox::Ok );

    browseButtonClicked();
}
//Screen Katalogeintrag editieren ENDE

//Screen Katalog durchsuchen START
void MainWindow::on_btn_search_suchendoc_clicked()
{
    Connect conn;
    QSqlQueryModel * mod = new QSqlQueryModel();

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    QString s;
    s = "SELECT * FROM dokument, autor, dokument_autor WHERE dokument.dokumentid = dokument_autor.dokumentid AND autor.autorid = dokument_autor.autorid AND dokument.titel LIKE CONCAT('%', :titel, '%') AND autor.autor LIKE CONCAT('%', :autor, '%')";
    if (!(ui->le_erschj_von_suchendoc->text().isEmpty()))
    {
        QString jahr1 = ui->le_erschj_von_suchendoc->text();
        s+= " AND jahr >= " + jahr1;
    }
    if (!(ui->le_erschj_bis_suchendoc->text().isEmpty()))
    {
        QString jahr2 = ui->le_erschj_bis_suchendoc->text();
        s+= " AND jahr <= " + jahr2;
    }
    s+= " ORDER BY dokument.dokumentid";


    QString titel;
    titel = ui->le_titelstichw_suchendoc->text();
    QString autor;
    autor = ui->le_autor_suchendoc->text();

    qry->prepare(s);
    qry->bindValue(":titel", titel);
    qry->bindValue(":autor", autor);

    qry->exec();
    mod->setQuery(*qry);

    ui->katalogdurchsuchentableView->setModel(mod);
}
//Screen Katalog durchsuchen ENDE

//Screen Bearbeiter START
void MainWindow::on_pushButtonSpeichern_clicked()
{
    if(ui->lineEditBId->text().isEmpty())
    {
        Connect conn;
        conn.connClose();
        conn.connOpen();

        QSqlQuery * qry = new QSqlQuery(conn.db);

        QString s;
        s = "INSERT INTO bearbeiter ( anrede, akademischergrad, vorname, nachname, institut, universitaet, strasse, hausnummer, plz, stadt, land, email, benutzername, emailsignatur )VALUES ( :anrede, :akademischergrad, :vorname, :nachname, :institut, :universitaet, :strasse, :hausnummer, :plz, :stadt, :land, :email, :benutzername, :emailsignatur )";

        Person p;
        Bearbeiter b;
        p.anrede = ui->lineEditBAnrede->text();
        p.akademischerGrad = ui->lineEditBAkadGrad->text();
        p.vorname = ui->lineEditBVorname->text();
        p.nachname = ui->lineEditBNachname->text();
        p.institut = ui->lineEditBInstitut->text();
        p.universitaet = ui->lineEditBUni->text();
        p.strasse = ui->lineEditBStr->text();
        p.hausnummer = ui->lineEditBHausnr->text().toInt();
        p.plz = ui->lineEditBPlz->text().toInt();
        p.ort = ui->lineEditBOrt->text();
        p.land = ui->lineEditBLand->text();
        p.email = ui->lineEditBEMail->text();
        b.benutzername = ui->lineEditBLogin->text();
        b.emailSignatur = ui->lineEditBEmailSignatur->text();

        qry->prepare(s);
        qry->bindValue(":anrede", p.anrede);
        qry->bindValue(":akademischergrad", p.akademischerGrad);
        qry->bindValue(":vorname", p.vorname);
        qry->bindValue(":nachname", p.nachname);
        qry->bindValue(":institut", p.institut);
        qry->bindValue(":universitaet", p.universitaet);
        qry->bindValue(":strasse", p.strasse);
        qry->bindValue(":hausnummer", p.hausnummer);
        qry->bindValue(":plz", p.plz);
        qry->bindValue(":stadt", p.ort);
        qry->bindValue(":land", p.land);
        qry->bindValue(":email", p.email);
        qry->bindValue(":benutzername", b.benutzername);
        qry->bindValue(":emailsignatur", b.emailSignatur);

        if(qry->exec())
            QMessageBox::information(this, tr("Benutzer hinzugefügt"),tr("Der Benutzer wurde erfolgreich hinzugefügt"),QMessageBox::Ok );
        else
            QMessageBox::warning(this, tr("Benutzer nicht hinzugefügt"),tr("Der Benutzer wurde nicht hinzugefügt!"),QMessageBox::Ok );

    }
    else
    {
        Connect conn;
        conn.connClose();
        conn.connOpen();

        QSqlQuery * qry = new QSqlQuery(conn.db);

        QString s;
        s = "UPDATE bearbeiter SET anrede=:anrede, akademischergrad=:akademischergrad, vorname=:vorname, nachname=:nachname, institut=:institut, universitaet=:universitaet, strasse=:strasse, hausnummer=:hausnummer, plz=:plz, stadt=:stadt, land=:land, email=:email, benutzername=:benutzername, emailsignatur=:emailsignatur WHERE bearbeiterid=:bearbeiterid";

        Person p;
        Bearbeiter b;
        b.bearbeiterId = ui->lineEditBId->text().toInt();
        p.anrede = ui->lineEditBAnrede->text();
        p.akademischerGrad = ui->lineEditBAkadGrad->text();
        p.vorname = ui->lineEditBVorname->text();
        p.nachname = ui->lineEditBNachname->text();
        p.institut = ui->lineEditBInstitut->text();
        p.universitaet = ui->lineEditBUni->text();
        p.strasse = ui->lineEditBStr->text();
        p.hausnummer = ui->lineEditBHausnr->text().toInt();
        p.plz = ui->lineEditBPlz->text().toInt();
        p.ort = ui->lineEditBOrt->text();
        p.land = ui->lineEditBLand->text();
        p.email = ui->lineEditBEMail->text();
        b.benutzername = ui->lineEditBLogin->text();
        b.emailSignatur = ui->lineEditBEmailSignatur->text();

        qry->prepare(s);
        qry->bindValue(":anrede", p.anrede);
        qry->bindValue(":akademischergrad", p.akademischerGrad);
        qry->bindValue(":vorname", p.vorname);
        qry->bindValue(":nachname", p.nachname);
        qry->bindValue(":institut", p.institut);
        qry->bindValue(":universitaet", p.universitaet);
        qry->bindValue(":strasse", p.strasse);
        qry->bindValue(":hausnummer", p.hausnummer);
        qry->bindValue(":plz", p.plz);
        qry->bindValue(":stadt", p.ort);
        qry->bindValue(":land", p.land);
        qry->bindValue(":email", p.email);
        qry->bindValue(":benutzername", b.benutzername);
        qry->bindValue(":emailsignatur", b.emailSignatur);
        qry->bindValue(":bearbeiterid", b.bearbeiterId);

        if(qry->exec())
            QMessageBox::information(this, tr("Benutzer geändert"),tr("Der Benutzer wurde erfolgreich geändert"),QMessageBox::Ok );
        else
            QMessageBox::warning(this, tr("Benutzer nicht geändert"),tr("Der Benutzer wurde nicht geändert!"),QMessageBox::Ok );

    }
    list2=bcontroller->anzeigenBearbeiter2();
    list3=bcontroller->anzeigenPerson();
    on_actionBearbeiter_in_triggered();
}

void MainWindow::on_pushButtonBNeuerBearbeiter_clicked()
{
    ui->lineEditBId->clear();
    ui->lineEditBAnrede->clear();
    ui->lineEditBAkadGrad->clear();
    ui->lineEditBVorname->clear();
    ui->lineEditBNachname->clear();
    ui->lineEditBInstitut->clear();
    ui->lineEditBUni->clear();
    ui->lineEditBStr->clear();
    ui->lineEditBHausnr->clear();
    ui->lineEditBPlz->clear();
    ui->lineEditBOrt->clear();
    ui->lineEditBLand->clear();
    ui->lineEditBEMail->clear();
    ui->lineEditBLogin->clear();
    ui->lineEditBEmailSignatur->clear();
}
void MainWindow::on_pushButton_4_clicked()
{
    browseButtonClicked2();

}
//Screen Bearbeiter ENDE

//Screen Mediendatei hinzufügen START
void MainWindow::on_btn_datei_waehlen_media_clicked()
{
    QString media_path;
    QFileDialogTester test;
    media_path = test.openFile();
    //Add media path to doc_id
}
//Wenn speichern geklickt wurde, wird geprüft ob doc_id existiert und anschließend der Name der gewählten Datei mit doc_id verknüpft
void MainWindow::on_btn_save_media_2_clicked()
{
    list=bcontroller->suchenKatalogeintragbyid(ui->le_add_media_2->text().toInt());
    totalRecord=list.size();
    if(totalRecord!=0){
        //doc_id mit dateinamen verbinden
        QMessageBox::warning( 0, tr( "Erfolgreich" ), tr( "Datei hinzugefügt!\n\n" ) );
        ui->stackedWidget->setCurrentIndex(6);
    }
    else {
        QMessageBox::warning(this, tr("Doc_ID nicht vorhanden"),
           tr("Bei der Suche wurde keine passende Dokument_ID gefunden"),QMessageBox::Ok );
    }
}

//Screen EMail START
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

//CONFIG DATEI
void MainWindow::onEmail()
{
    //Config Datei einlesen
    QFile inputFile(QString("/home/son1i/Schreibtisch/Desktop\ App/SWT_v18/bearbeiter.config"));
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen())
        return;

    QTextStream stream(&inputFile);
    QString config = stream.readLine();

    //SQL Anfrage
    QString email;
    Connect conn;

    conn.connClose();
    conn.connOpen();
    QSqlQuery * qry = new QSqlQuery(conn.db);

    qry->prepare("SELECT email FROM bearbeiter WHERE nachname=:nachname");
    qry->bindValue(":nachname", config);
    qry->exec();

    if (qry->next())
        email = qry->value(0).toString();

    //UI
    ui->uname->setText(email);
}

/* Screen EMail ENDE */
