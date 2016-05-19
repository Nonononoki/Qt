#include "vector.h"

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector operator+(Vector a, float b)
{
    return Vector(a.x+b, a.y+b, a.z+b);
}

Vector operator+(Vector a, Vector b)
{
    return Vector(a.x+b.x, a.y+b.y, a.z+b.z);
}

Vector operator-(Vector a, float b)
{
    return Vector(a.x-b, a.y-b, a.z-b);
}

Vector operator-(Vector a, Vector b)
{
    return Vector(a.x-b.x, a.y-b.y, a.z-b.z);
}

Vector operator/(Vector a, float b)
{
    return Vector(a.x/b, a.y/b, a.z/b);
}

Vector operator*(float a, Vector b)
{
    return Vector(a*b.x, a*b.y, a*b.z);
}

Vector operator*(Vector a, float b)
{
    return Vector(a.x*b, a.y*b, a.z*b);
}

float operator*(Vector a, Vector b)
{
    float dot = (a.x*b.x + a.y*b.y + a.z*b.z);
    return dot;
}


