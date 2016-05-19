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
    int maxRand;

    bool verhakt[13]; // immer gleich anzKugeln

    bool randVerhakt[4];
};

#endif // KUGEL_H
