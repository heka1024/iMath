#ifndef __MATRIX__H
#define __MATRIX__H
#include <iostream>
#include "Vector.h"

class Matrix {
public:
    double **elem;
    int rows, cols;

    // Constructors
    Matrix(const Matrix& origin);
    Matrix() : rows(0), cols(0), elem(nullptr) {};
    Matrix(int squareSize);
    Matrix(int rows, int cols);
    Matrix(Vector row[], int rows);
    Matrix(double **values, int rows, int cols);

    // Desctructor
    ~Matrix();

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

    const Matrix& operator+(const Matrix& x);
    const Matrix& operator-(const Matrix& x);
    const Matrix& operator*(const Matrix& other);
    Vector& operator*(const Vector& rhs);
    Vector& operator[](int n);
    const Vector& operator[](int n) const;
};
std::ostream& operator<<(std::ostream& os, Matrix& M);
#endif
