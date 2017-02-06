#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtCore>
#include <QMap>

class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

private slots:
    void updateStatusLabels();
    void on_closeButton_clicked();
    void on_germanLangButton_clicked();
    void on_englishLangButton_clicked();
    void on_polishLangButton_clicked();
};

#endif // MAINWINDOW_H
