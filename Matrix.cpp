#include <cmath>
#include <iostream>
#include "Vector.h"
#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->elem = new double*[this->rows];
    for(int i = 0; i < this->cols; i++) {
        this->elem[i] = new double[this->cols];
    }
}

Matrix::Matrix(double **values, int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->elem = new double*[rows];

    int i, j;
    for(i = 0; this->rows > i; i++) {
        elem[i] = new double[cols];
        for(j = 0; cols > j; j++) {
            this->elem[i][j] = values[i][j];
        }
    }
}

Matrix::~Matrix() {
    delete elem;
}

const void Matrix::print() {
    std::cout << rows << " * " << cols << " Matrix\n";
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols - 1; j++) {
            std::cout << this->elem[i][j] << ", ";
        }
        std::cout << this->elem[i][this->cols - 1];
    }
}

void Matrix::LUDecomposition(Matrix& M, Matrix& L, Matrix& U) {
    int n = M.rows;
    double sum = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            L.elem[i][j] = 0;
            U.elem[i][j] = 0;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int k = i; k < n; k++) {
            sum = 0;
            for(int j = 0; j < i; j++) {
                sum += L.elem[i][j] * U.elem[j][k];
            }
            U.elem[i][k] = M.elem[i][k] - sum;
        }
        for(int k = i; k < n; k++) {
            if(i == k) {
                L.elem[i][i] = 1;
            } else {
                sum = 0;
                for(int j = 0; j < i; j++) {
                    sum += L.elem[k][j] * U.elem[j][i];
                }
                L.elem[k][i] = (M.elem[k][i] - sum) / U.elem[i][i];
            }
        }
    }
}

const double& determinant(const Matrix& M) {
    if(M.rows != M.cols) {
        std::cout << "ERROR: Matrix should be square matrix to calculate determinant\n";
        exit(1);
    }
    // implementations
}

const Matrix& Matrix::operator+(const Matrix& x) {
    Matrix *pnew = new Matrix(this->rows, this->cols);

    for(int i = 0; pnew->rows > i; i++) {
        for(int j = 0; pnew->cols > j; j++) {
            pnew->elem[i][j] = this->elem[i][j] + x.elem[i][j];
        }
    }

    return *pnew;
}

const Matrix& Matrix::operator-(const Matrix& x) {
    Matrix *pnew = new Matrix(this->rows, this->cols);

    for(int i = 0; pnew->rows > i; i++) {
        for(int j = 0; pnew->cols > j; j++) {
            pnew->elem[i][j] = this->elem[i][j] - x.elem[i][j];
        }
    }

    return *pnew;
}

const Matrix& Matrix::operator*(const Matrix& other) {
    if(this->cols != other.rows) {
        std::cout << "ERROR: Matrix mult error. Please check size of matrix.\n";
        exit(1);
    }
    Matrix *mult = new Matrix(this->rows, other.cols);
    int i, j, k, lineSize = this->cols;
    for(i = 0; i < mult->rows; i++) {
        for(j = 0; j < mult->cols; j++) {
            // mult per line
            for(k = 0, mult->elem[i][j] = 0; k < lineSize; k++) {
                mult->elem[i][j] += this->elem[i][k] * other.elem[k][j];
            }
        }
    }

    return *mult;
}

Vector& Matrix::operator[](int n) {
    if (n >= this->rows || n < 0) {
        std::cout << "ERROR: Out of Bound\n";
        exit(1);
    }
    Vector *row = new Vector(this->cols);
    for(int i = 0; i < this->cols; i++) {
        row->elem[i] = this->elem[n][i];
    }

    return *row;
}

const Vector& Matrix::operator[](int n) const {
    if (n >= this->rows || n < 0) {
        std::cout << "ERROR: Out of Bound\n";
        exit(1);
    }
    Vector *row = new Vector(this->cols);
    for(int i = 0; i < this->cols; i++) {
        row->elem[i] = this->elem[n][i];
    }

    return *row;
}

std::ostream& operator<<(std::ostream& os, Matrix& M) {
    int i, j;
    for(int i = 0; i < M.rows; i++) {
        for(int j = 0; j < M.cols - 1; j++) {
            os << M.elem[i][j] << ", ";
        }
        os << M.elem[i][M.cols - 1] << '\n';
    }
    return os;
}
