#ifndef __MATRIX__H
#define __MATRIX__H
#include <iostream>
#include "Vector.h"

class Matrix {
public:
    double **elem;
    int rows, cols;

    // Constructors
    Matrix() : rows(0), cols(0), elem(nullptr) {};
    Matrix(int rows, int cols);
    Matrix(double **values, int rows, int cols);

    // Desctructor
    ~Matrix();

    // public methods
    const void print();
    const double& determinant(const Matrix& x);

    const Matrix& operator+(const Matrix& x);
    const Matrix& operator-(const Matrix& x);
    const Matrix& operator*(const Matrix& other);
    Vector& operator[](int n);
    const Vector& operator[](int n) const;
};
std::ostream& operator<<(std::ostream& os, Matrix& M);
#endif
