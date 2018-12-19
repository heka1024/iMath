#ifndef __MATRIX__H
#define __MATRIX__H
#include <iostream>
#include <vector>
#include "Vector.h"

class Matrix {
public:
    std::vector<Vector> elem;
    int rows, cols;

    // Constructors
    Matrix() : rows(0), cols(0) {};
    Matrix(int rows, int cols);
    Matrix(std::initializer_list<Vector> l);
    Matrix(const Matrix& origin);
    // Desctructor
    // ~Matrix();

    // public methods
    const void print();
    Matrix& pivoting(Matrix& P);
    Matrix& pivoting();
    void LUDecomposition(Matrix& L, Matrix& U);
    void LUDecomposition(Matrix& P, Matrix& L, Matrix& U);
    double determinant();
    bool isSingular();
    Matrix& transpose();
    Matrix& inverse();
    Vector& solve(Vector& colVec);

    Matrix& operator+(const Matrix& x);
    Matrix& operator-(const Matrix& x);
    Matrix& operator*(Matrix& other);
    Vector& operator*(const Vector& rhs);
    Vector& operator[](int n);
    const Vector& operator[](int n) const;
};
std::ostream& operator<<(std::ostream& os, const Matrix& M);
std::ostream& operator<<(std::ostream& os, Matrix& M);
#endif
