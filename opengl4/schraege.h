#ifndef SCHRAEGE_H
#define SCHRAEGE_H

#include "vector.h"


class Schraege
{
public:

    Schraege();
    Schraege(float anfang, float ende, float sconst);

    float anfang;
    float ende;
    float sconst;
};

#endif // SCHRAEGE_H
