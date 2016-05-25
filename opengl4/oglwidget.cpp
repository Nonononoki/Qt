#include "oglwidget.h"
#include <QDebug>
#include <cmath>

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

void drawZylinder( float rad, float v)
{
    int n = 30; int arg = 0;

    // DumbProof Double Check :)
        if (arg < 0)
            arg = 0;

        // Cylinder Bottom
        glBegin(GL_POLYGON);
            glColor4f(0.0, 0.0, 0.0, 1.0);
            for(int i = arg; i <= (360 + arg); i += (360 / n)) {
                float a = i * M_PI / 180; // degrees to radians
                glVertex3f(rad * cos(a), rad * sin(a), 0.0);
            }
        glEnd();

        // Cylinder Top
        glBegin(GL_POLYGON);
            glColor4f(0.0, 0.0, 0.0, 1.0);
            for(int i = arg; i <= (360 + arg); i += (360 / n)) {
                float a = i * M_PI / 180; // degrees to radians
                glVertex3f(rad * cos(a), rad * sin(a), v);
            }
        glEnd();

        // Cylinder "Cover"
        glBegin(GL_QUAD_STRIP);
            glColor4f(0.0, 0.0, 0.0, 1.0);
            for(int i = arg; i < 480; i += (360 / n)) {
                float a = i * M_PI / 180; // degrees to radians
                glVertex3f(rad * cos(a), rad * sin(a), 0.0);
                glVertex3f(rad * cos(a), rad * sin(a), v);
            }
        glEnd();

}

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    anzKugeln = 13;
    anzZylinder = 6;
    anzSchraege = 2;

    rotx = 0;
    roty = 0;
    rotz = 0;
    zoom = 100;

    radius = 1.0f;

    //Bänder Zeichnen
    sizex = 10;
    sizey = 20;
    height = 2;
    height2 = height+1; //höhe der Bänder

    //Startpositionen
    start[0] = Vector(0,0,0);
    start[1] = Vector(0,18,0);
    start[2] = Vector(-2,16,0);
    start[3] = Vector(2,16,0);
    start[4] = Vector(0,14,0);
    start[5] = Vector(4,14,0);
    start[6] = Vector(-4,14,0);

    start[7] = start[1] * -1;
    start[8] = start[2] * -1;
    start[9] = start[3] * -1;
    start[10] = start[4] * -1;
    start[11] = start[5] * -1;
    start[12] = start[6] * -1;

    for(int i = 0; i < anzKugeln; i++)
    {
        if(i == 0)
            kugel[i] = Kugel(0.7f, radius); //gewicht für meine Kugel
        else
            kugel[i] = Kugel(0.3f, radius);

        kugel[i].pos = start[i];
    }

    schraege[0] = Schraege(sizey/5*3, sizey/5, 0.015f); //obere Schräge
    schraege[1] = Schraege(sizey/5*-1, sizey/5*3*-1, -0.015f); //untere schräge

    //Zylindervariablen
    float zhoehe = height2;
    float zradius = 1;

    zylinder[0] = Zylinder(Vector(sizex,0.0f,0), zradius,zhoehe);
    zylinder[1] = Zylinder(Vector(-sizex,0.0f,0), zradius,zhoehe);
    zylinder[2] = Zylinder(Vector(sizex,sizey,0), zradius,zhoehe);
    zylinder[3] = Zylinder(Vector(-sizex,sizey,0), zradius,zhoehe);
    zylinder[4] = Zylinder(Vector(sizex,-sizey,0), zradius,zhoehe);
    zylinder[5] = Zylinder(Vector(-sizex,-sizey,0), zradius,zhoehe);
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

float betrag(float a)
{
    if(a < 0) a = -a;

    return a;
}

