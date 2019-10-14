#ifndef APROJHANDLER_H
#define APROJHANDLER_H

#include <QFile>
#include <QObject>
#include <memory>

class XmlStreamReader;

class handler : public QObject {
  Q_OBJECT
 public:
  handler(QString filename);
  ~handler();

 private:
  void readcefstream(QFile *file);
  void prepare(QFile *file);

 private:
  QString filename_;
};

#endif  // HANDLER_H
