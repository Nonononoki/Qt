#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector
{
public:

    Vector();
    Vector(float x, float y, float z);

    float x;
    float y;
    float z;

    //float norm();
    float norm()
    {
        return sqrt(this->x * this->x + this->y*this->y + this->z*this->z);
    }

    friend Vector operator+(Vector a, float b);
    friend Vector operator+(Vector a, Vector b);
    friend Vector operator-(Vector a, Vector b);
    friend Vector operator-(Vector a, float b);
    friend float operator*(Vector a, Vector b);
    friend Vector operator*(float a, Vector b);
    friend Vector operator/(Vector a, float b);
    friend Vector operator*(Vector a, float b);

    Vector cross(Vector a)
    {
        return Vector ( a.y*this->z - a.z*this->y,
                        a.z*this->x - a.x*this->z,
                        a.x*this->y - a.y*this->x );
    }
};


#endif // VECTOR_H