void reibung(Vector &dir, Vector pos, float anfang, float ende)
{
    //Keine Reibung wenn an der Schräge!

    if(pos.y < ende || pos.y > anfang)
    {
        float a = 0.02f; //Grenze zur stärkeren Reibung

        float b = 0.99f; //Reibungsfaktor schnell
        float c = 0.9; //Reibungsfaktor langsam

        if(betrag(dir.x) > a)
            dir.x = dir.x * b;
        else
            dir.x = dir.x * c;

        if(betrag(dir.y) > a)
            dir.y = dir.y * b;
        else
            dir.y = dir.y * c;


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

float kugelHoehe(float y, float hoehe, float sizey, float radius)
{
    float z;

    //5 Fälle, oben, schief-oben, mitte, schief-mitte, unten

    float m1 = hoehe/ (sizey/5*3 - sizey/5) * -1;
    float m2 = hoehe/ (sizey/5*-3 - sizey/-5) * -1;


    if(y > sizey/5*3) //oben
    {
        z = 0;
    }
    else if(y < sizey/5*-3) //unten
    {
        z = 0;
    }
    else if(y > sizey/-5 && y < sizey/5) //mittig
    {
        z = hoehe;
    }
    else if(y > sizey/5 && y < sizey/5*3) //schräge oben
    {
        float b = -6*radius*hoehe;
        z = (y+b)*m1;
    }
    else if(y < sizey/5*-1 && y > sizey/5*-3) //schräge unten
    {
        float b = 6*radius*hoehe;
        z = (y+b)*m2;
    }

    //z = (y+b)*m;

    //qDebug() << z;

    return z;

}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    /*
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // For wireframe replace GL_FILL with GL_LINE
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    */

    GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
    GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

    glEnable(GL_LIGHT1);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glOrtho(-10,10,-20,20, -100,100);

    glPushMatrix();
    glColor3f(1,1,1);

    // Apply rotation angles

    glRotatef(rotx, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(roty, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(rotz, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    // Apply scaling
    float scale = zoom/100.0;
    glScalef( scale, scale, scale ); // Scale along all axis

    //Zeichen Bänder
    drawQuad(sizex,sizey, height2, false);
    drawQuad(sizex,-sizey,height2, false);
    drawQuad(sizex,sizey,height2, true);
    drawQuad(-sizex,sizey,height2, true);

    //Boden zeichnen
    float part = sizey/5; //Bord soll gefüntelt werden

    glColor3f(0,1,0);
    drawGround(sizex, 5*part, 3*part, 0, 0);

    glColor3f(1,1,0);
    drawGround(sizex, 3*part, 1*part, 0, height);

    glColor3f(0,1,1);
    drawGround(sizex, 1*part, -1*part, height, height);

    glColor3f(1,1,0);
    drawGround(sizex, -3*part, -1*part, 0, height);

    glColor3f(0,1,0);
    drawGround(sizex, -5*part, -3*part, 0, 0);


    //Zylinder zeichnen
    for(int i = 0; i < anzZylinder; i++)
    {
        glPushMatrix();

        glTranslatef(zylinder[i].pos.x, zylinder[i].pos.y, zylinder[i].pos.z);

        drawZylinder(zylinder[i].radius, zylinder[i].hoehe);

        glPopMatrix();

    }

    const float speed = 0.001 * 1.3f;
    //const float ebenenKonst = 0.01;
    //float radius = 1;

    //Kugel Objects
    for(int i = 0; i < anzKugeln; i++)
    {

         if(kugel[i].del == false || i == 0)
         {
             glPushMatrix();

                if(i == 0)
                    glColor3f(0,0,1);
                else
                    glColor3f(1,0,0);

                if( i == 0 && uppos.x() != 0 && uppos.y() != 0)
                {
                    kugel[i].dir.x = (float)(uppos.x() - lastpos.x()) * speed;
                    kugel[i].dir.y = -(uppos.y() - lastpos.y()) * speed;

                    uppos.setX(0);
                    uppos.setY(0);
                }

                //Schräge
                for(int j = 0; j < anzSchraege; j++)
                {
                    if(kugel[i].pos.y < schraege[j].anfang && kugel[i].pos.y > schraege[j].ende)
                    {
                        kugel[i].dir.y += schraege[j].sconst;
                    }
                }

                kugel[i].pos.x += kugel[i].dir.x;
                kugel[i].pos.y += kugel[i].dir.y;
                kugel[i].pos.z = kugelHoehe(kugel[i].pos.y, height, sizey, radius) + radius;

                drawKugel(radius,kugel[i].pos.x,kugel[i].pos.y,kugel[i].pos.z);

            glPopMatrix();
         }
    }

    //Kollision der Kugel
    for(int j = 0; j < anzKugeln; j++)
    {
        if(kugel[j].del == false || j == 0)
        {

            //Kollision mit anderen Kugeln
            for(int i = 0; i < anzKugeln; i++)
            {
                float abstand = sqrt(pow(kugel[i].pos.x-kugel[j].pos.x,2) + pow(kugel[i].pos.y-kugel[j].pos.y,2));
                float margin = 0.01f; //Damit die Kugeln nicht ineinander gehen, margin error

                if(i != j && kugel[i].del == false)
                {
                    //Kollision der Kugeln
                    if(abstand <= radius*2 + margin && kugel[i].verhakt[j] == false)
                    {
                        //do something

                        Vector X = kugel[i].pos;
                        Vector Y = kugel[j].pos;
                        Vector a = X-Y;
                        Vector VX = kugel[i].dir;
                        Vector VY = kugel[j].dir;

                        //Vector S = 0.5f * (X-Y) ;
                        Vector VS = ((float)(kugel[i].masse)*VX+(float)(kugel[j].masse)*VY);

                        Vector VX1 = VX-VS;
                        Vector VY1 = VY-VS;

                        Vector VX2 = 2.0f * ((a*VX1) / a.norm()*a.norm()) * a;
                        Vector VY2 = 2.0f * ((a*VY1) / a.norm()*a.norm()) * a;

                        const float impulserhaltung = -0.185;
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

            //reibung
            for(int k = 0; k < anzSchraege && kugel[j].del == false; k++)
            {
                reibung(kugel[j].dir, kugel[j].pos, schraege[k].anfang, schraege[k].ende);
            }

            //Kollision mit Zylindern
            for(int k = 0; k < anzZylinder && kugel[j].del == false; k++)
            {
                Vector vec;
                float abstand;

                if (k <= 1) //Zylinder in der Mitte
                    vec = Vector(zylinder[k].pos - kugel[j].pos) + Vector(0,0,radius+height);
                else
                    vec = Vector(zylinder[k].pos - kugel[j].pos) + Vector(0,0,radius);

                abstand = vec.norm() - zylinder[k].radius - kugel[j].radius;

                if(abstand <= 0 && j != 0) //Lösche normale Kugeln
                {
                    kugel[j].del = true;
                }
                else if(abstand <= 0 && j == 0) //resette meine Kugel
                {
                    kugel[j].pos = Vector(0,0,0);
                    kugel[j].dir = Vector(0,0,0);
                }
            }
        }
    }

    //Kollisionsüberprüfung Rand
    for(int i = 0; i < anzKugeln; i++)
    {
        if(kugel[i].pos.x-radius <= -sizex && kugel[i].randVerhakt[0] == false)
        {
            kugel[i].dir.x = -kugel[i].dir.x;
            kugel[i].randVerhakt[0] = true;
        }
        if (kugel[i].pos.x +radius>= sizex && kugel[i].randVerhakt[1] == false)
        {
            kugel[i].dir.x = -kugel[i].dir.x;
            kugel[i].randVerhakt[1] = true;
        }
        if(kugel[i].pos.y-radius <= -sizey && kugel[i].randVerhakt[2] == false)
        {
            kugel[i].dir.y = -kugel[i].dir.y;
            kugel[i].randVerhakt[2] = true;
        }
        if (kugel[i].pos.y+radius >= sizey && kugel[i].randVerhakt[3] == false)
        {
            kugel[i].dir.y = -kugel[i].dir.y;
            kugel[i].randVerhakt[3] = true;
        }

        //enthaken
        if(kugel[i].pos.x-radius > -sizex)
        {
            kugel[i].randVerhakt[0] = false;
        }
        if (kugel[i].pos.x +radius < sizex)
        {
            kugel[i].randVerhakt[1] = false;
        }
        if(kugel[i].pos.y-radius > -sizey)
        {
            kugel[i].randVerhakt[2] = false;
        }
        if (kugel[i].pos.y+radius < sizey)
        {
            kugel[i].randVerhakt[3] = false;
        }
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
