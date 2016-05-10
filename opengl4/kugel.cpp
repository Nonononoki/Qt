#include "kugel.h"
#include "oglwidget.h"


Kugel::Kugel()
{
    anzKugeln = 2;

    for(int i = 0; i < anzKugeln; i++)
    {
        verhakt[i] = true;
    }
}



