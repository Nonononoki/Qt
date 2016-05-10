#include "oglwidget.h"
#include <QDebug>
#include <cmath>
#include "kugel.h"

void drawQuad(float x, float y, float z, bool senktrecht)
{
    glBegin(GL_QUADS);

        if(senktrecht)
        {
            glVertex3f(x,y,0);
            glVertex3f(x,-y,0);

            glVertex3f(x,-y,z);
            glVertex3f(x,y,z);

            glVertex3f(x,y,0);
        }
        else
        {
            glVertex3f(x,y,0);
            glVertex3f(-x,y,0);

            glVertex3f(-x,y,z);
            glVertex3f(x,y,z);

            glVertex3f(x,y,0);
        }

    glEnd();
}

void drawGround(float x, float y, float y2, float z, float z2)
{
    glBegin(GL_QUADS);


        glVertex3f(x,y,z);
        glVertex3f(-x,y,z);

        glVertex3f(-x,y2,z2);
        glVertex3f(x,y2,z2);

        glVertex3f(x,y,0);

    glEnd();
}


float kugelHoehe(float a, float b, float hoehe, float y) //Start und Ende der schiefen Ebene
{
    float z;

    float m = hoehe/ (a-b) * -1;

    if(y >= a)
    {
        z = 0;
    }
    else if(y < a && y > b)
    {
        z = (y+b)*m;
    }
    else if(y <= b)
    {
        z = hoehe;
    }

    return z;
}

void drawKugel(float radius, float x, float y, float z)
{
    float theta = 0, phi = 0;

    float delta = 20;
    float deltaTheta = M_PI / delta, deltaPhi = M_PI / delta;

    glTranslatef(x,y,z);

    //Berechnung
    float z1, x1, y1, z2, x2, y2, z3, x3, y3, z4, x4, y4;

    glBegin(GL_QUAD_STRIP);

        for(theta = 0; theta <= 2 * M_PI ; theta += deltaTheta)
        {
            for(phi = 0; phi <= 2 * M_PI; phi += deltaPhi)
            {

                //Kreisformel
                z1 = radius * sin(phi + deltaPhi) * cos(theta + deltaTheta);
                x1 = radius * sin(phi + deltaPhi) * sin(theta + deltaTheta);
                y1 = radius * cos(phi + deltaPhi);

                z2 = radius * sin(phi) * cos(theta + deltaTheta);
                x2 = radius * sin(phi) * sin(theta + deltaTheta);
                y2 = radius * cos(phi);

                z3 = radius * sin(phi) * cos(theta);
                x3 = radius * sin(phi) * sin(theta);
                y3 = radius * cos(phi);

                z4 = radius * sin(phi + deltaPhi) * cos(theta);
                x4 = radius * sin(phi + deltaPhi) * sin(theta);
                y4 = radius * cos(phi + deltaPhi);


                glVertex3f(x1, y1, z1);

                glVertex3f(x2, y2, z2);

                glVertex3f(x3, y3, z3);

                glVertex3f(x4, y4, z4);
            }
        }

    glEnd();
}

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    rotx = 0;
    roty = 0;
    rotz = 0;
    zoom = 100;
}

OGLWidget::~OGLWidget()
{
}


void OGLWidget::setRotX(int newrx)
{
    rotx = newrx;
    update();
}

void OGLWidget::setRotY(int newry)
{
    roty = newry;
    update();
}

void OGLWidget::setRotZ(int newrz)
{
    rotz = newrz;
    update();
}

void OGLWidget::setZoom(int newzoom)
{
    zoom = newzoom;
    update();
}

Vector cross(Vector a, Vector b)
{
    return Vector ( a.y*b.z - a.z*b.y,
                    a.z*b.x - a.x*b.z,
                    a.x*b.y - a.y*b.x  );
}

