// camera class

#ifndef SCAMERA_H
#define SCAMERA_H

#include <string>

#include "../include/sPoint.h"

class sCamera
{
    private:
    sPoint O; // center
    sPoint F; // forward
    sPoint U; // up
    sPoint R; // right

    /*mode: 1-OX, 2-OY, 3-OZ*/
    void rotate(double alpha, int mode); // alpha in degree

    double c(double a); // cos
    double s(double a); // sin
    double c1(double a); // 1 - cos

    public:
    sCamera();
    void move(double x, double y, double z);
    void moveForward(double s);
    void moveBack(double s);
    void moveRight(double s);
    void moveLeft(double s);
    void moveUp(double s);
    void moveDown(double s);

    void rotateOX(double a); // around R, a in degree
    void rotateOY(double a); // around F, a in degree
    void rotateOZ(double a); // around U, a in degree

    sPoint o() const;
    sPoint f() const;
    sPoint u() const;
    sPoint r() const;

    sPoint vf() const;
    sPoint vu() const;
    sPoint vr() const;

    std::string print() const;
};

#endif // SCAMERA_H
