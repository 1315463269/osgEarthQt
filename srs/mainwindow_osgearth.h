#ifndef MAINWINDOW_OSGEARTH_H
#define MAINWINDOW_OSGEARTH_H

#include <QMainWindow>

namespace Ui {
class MainWindow_osgEarth;
}

class MainWindow_osgEarth : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_osgEarth(QWidget *parent = nullptr);
    ~MainWindow_osgEarth();

private:
    Ui::MainWindow_osgEarth *ui;
};

#endif // MAINWINDOW_OSGEARTH_H