float norm(Vector a)
{
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

float betrag(float a)
{
    if(a < 0) a = -a;

    return a;
}

void reibung(Vector &dir, Vector pos, float anfang, float ende)
{
    //Keine Reibung wenn an der Schräge!

    //qDebug() << pos.y;
    if(pos.y < ende || pos.y > anfang)
    {
        float b = 0.995f;
        dir = dir * b;

        float margin = 0.01f;
        if(betrag(dir.x) <= margin)
        {
            dir.x = 0;
        }

        if(betrag(dir.y) <= margin)
        {
            dir.y = 0;
        }
    }
}


void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // For wireframe replace GL_FILL with GL_LINE
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(-10,10,-10,10, -100,100);

    glTranslatef(0,0,10);

    glPushMatrix();
    glColor3f(1,1,1);

    // Apply rotation angles

    glRotatef(rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    // Apply scaling
    float scale = zoom/100.0;
    glScalef( scale, scale, scale ); // Scale along all axis


    //Bänder Zeichnen
    float size = 9;
    float height = 5;
    float height2 = height+2;

    drawQuad(size,size, height2, false);
    drawQuad(size,-size,height2, false);
    drawQuad(size,size,height2, true);
    drawQuad(-size,size,height2, true);


    //Boden zeichnen
    //Anfang und Ende der schiefen Ebene
    float anfang = size/3; //Bord soll gedrittelt werden
    float ende = -size/3;

    glColor3f(0,1,0);
    drawGround(size, size, anfang, 0, 0);

    glColor3f(1,1,0);
    drawGround(size, anfang, ende, 0, height);

    glColor3f(0,1,1);
    drawGround(size, ende, -size, height, height);


    const float speed = 0.001;
    const float ebenenKonst = 0.01;
    float radius = 1;

    //Kugel Objects
    int anzKugeln = 2;

    //Erste Kugel
    glPushMatrix();

        glColor3f(1,0,0);

        //calculate direction
        if(uppos.x() != 0 && uppos.y() != 0)
        {
            kugel[0].dir.x = (float)(uppos.x() - lastpos.x()) * speed;
            kugel[0].dir.y = -(uppos.y() - lastpos.y()) * speed;

            uppos.setX(0);
            uppos.setY(0);
        }

        //Geschwindigkeitsänderung in der schiefen Ebene
        if(kugel[0].pos.y < anfang && kugel[0].pos.y > ende)
        {
            kugel[0].dir.y += ebenenKonst;
        }     

        kugel[0].pos.x += kugel[0].dir.x;
        kugel[0].pos.y += kugel[0].dir.y;
        kugel[0].pos.z =  kugelHoehe(anfang, ende, height, kugel[0].pos.y) + radius;

        drawKugel(radius,kugel[0].pos.x,kugel[0].pos.y,kugel[0].pos.z);

    glPopMatrix();

    for(int i = 1; i < anzKugeln; i++)
    {
        //zweite Kugel und auch weitere
        glPushMatrix();

            glColor3f(0,0,1);

            //Geschwindigkeitsänderung in der schiefen Ebene
            if(kugel[i].pos.y < anfang && kugel[i].pos.y > ende)
            {
                kugel[i].dir.y += ebenenKonst;
            }

            kugel[i].pos.x += kugel[i].dir.x;
            kugel[i].pos.y += kugel[i].dir.y;
            kugel[i].pos.z = kugelHoehe(anfang, ende, height, kugel[i].pos.y) + radius;

            drawKugel(radius,kugel[i].pos.x,kugel[i].pos.y,kugel[i].pos.z);

        glPopMatrix();
    }

    //Kollisionsüberprüfung Rand
    for(int i = 0; i < anzKugeln; i++)
    {
        if(kugel[i].pos.x-radius <= -size || kugel[i].pos.x +radius>= size)
        {
            kugel[i].dir.x = -kugel[i].dir.x;
        }
        else if(kugel[i].pos.y-radius <= -size || kugel[i].pos.y+radius >= size)
        {
            kugel[i].dir.y = -kugel[i].dir.y;
        }
    }

    for(int j = 0; j < anzKugeln; j++)
    {
        for(int i = 0; i < anzKugeln; i++)
        {
            //float abstand = sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2));
            float abstand = sqrt(pow(kugel[i].pos.x-kugel[j].pos.x,2) + pow(kugel[i].pos.y-kugel[j].pos.y,2));

            if(i != j)
            {
                //Kollision der Kugeln
                if(abstand <= radius*2 && kugel[i].verhakt[j] == false)
                {
                    //do something

                    Vector X = kugel[i].pos;
                    Vector Y = kugel[j].pos;
                    Vector a = X-Y;
                    Vector VX = kugel[i].dir;
                    Vector VY = kugel[j].dir;

                    Vector S = 0.5f * (X-Y) ;
                    Vector VS = 0.5f *(VX+VY);

                    Vector VX1 = VX-VS;
                    Vector VY1 = VY-VS;

                    Vector VX2 = 2.0f * ((a*VX1) / norm(a)*norm(a)) * a;
                    Vector VY2 = 2.0f * ((a*VY1) / norm(a)*norm(a)) * a;

                    float impulserhaltung = -0.15;//-0.15;
                    kugel[i].dir = (VX2+VS) * impulserhaltung;
                    kugel[j].dir = (VY2+VS) * impulserhaltung;

                    kugel[i].verhakt[j] = true;
                    kugel[j].verhakt[i] = true;
                }
            }

            //enthaken
            if(kugel[i].verhakt[j] == true && abstand > radius*2)
            {
                kugel[i].verhakt[j] = false;
            }
        }

        //reibung#
        reibung(kugel[j].dir, kugel[j].pos, anfang, ende);
    }


    glPopMatrix();
    update();

}

void OGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    // Upon mouse pressed, we store the current position...
    lastpos = event->pos();
}


void OGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    uppos = event->pos();
}
