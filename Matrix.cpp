#include <cmath>
#include <iostream>
#include "Vector.h"
#include "Matrix.h"

Matrix::Matrix(const Matrix& origin) {
    this->cols = origin.cols;
    this->rows = origin.rows;

    this->elem = new double*[this->rows];
    for(int i = 0; i < this->rows; i++) {
        this->elem[i] = new double[this->cols];
        for(int j = 0; j < this->cols; j++) {
            this->elem[i][j] = origin[i][j];
        }
    }
}

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    this->elem = new double*[this->rows];
    for(int i = 0; i < this->rows; i++) {
        this->elem[i] = new double[this->cols];
    }
}

Matrix::Matrix(int squareSize) {
    this->rows = squareSize;
    this->cols = squareSize;
    this->elem = new double*[this->rows];
    for(int i = 0; i < this->cols; i++) {
        this->elem[i] = new double[this->cols];
    }
}

Matrix::Matrix(Vector row[], int rows) {
    this->rows = rows;
    this->cols = row[0].size;

    this->elem = new double*[this->rows];
    for(int i = 0; i < this->rows; i++) {
        this->elem[i] = new double[this->cols];
        for(int j = 0; j < this->cols; j++) {
            this->elem[i][j] = row[i].elem[j];
        }
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
        Vector tmp(this->elem[i], this->cols);
        std::cout << tmp << '\n';
    }
}

void Matrix::LUDecomposition(Matrix& L, Matrix& U) {
    if(this->rows != this->cols) {
        std::cout << "ERROR: LU ecomposition is valid for square matrix.\n";
        exit(1);
    }

    int n = this->rows;
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
            U.elem[i][k] = this->elem[i][k] - sum;
        }
        for(int k = i; k < n; k++) {
            if(i == k) {
                L.elem[i][i] = 1;
            } else {
                sum = 0;
                for(int j = 0; j < i; j++) {
                    sum += L.elem[k][j] * U.elem[j][i];
                }
                L.elem[k][i] = (this->elem[k][i] - sum) / U.elem[i][i];
            }
        }
    }
}
void rowSwap(double *arr1, double *arr2) {
    double *tmp = arr2;
    arr2 = arr1;
    arr1 = tmp;
}

Matrix& Matrix::pivoting(Matrix& P) {
    if(P.rows != P.cols) {
        std::cout << "ERROR: P must be square Matrix.\n";
        exit(1);
    } else {
        for(int i = 0; i < P.rows; i++) {
            for(int j = 0; j < P.cols; j++) {
                P.elem[i][j] = (i == j) ? 1 : 0;
            }
        }
    }

    Matrix pivotted = *this;
    int cnt = 0;
    int n = this->cols, imax = 0;
    double maxA = 0;
    double *tmp = 0, *tmpP = 0;
    for(int i = 0; i < n; i++) {
        maxA = 0;
        imax = i;
        for(int k = i; k < n; k++) {
            if(std::abs(pivotted.elem[k][i]) > maxA) {
                maxA = std::abs(pivotted.elem[k][i]);
                imax = k;
            }
        }

        if(imax != i) {
            // swap
            tmp = pivotted.elem[i];
            pivotted.elem[i] = pivotted.elem[imax];
            pivotted.elem[imax] = tmp;

            // swap P
            tmpP = P.elem[i];
            P.elem[i] = P.elem[imax];
            P.elem[imax] = tmpP;
        }
    }
    Matrix *pnew = new Matrix(pivotted);

    return *pnew;
}

Matrix& Matrix::pivoting() {
    Matrix P(this->rows, this->cols);
    /*
    Matrix *pnew = new Matrix(this->rows, this->cols);
    *pnew = this->pivoting(P);
    */

    return this->pivoting(P);
}

void Matrix::LUDecomposition(Matrix& L, Matrix& U, Matrix& P){
    if(this->rows != this->cols) {
        std::cout << "ERROR: PLU ecomposition is valid for square matrix.\n";
        exit(1);
    }
    Matrix *PA = new Matrix(this->rows);
    *PA = this->pivoting(P);
    PA->LUDecomposition(L, U);
}


double Matrix::determinant() {
    if(this->rows != this->cols) {
        std::cout << "ERROR: Matrix should be square matrix to calculate determinant\n";
        exit(1);
    }
    Matrix *pnew = this;
    Matrix L(3);
    Matrix U(3);
    Matrix P(3);
    pnew->LUDecomposition(L, U, P);
    double detLower = 1, detUpper = 1, detP = 1;
    for(int i = 0; i < this->rows; i++) {
        detLower *= L.elem[i][i];
        detUpper *= U.elem[i][i];
        detP *= P.elem[i][i];
    }
    return detLower * detUpper * detP;
}

bool Matrix::isSingular() {
    return (this->determinant() == 0);
}

Matrix& Matrix::transpose() {
    Matrix *trans = new Matrix(this->cols, this->rows);

    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            trans->elem[j][i] = this->elem[i][j];
        }
    }
    return *trans;
}

Vector& Matrix::operator*(const Vector& rhs) {
    /***** rhs is regarded as column vector! *****/
    if(this->cols != rhs.size) {
        std::cout << "ERROR: cols of matrix and size of vector does not match.\n";
        exit(1);
    }

    Vector *ans = new Vector(rhs.size);
    double elem = 0;
    for(int i = 0; i < this->rows; i++) {
        elem = 0;
        for(int j = 0; j < this->cols; j++) {
            elem += this->elem[i][j] * rhs[j];
        }
        ans->elem[i] = elem;
    }
    return *ans;
}

Vector& Matrix::solve(Vector& colVec) {
    if(this->rows != this->cols) {
        std::cout << "ERROR: To sovle eq., Matrix must be sqaure matrix.\n";
        exit(1);
    }
    int size = this->rows;

    Matrix P(size);
    Matrix PA = this->pivoting(P);

    Matrix L(size);
    Matrix U(size);
    PA.LUDecomposition(L, U);

    Vector b = P * colVec;
    Vector z(size);
    Vector x(size);

    for(int i = 0; i < size; i++) {
        double sum = 0;
        for(int j = 0; j < i; j++) {
            sum += L[i][j] * z[j];
        }
        z[i] = (b[i] - sum) / L[i][i];
    }
    // z.print();
    for(int i = size - 1; i >= 0; i--) {
        double sum = 0;
        for(int j = size - 1; j >= i; j--) {
            sum += U[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / U[i][i];
    }
    return *(new Vector(x.elem, x.size));
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
        Vector vnew(M.elem[i], M.cols);
        os << vnew << "\n";
    }
    return os;
}

Matrix& Matrix::inverse() {
    if(this->cols != this->rows) {
        std::cout << "ERROR: Matrix must be square to get inverse." << '\n';
        exit(1);
    }
    int n = this->cols;
    Vector *ans = new Vector[n];
    Vector unit(n);
    Vector z(n);
    Matrix L(n);
    Matrix U(n);
    Matrix P(n);
    this->LUDecomposition(L, U, P);
    for(int i = 0; i < n; i++) {
        unit.elem = P.elem[i];
        ans[i] = U.solve(L.solve(unit));
    }
    Matrix *pnew = new Matrix(ans, n);

    return *pnew;
}
