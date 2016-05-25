#include "kugel.h"
#include "oglwidget.h"


Kugel::Kugel(float masse, float radius)
{
    anzKugeln = 13;
    maxRand = 4;
    this->del = false;

    this->masse = masse;
    this->radius = radius;

    for(int i = 0; i < anzKugeln; i++)
    {
        verhakt[i] = true;
    }

    for(int i = 0; i < maxRand; i++)
    {
        randVerhakt[i] = true;
    }
}

Kugel::Kugel()
{
   this-> del = false;
}



