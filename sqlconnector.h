#ifndef CONNECT_H
#define CONNECT_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class Connect;
}

class Connect : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;

    void connClose();

    bool connOpen();

    ~Connect();
};

#endif // CONNECT_H
