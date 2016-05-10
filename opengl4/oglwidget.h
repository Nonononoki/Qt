#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include "kugel.h"
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

    void setX( float newx );
    void setY( float newy );

    void cross(Vector a, Vector b);


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    int rotx;       // Rotation angles (0..360)
    int roty;
    int rotz;
    int zoom;       // Zoom factor (0..200, 100 for 1:1)

    QPoint lastpos; // Last position of mouse pressed, used for dragging
    QPoint uppos;

    Kugel kugel[2]; //immer gleich anzKugeln
};


#endif // OGLWIDGET_H
