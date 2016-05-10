#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
public:

    Vector();
    Vector(float x, float y, float z);
    float x;
    float y;
    float z;

    friend Vector operator+(Vector a, float b);
    friend Vector operator+(Vector a, Vector b);
    friend Vector operator-(Vector a, Vector b);
    friend Vector operator-(Vector a, float b);
    friend float operator*(Vector a, Vector b);
    friend Vector operator*(float a, Vector b);
    friend Vector operator/(Vector a, float b);
    friend Vector operator*(Vector a, float b);
};



#endif // VECTOR_H
