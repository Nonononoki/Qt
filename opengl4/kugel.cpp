#include "kugel.h"
#include "oglwidget.h"


Kugel::Kugel()
{
    anzKugeln = 2;
    maxRand = 4;

    for(int i = 0; i < anzKugeln; i++)
    {
        verhakt[i] = true;
    }

    for(int i = 0; i < maxRand; i++)
    {
        randVerhakt[i] = true;
    }
}



