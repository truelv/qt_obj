#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTranslator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#if 0
void MainWindow::changeEvent(QEvent *e)
{
    qDebug() << "xxxxxxxxxxx ";
    if (e->type()==QEvent::LanguageChange) {
        ui->label->setText(tr("PushButton"));
    } else
        QMainWindow::changeEvent(e);
}
#endif

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    qDebug() << "check " << arg1;
    QTranslator m;
    m.load(":/Chinese.qm");
    qApp->installTranslator(&m);
    ui->label->setText(tr("TextLabel"));
    ui->pushButton->setText(tr("PushButton"));
}
