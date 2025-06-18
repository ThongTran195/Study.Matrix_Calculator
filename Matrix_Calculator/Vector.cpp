#include "vector.h"
#include <iostream>
#include <cmath>
#include <cassert> 
using namespace std;

BaseVector::BaseVector(int size) : entry(size) {}

void BaseVector::input()
{
    int size;
    cout << "Enter the size of the vector: ";
    while (true)
    {
        cin >> size;
        if (cin.fail() || size <= 0)
        {
            cout << "Invalid input. Please enter a positive integer: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else
        {
            break;
        }
    }
    entry.resize(size);
    for (int i = 0; i < size; ++i)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> entry[i];
    }
}

void BaseVector::print(const string& name) const
{
    cout << name << " = [ ";
    for (double val : entry)
    {
        cout << val << " ";
    }
    cout << "]" << endl;
}

double BaseVector::magnitude() const
{
    double sum = 0;
    for (double val : entry) sum += val * val;
    return sqrt(sum);
}

Vector::Vector(int size) : BaseVector(size) {}

Vector Vector::operator+(const Vector& other) const
{
    while (entry.size() != other.entry.size())
    {
        cout << "Vectors must be of the same size to add. Please re-enter the size of the second vector: \n";
        const_cast<Vector&>(other).input();
    }
    Vector result(entry.size());
    for (int i = 0; i < entry.size(); ++i) result.entry[i] = entry[i] + other.entry[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const
{
    while (entry.size() != other.entry.size())
    {
        cout << "Vectors must be of the same size to subtract. Please re-enter the size of the second vector: \n";
        const_cast<Vector&>(other).input();
    }
    Vector result(entry.size());
    for (int i = 0; i < entry.size(); ++i) result.entry[i] = entry[i] - other.entry[i];
    return result;
}

Vector Vector::operator*(double scalar) const
{
    Vector result(entry.size());
    for (int i = 0; i < entry.size(); ++i) result.entry[i] = entry[i] * scalar;
    return result;
}

double Vector::dot(const Vector& other) const
{
    while (entry.size() != other.entry.size())
    {
        cout << "Vectors must be of the same size for dot product. Please re-enter the size of the second vector: \n";
        const_cast<Vector&>(other).input();
    }
    double result = 0;
    for (int i = 0; i < entry.size(); ++i) result += entry[i] * other.entry[i];
    return result;
}

Vector Vector::normalize() const
{
    double mag = magnitude();
    assert(mag != 0 && "Cannot normalize a zero vector.");
    return *this * (1 / mag);
}

Vector Vector::cross(const Vector& other) const
{
    while (entry.size() != 3 || other.entry.size() != 3)
    {
        cout << "Cross product only works for 3D vectors. Please re-enter the size of the vectors: \n";
        const_cast<Vector&>(*this).input();
        const_cast<Vector&>(other).input();
    }
    Vector result(3);
    result.entry[0] = entry[1] * other.entry[2] - entry[2] * other.entry[1];
    result.entry[1] = entry[2] * other.entry[0] - entry[0] * other.entry[2];
    result.entry[2] = entry[0] * other.entry[1] - entry[1] * other.entry[0];
    return result;
}

double Vector::angle(const Vector& other) const
{
    while (entry.size() != other.entry.size())
    {
        cout << "Vectors must be of the same size to compute the angle. Please re-enter the size of the second vector: \n";
        const_cast<Vector&>(other).input();
    }
    double dot_product = dot(other);
    double mag_product = magnitude() * other.magnitude();
    assert(mag_product != 0 && "Cannot compute angle with a zero vector.");
    return acos(dot_product / mag_product) * 180.0 / PI;
}

Vector Vector::projection(const Vector& other) const
{
    while (entry.size() != other.entry.size())
    {
        cout << "Vectors must be of the same size for projection. Please re-enter the size of the second vector: \n";
        const_cast<Vector&>(other).input();
    }
    double dot_product = dot(other);
    double other_dot = other.dot(other);
    assert(other_dot != 0 && "Cannot project onto a zero vector.");
    return other * (dot_product / other_dot);
}



void actionTwo_Vector()
{
    system("cls");
    int choice;
    bool running = true;

    while (running) {
        cout << "\nVector Calculator Menu" << endl;
        cout << "1. Add two vectors" << endl;
        cout << "2. Subtract two vectors" << endl;
        cout << "3. Multiply vector by scalar" << endl;
        cout << "4. Compute dot product of two vectors" << endl;
        cout << "5. Compute vector magnitude (norm)" << endl;
        cout << "6. Normalize a vector" << endl;
        cout << "7. Cross product of two 3D vectors" << endl;
        cout << "8. Angle between two vectors" << endl;
        cout << "9. Projection of one vector onto another" << endl;
        cout << "10. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        if (choice == 10)
        {
            system("cls");
            break;
        }

        try {
            Vector v1, v2;
            switch (choice) {
            case 1: v1.input(); v2.input(); (v1 + v2).print("Result"); break;
            case 2: v1.input(); v2.input(); (v1 - v2).print("Result"); break;
            case 3: v1.input(); double scalar; cin >> scalar; (v1 * scalar).print("Result"); break;
            case 4: v1.input(); v2.input(); cout << "Dot Product: " << v1.dot(v2) << endl; break;
            case 5: v1.input(); cout << "Magnitude: " << v1.magnitude() << endl; break;
            case 6: v1.input(); v1.normalize().print("Normalized Vector"); break;
            case 7: v1.input(); v2.input(); v1.cross(v2).print("Cross Product"); break;
            case 8: v1.input(); v2.input(); cout << "Angle: " << v1.angle(v2) << " degrees" << endl; break;
            case 9: v1.input(); v2.input(); v1.projection(v2).print("Projection"); break;
            default: cout << "Invalid choice.\n"; break;
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}