#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include "zylinder.h"
#include "kugel.h"
#include "schraege.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>


class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

    // Used to rotate object by mouse
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    // Set the rotation angles
    void setRotX( int newrx );
    void setRotY( int newry );
    void setRotZ( int newrz );

    // Set zoom factor
    void setZoom( int newzoom );

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    int rotx;       // Rotation angles (0..360)
    int roty;
    int rotz;
    int zoom;       // Zoom factor (0..200, 100 for 1:1)

    float sizex = 10;
    float sizey = 20;
    float height = 2;
    float height2 = height+1;

    QPoint lastpos; // Last position of mouse pressed, used for dragging
    QPoint uppos;

    int anzKugeln;
    int anzZylinder;
    int anzSchraege;

    Kugel kugel[13]; //immer gleich anzKugeln
    Vector start[13]; //Startpositionen der Kugel

    Zylinder zylinder[6];
    Schraege schraege[2];


};


#endif // OGLWIDGET_H
