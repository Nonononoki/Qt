#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Handle slider usage
    connect(ui->xRot, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotX(int)));
    connect(ui->yRot, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotY(int)));
    connect(ui->zRot, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setRotZ(int)));
    connect(ui->zoom, SIGNAL(valueChanged(int)), ui->glwidget, SLOT(setZoom(int)));

    // Handle any rotation change requests from mouse dragging and key presses
    //connect( ui->glwidget, SIGNAL(changeRotation(int,int,int)), this, SLOT(onChangeRotation(int,int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


