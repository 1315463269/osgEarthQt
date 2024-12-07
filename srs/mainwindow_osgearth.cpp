#include "mainwindow_osgearth.h"
#include "ui_mainwindow_osgearth.h"

MainWindow_osgEarth::MainWindow_osgEarth(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_osgEarth)
{
    ui->setupUi(this);
}

MainWindow_osgEarth::~MainWindow_osgEarth()
{
    delete ui;
}
