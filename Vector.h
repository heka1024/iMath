#ifndef __iVECTOR__H
#define __iVECTOR__H
#include <iostream>
#include <vector>

class Vector {
public:
    std::vector<double> elem;

    // Constructors
    Vector() : elem(0) {};
    Vector(std::initializer_list<double> l);
    Vector(double *values, int len);

    // Desctructor
    ~Vector();

    size_t size();
    const size_t size() const;
    Vector* crossP(Vector x, Vector y);
    Vector& operator+(const Vector &x);
    Vector& operator-(const Vector &x);
    const Vector& operator^(const Vector &other);
    double operator*(const Vector &other);
    double& operator[](int n);
    const double& operator[](int n) const;
};

std::ostream& operator<<(std::ostream& os, Vector& v);
std::ostream& operator<<(std::ostream& os, const Vector& v) ;
#endif
