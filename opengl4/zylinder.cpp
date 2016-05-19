#include "zylinder.h"

Zylinder::Zylinder()
{   
    pos = Vector(0,0,0);
    radius = 1;
    hoehe = 1;   
}


Zylinder::Zylinder(Vector vec, float r, float h)
{
    pos = vec;
    radius = r;
    hoehe = h;
}


