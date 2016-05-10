#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onChangeDirection( int dx, int dy, int dz );
    //void onChangeDirection( float dx, float dz);
    void move( int x, int y );

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
