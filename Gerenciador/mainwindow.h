#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtWidgets>
#include "bd.h"  // incluir o header

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QListWidget *instrumentList;
    QListWidget *scheduleScreen;
    QListWidget *scheduleshow;
    bd *database;
    QLabel * label;
    QPushButton * button_instrument;
    QPushButton * button_musician;
    QPushButton * button_musicianV;
    QPushButton * button_scheduleshow;
    QPushButton * button_music;
    QPushButton * button_checkSchedMusician;
    QSpinBox * spin;
    QSlider * slider;
    QVBoxLayout * mainLayout;
};

#endif // MAINWINDOW_H
