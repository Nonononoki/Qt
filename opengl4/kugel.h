#ifndef KUGEL_H
#define KUGEL_H

#include "vector.h"
#include <QDebug>
#include <cmath>

class Kugel
{
public:
    Kugel();
    Kugel(float masse, float radius);

    Vector pos;
    Vector dir;

    bool del;

    int anzKugeln;
    int maxRand;
    float radius;

    bool verhakt[13]; // immer gleich anzKugeln

    bool randVerhakt[4];

    float masse;
};

#endif // KUGEL_H
