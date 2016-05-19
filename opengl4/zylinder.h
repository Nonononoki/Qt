#ifndef ZYLINDER_H
#define ZYLINDER_H

#include "vector.h"

class Zylinder
{
public:

    Zylinder();
    Zylinder(Vector vec, float r, float h);

    Vector pos;
    float radius;
    float hoehe;
};

#endif // ZYLINDER_H
