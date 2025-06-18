#ifndef VECTOR_HEADER
#define VECTOR_HEADER
#ifndef PI
#define PI 3.1415

#include <vector>
#include <string>

class BaseVector {
protected:
    std::vector<double> entry;

public:
    BaseVector(int size = 0);
    void input(); // input function
    void print(const std::string& name) const; // print the vector
    double magnitude() const; // magnitude (norm) of the vector
};

class Vector : public BaseVector {
public:
    Vector(int size = 0);

    Vector operator+(const Vector& other) const; // add vector
    Vector operator-(const Vector& other) const; // substract vector
    Vector operator*(double scalar) const; // scalar multi


    double dot(const Vector& other) const; // dot product
    Vector normalize() const; // normalize the vector
    Vector cross(const Vector& other) const; // cross product (3D vectors only)
    double angle(const Vector& other) const; // angle between two vectors (in degrees)
    Vector projection(const Vector& other) const; // projection vector onto another
};


void actionTwo_Vector();

#endif // M_PI
#endif // VECTOR_HEADER