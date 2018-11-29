#ifndef __iVECTOR__H
#define ___iVECTOR__H


class Vector {
public:
    int size;
    double *elem;

    // Constructors
    Vector() : size(0), elem(nullptr) {};
    Vector(double *values, int len);

    // Desctructor
    ~Vector();

    // public methods
    const void print();
    double dotP(const Vector &x, const Vector &y);
    Vector* crossP(Vector x, Vector y);
    const Vector& operator+(const Vector &x);
    const Vector& operator*(const Vector &other);
};
#endif
