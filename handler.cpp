#include "handler.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QMdiSubWindow>
#include <memory>

handler::handler(QString filename) : filename_(filename) {
  Q_ASSERT(!filename.isEmpty());
  QFile *file = new QFile(filename_);
  if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
    qDebug() << "unable to open " << filename_;
    delete file;
    return;
  } else {
    prepare(file);
    readcefstream(file);
    delete file;
  }
}

handler::~handler() {}

void handler::readcefstream(QFile *file) {
  QFileInfo fileinfo(filename_);
  QString baseName = fileinfo.fileName();
  QString newFilename = fileinfo.absoluteFilePath().remove(".cef") + ".tsv";
  std::unique_ptr<QFile> tsvfile =
      std::unique_ptr<QFile>(new QFile(newFilename));
  if (tsvfile->open(QFile::WriteOnly)) {
    QTextStream stream(tsvfile.get());
    stream << "rt\tx\ty\tv\tz\ts\n";
    QString line = QString();
    QStringList linelist;
    QString rt, x, y, v, z, s;
    while (!file->atEnd()) {
      line = file->readLine().trimmed();
      if (line.startsWith("<p") && line.contains("rt=\"") &&
          line.contains("x=\"") && line.contains("y=\"") &&
          line.contains("v=\"") && line.contains("z=\"") &&
          line.contains("s=\"")) {
        line = line.remove(0, 3);
        line = line.remove(line.length() - 3, 3);
        linelist = line.split(" ");
        foreach (QString str, linelist) {
          if (str.startsWith("rt=\"")) {
            rt = str;
            rt.remove("rt=\"");
            rt.remove("\"");
          } else if (str.startsWith("x=\"")) {
            x = str;
            x.remove("x=\"");
            x.remove("\"");
          } else if (str.startsWith("y=\"")) {
            y = str;
            y.remove("y=\"");
            y.remove("\"");
          } else if (str.startsWith("v=\"")) {
            v = str;
            v.remove("v=\"");
            v.remove("\"");
          } else if (str.startsWith("z=\"")) {
            z = str;
            z.remove("z=\"");
            z.remove("\"");
          } else if (str.startsWith("s=\"")) {
            s = str;
            s.remove("s=\"");
            s.remove("\"");
          }
        }
        stream << rt << "\t" << x << "\t" << y << "\t" << v << "\t" << z << "\t"
               << s << "\n";
      }
    }

    tsvfile->close();
  }
}

void handler::prepare(QFile *file) {
  QString line = QString();
  while (!file->atEnd()) {
    line = file->readLine().trimmed();
    if (line.startsWith("<p") && line.contains("rt=\"") &&
        line.contains("x=\"") && line.contains("y=\"") &&
        line.contains("v=\"") && line.contains("z=\"") &&
        line.contains("s=\"")) {
    }
  }
}
