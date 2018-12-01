#include "Vector.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>

Vector::Vector(int len) {
    this->size = len;
    this->elem = new double[len];
}

Vector::Vector(std::initializer_list<double> elem) {
    this->size = elem.size();
    this->elem = new double[this->size];
    int cnt = 0;
    for (auto i : elem) {
        this->elem[cnt] = i;
        cnt++;
    }
}

Vector::Vector(double *values, int len) {
    this->size = len;
    this->elem = new double[len];
    for(int i = 0; len > i; i++) {
        this->elem[i] = values[i];
    }
}

Vector::~Vector() {
    delete elem;
}

const void Vector::print() {
    std::cout << "size :: " << this->size;
    std::cout << "[";

    for(int i = 0; i < this->size - 1; i++) {
        std::cout << this->elem[i] << ", ";
    }

    std::cout << this->elem[this->size - 1] << "]\n";
}

double Vector::dotP(const Vector &x, const Vector &y) {
    if(x.size != y.size) {
        exit(1);
    } else {
        double ans = 0;
        for(int i = 0; x.size > i; i++) {
            ans += x.elem[i] * y.elem[i];
        }
        return ans;
    }
}

int Vector::maxElemIdx() {
    int maxIdx = 0;
    for(int i = 0; i < this->size; i++) {
        if (this->elem[i] > this->elem[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

int Vector::minElemIdx() {
    int minIdx = 0;
    for(int i = 0; i < this->size; i++) {
        if (this->elem[i] < this->elem[minIdx]) {
            minIdx = i;
        }
    }
    return minIdx;
}

const Vector& Vector::operator-(const Vector &x) {
    Vector *pnew = new Vector(new double[x.size], x.size);


    for(int i = 0; pnew->size > i; i++) {
        pnew->elem[i] = this->elem[i] - x.elem[i];
    }

    return *pnew;
}

const Vector& Vector::operator+(const Vector &x) {
    Vector *pnew = new Vector(new double[x.size], x.size);


    for(int i = 0; pnew->size > i; i++) {
        pnew->elem[i] = x.elem[i] + this->elem[i];
    }

    return *pnew;
}

const Vector& Vector::operator*(const Vector &other) {
    Vector *crossP = new Vector(new double[this->size], this->size);

    crossP->elem[0] = (this->elem[1] * other.elem[2]) - (this->elem[2] * other.elem[1]);
    crossP->elem[1] = (this->elem[2] * other.elem[0]) - (this->elem[0] * other.elem[2]);
    crossP->elem[2] = (this->elem[0] * other.elem[1]) - (this->elem[1] * other.elem[0]);

    return *crossP;
}

double& Vector::operator[](int n) {
    if (n >= this->size || n < 0) {
        std::cout << "ERROR: Out of Bound\n";
        exit(1);
    }

    return this->elem[n];
}


const double& Vector::operator[](int n) const {
    if (n >= this->size || n < 0) {
        std::cout << "ERROR: Out of Bound\n";
        exit(1);
    }

    return this->elem[n];
}

std::ostream& operator<<(std::ostream& os, Vector& v) {
    os << '[';
    for (int i = 0; i < v.size - 1; i++) {
        os << v[i] << ", ";
    }

    os << v[v.size - 1] << ']';
    return os;
}
