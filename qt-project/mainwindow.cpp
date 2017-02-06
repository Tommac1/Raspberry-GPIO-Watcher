#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>
#include <QtCore>
#include <QMap>

QString setLabelText(int pinNum);
void updateStatusLabels();
void setLabelStyleSheet(QLabel *label);

// Sets the display language: 0 - Polish, 1 - German, 2 - English
int language = 0;

QString const STATUS_OK_STYLESHEET = "color: white; "
                                     "border: 2px solid white; "
                                     "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
                                     "stop: 0 #77d42a, stop: 1.0 #08A500); ";

QString const STATUS_NOT_OK_STYLESHEET = "color: white; "
                                         "border: 2px solid white; "
                                         "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, "
                                         "stop: 0 #fe1a00, stop: 1.0 #A50000); ";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Main program loop, updates data every X secs
    QTimer *updater = new QTimer(this);
    connect(updater, SIGNAL(timeout()), this, SLOT(updateStatusLabels()));
    updater->start(3000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatusLabels()
{
    QMap<QString, QLabel *> map;

    // Pushes status labels to QMap (map) with the key as it's name
    for (int i = 1; i <= 16; i++) {
        QString labelName = "pin";
        if (i <= 99 && i >= 10)
            labelName += "0";
        if (i < 10)
            labelName += "00";

        labelName += QString::number(i);
        labelName += "Status";

        map[labelName] = this->findChild<QLabel *>(labelName);
    }

    QMapIterator<QString, QLabel *> mapIterator(map);

    QProcess proc(this);

    proc.start("./fileProgram");

    if (proc.waitForFinished(500)) {
        int i = 1;

        while (mapIterator.hasNext()) {
            mapIterator.next();

            mapIterator.value()->setText(setLabelText(i));
            setLabelStyleSheet(mapIterator.value());

            i++;
        }

        mapIterator.toFront();
    }

    proc.close();


}

void setLabelStyleSheet(QLabel *label)
{
    if (!QString::compare(label->text(), "OK"))
        label->setStyleSheet(STATUS_OK_STYLESHEET);
    else if (!QString::compare(label->text(), "BRAK SMAROWANIA") ||
             !QString::compare(label->text(), "LUBRICATION MISSING") ||
             !QString::compare(label->text(), "FAHLENDE SHIMERUNG"))
        label->setStyleSheet(STATUS_NOT_OK_STYLESHEET);
}

QString setLabelText(int pinNum)
{
    QFile mFile("./pinStatus.txt");

    QString pins;

    if (mFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&mFile);

        while (!in.atEnd()) {
            pins += in.readLine();
            pins += "; ";
        }
    }

    QString pinState = "pin";
    pinState += QString::number(pinNum);

    mFile.close();

    int statePosition = (pins.indexOf(pinState) + 5);

    if (pinNum >= 100)
        statePosition += 2;

    if (pinNum >= 10 && pinNum <= 99)
        statePosition += 1;

    QChar state = pins.at(statePosition);

    if (state.digitValue())
        return "OK";
    else {
        switch (language)
        {
        case 0:
            return "BRAK SMAROWANIA";
        case 1:
            return "FAHLENDE SHIMERUNG";
        case 2:
            return "LUBRICATION MISSING";
        default:
            // never reached...
            return "XXX";
        }
    }
    return "XXX";
}

void MainWindow::on_closeButton_clicked()
{
    exit(0);
}

void MainWindow::on_polishLangButton_clicked()
{
    language = 0;
    ui->closeButton->setText("ZAMKNIJ");
}

void MainWindow::on_germanLangButton_clicked()
{
    language = 1;
    ui->closeButton->setText("SCHLUSS");
}

void MainWindow::on_englishLangButton_clicked()
{
    language = 2;
    ui->closeButton->setText("CLOSE");
}


