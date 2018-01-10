#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include "add_media.h"


QString QFileDialogTester::openFile()
  {
    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open Document",
          QDir::currentPath(),
          "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");

    if( !filename.isNull() )
    {
      qDebug() << "selected file path : " << filename.toUtf8();
    }
    return filename;
  }

