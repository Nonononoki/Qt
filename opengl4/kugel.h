#ifndef KUGEL_H
#define KUGEL_H

#include "vector.h"
#include <QDebug>
#include <cmath>

class Kugel
{
public:
    Kugel();

    Vector pos;
    Vector dir;

    int anzKugeln;
    bool verhakt[2]; // immer gleich anzKugeln
};

#endif // KUGEL_H
