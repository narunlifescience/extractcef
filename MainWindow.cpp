#include "MainWindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QThread>
#include <memory>
#include "handler.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->open_pushButton, &QPushButton::clicked, this,
          &MainWindow::openPushbutton);
  connect(ui->generatetxt_pushButton, &QPushButton::clicked, this,
          &MainWindow::generatetextfile);
  connect(ui->about_pushButton, &QPushButton::clicked, this, [=]() {
    ui->statusBar->showMessage(
        "Created by: Arun Narayanankutty, PostDoc, MSoLS");
  });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::openPushbutton() {
  QFileDialog filedialog;
  QString fileName =
      filedialog.getOpenFileName(this, tr("Open CEF"), tr("CEF File (*.cef)"));
  ui->open_lineEdit->setText(fileName);
}

void MainWindow::generatetextfile() {
  QFile f(ui->open_lineEdit->text().trimmed());
  if (ui->open_lineEdit->text().trimmed().isEmpty() || !f.exists() ||
      !ui->open_lineEdit->text().trimmed().endsWith(".cef")) {
    ui->statusBar->showMessage(tr("Please select a valid file"));
  } else {
    ui->statusBar->showMessage(tr("Generating tsv..."));
    QString fname = ui->open_lineEdit->text().trimmed();
    std::unique_ptr<handler> hdlr =
        std::unique_ptr<handler>(new handler(fname));
    ui->statusBar->showMessage(tr("Done"));
  }
}
