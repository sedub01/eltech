#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <cmath>
#include <iostream>
#include <limits>

#include "../include/drawField.h"

#include "../include/sPoint.h"
#include "../include/sup.h"
#include "../include/matrix.h"

DrawField::DrawField(QWidget *parent,
      double x1, double y1, double z1, 
      double x2, double y2, double z2, 
      double x3, double y3, double z3,
      double x4, double y4, double z4
    ) : QWidget(parent), cam(), p1(x1, y1, z1), p2(x2, y2, z2), p3(x3, y3, z3), p4(x4, y4, z4), M_rotate(3, 3)
{
    resize(W, H);
    this->setStyleSheet("background-color: rgb(255,255,255); margin:0px; border:1px solid rgb(255, 0, 0); ");

    // settings (constant numbers) for movveing camera (step is constant)

    /*9*Arrow_UP
    9*Arrow_Right
    9*Space
    27*A
    7*W*/
    cam.moveForward(2*9);
    cam.moveRight(2*9);
    cam.move(0.0, 0.0, 2*9);
    cam.rotateOZ(5 * 27);
    cam.rotateOX(-5 * 7);

    angleX = 0;
    angleY = 0;
    M_rotate_refresh(); // update rotating
    
    C_ = NULL;
    refresh_C_(); // update

    display = new int*[H]; // screen height
    for(size_t li = 0; li < H; ++li)
    {
        display[li] = new int[W]; // for each high point is with point (it's for output)
    }
    refresh_display(); // update display
}

// destructor

DrawField::~DrawField()
{
    if(C_ != NULL)
    {    
        delete C_; // C is matrix
    }

    for(size_t li = 0; li < H; ++li)
    {
        delete display[li];
    }
    delete display;
}

// event painting (first painting & reaction on push button)
 
void DrawField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    refresh_display();

    // coordinates lines
    putLine3D(sPoint(0, 0, 0), sPoint(30, 0, 0));
    putLine3D(sPoint(0, 0, 0), sPoint(0, 30, 0));
    putLine3D(sPoint(0, 0, 0), sPoint(0, 0, 30));

    drawBilinearSurface(); // bilenear surface drawing

    QPainter qp(this); // paint points
    for(size_t li = 0; li < H; ++li)
    {
        for(size_t lj = 0; lj < W; ++lj)
        {
            if(display[li][lj] != 0)
            {
                qp.drawPoint(lj, li); // if display afford it, paint points
            }
        }
    }

    /*
    QPainter qp(this);
    for(size_t li = 0; li < H; ++li)
    {
        for(size_t lj = 0; lj < W; ++lj)
            cout << display[li][lj];
        cout << endl;
    }*/
}

// pressing buttons events make changes in drawing + refreshing it immediately
// AWSDQE -- camera turn
// <up><down><left><right> -- move
// HUJK -- move relatively coordinate start
// YI -- up/down move locally
// C<space> -- up/down relatively coordinate start
// RT -- rounding relatively OY
// FG -- rounding relatively OX

void DrawField::keyPressEventFU(QKeyEvent *event)
{
    int key = event->key();

    double d = 2;
    double dd = 5;
    
    // https://doc.qt.io/qt-5/qt.html#Key-enum
    if(key == Qt::Key_Up)
    {
        cam.moveForward(d);
    }
    else if(key == Qt::Key_Down)
    {
        cam.moveBack(d);
    }
    else if(key == Qt::Key_U)
    {
        cam.move(d, 0.0, 0.0);
    }
    else if(key == Qt::Key_J)
    {
        cam.move(-d, 0.0, 0.0);
    }
    else if(key == Qt::Key_Left)
    {
        cam.moveLeft(d);
    }
    else if(key == Qt::Key_Right)
    {
        cam.moveRight(d);
    }
    else if(key == Qt::Key_H)
    {
        cam.move(0.0, d, 0.0);
    }
    else if(key == Qt::Key_K)
    {
        cam.move(0.0, -d, 0.0);
    }
    else if(key == Qt::Key_Space)
    {
        cam.move(0.0, 0.0, d);
    }
    else if(key == Qt::Key_C)
    {
        cam.move(0.0, 0.0, -d);
    }
    else if(key == Qt::Key_Y)
    {
        cam.moveUp(d);
    }
    else if(key == Qt::Key_I)
    {
        cam.moveDown(d);
    }
    else if(key == Qt::Key_W)
    {
        cam.rotateOX(-dd);
    }
    else if(key == Qt::Key_S)
    {
        cam.rotateOX(dd);
    }
    else if(key == Qt::Key_A)
    {
        cam.rotateOZ(dd);
    }
    else if(key == Qt::Key_D)
    {
        cam.rotateOZ(-dd);
    }
    else if(key == Qt::Key_Q)
    {
        cam.rotateOY(-dd);
    }
    else if(key == Qt::Key_E)
    {
        cam.rotateOY(dd);
    }
    else if(key == Qt::Key_T)
    {
        angleX += dd;
        M_rotate_refresh();
    }
    else if(key == Qt::Key_R)
    {
        angleX -= dd;
        M_rotate_refresh();
    }
    else if(key == Qt::Key_F)
    {
        angleY += dd;
        M_rotate_refresh();
    }
    else if(key == Qt::Key_G)
    {
        angleY -= dd;
        M_rotate_refresh();
    }

    refresh_C_();
    update(); // event calling???
}

// drawing point on the working place

void DrawField::putPoint(double x, double y, double z)
{
    sPoint cam_o = cam.o();
    double obj_x = x - cam_o.x(); 
    double obj_y = y - cam_o.y(); 
    double obj_z = z - cam_o.z(); 

    //std::cout << C_.multiply(C).toString() << std::endl;

    Matrix<double> old_v(3, 1);
    old_v.set(obj_x, 0, 0); old_v.set(obj_y, 1, 0); old_v.set(obj_z, 2, 0);

    Matrix<double> new_v = C_->multiply(old_v);

    /*
    Конечно, намного лучше найти в новом базисе начало и конец прямой.
    Потом в этом базисе и рисовать. Но хотелось именно в общем виде реализовать
    Поэтому, если есть желание, то для оптимизации лучше переделать отрисовку прямых.
    */
    double x_ = new_v.get(0, 0);
    double y_ = new_v.get(1, 0);
    double z_ = new_v.get(2, 0);

    // В координой системе камеры есть координаты точки
    // (x_, y_, z_)
    // Теперь "Проекция перспективы"
    // pizza time https://www.youtube.com/watch?v=lpvT-Fciu-4

    // ==========================================
    
    double xp,/* yp,*/ zp;

    xp = ((n*x_)/y_);
    zp = ((n*z_)/y_);

    // comparison coordinates for screen drawing

    if(xp < -r || xp > r)
    {
        return;
    }
    if(zp < -t || zp > t)
    {
        return;
    }
    if(y_ > f || y_ < n)
    {
        return;
    }

    // result counting
    
    double x_res, y_res;
    x_res = ((xp+r)*(W-1))/(r+r);
    y_res = ((zp+t)*(H-1))/(t+t);

    // ==========================================

    size_t display_x = (size_t)(x_res+0.5);
    size_t display_y = (size_t)(y_res+0.5);
    display[H-1-display_y][display_x] = 1;

    return;
}

// putting line in working place (3d line, but schreen is 2d), for points

void DrawField::putLine3D(const sPoint& b, const sPoint& e)
{
    putLine3D(b.x(), b.y(), b.z(), e.x(), e.y(), e.z());
}

// putting line in working place (3d line, but schreen is 2d), for coordinates

void DrawField::putLine3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double x, y, z;
    for(double _t = 0.0; _t <= 1.0; _t += 0.001)
    {
        x = (1-_t)*x1 + _t*x2;
        y = (1-_t)*y1 + _t*y2;
        z = (1-_t)*z1 + _t*z2;
        putPoint(x,y,z);
    }
}

// updating working place (matrix)

void DrawField::refresh_C_()
{
    sPoint vx(cam.vr());
    sPoint vy(cam.vf());
    sPoint vz(cam.vu());

    Matrix<double> C(3, 3);
    C.set(vx.x(), 0, 0); C.set(vy.x(), 0, 1); C.set(vz.x(), 0, 2);
    C.set(vx.y(), 1, 0); C.set(vy.y(), 1, 1); C.set(vz.y(), 1, 2);
    C.set(vx.z(), 2, 0); C.set(vy.z(), 2, 1); C.set(vz.z(), 2, 2);
    //std::cout << C.toString() << std::endl;
    Matrix<double> C_buff = C.inverse();
    
    if(C_ != NULL)
    {
        delete C_;
    }
    C_ = new Matrix<double>(C_buff);
}

// updating working place (rotating the image, degree matrix)

void DrawField::M_rotate_refresh()
{
    Matrix<double> Rx(3, 3), Ry(3, 3);

    Rx.set(1, 0, 0); Rx.set(0, 0, 1);                    Rx.set(0, 0, 2); 
    Rx.set(0, 1, 0); Rx.set(cos(deg2rad(angleX)), 1, 1); Rx.set(-sin(deg2rad(angleX)), 1, 2); 
    Rx.set(0, 2, 0); Rx.set(sin(deg2rad(angleX)), 2, 1); Rx.set(cos(deg2rad(angleX)), 2, 2); 

    Ry.set(cos(deg2rad(angleY)), 0, 0);  Ry.set(0, 0, 1); Ry.set(sin(deg2rad(angleY)), 0, 2); 
    Ry.set(0, 1, 0);                     Ry.set(1, 1, 1); Ry.set(0, 1, 2); 
    Ry.set(-sin(deg2rad(angleY)), 2, 0); Ry.set(0, 2, 1); Ry.set(cos(deg2rad(angleY)), 2, 2);

    Matrix<double> buff(Ry.multiply(Rx));

    M_rotate.set(buff.get(0, 0), 0, 0); M_rotate.set(buff.get(0, 1), 0, 1); M_rotate.set(buff.get(0, 2), 0, 2);
    M_rotate.set(buff.get(1, 0), 1, 0); M_rotate.set(buff.get(1, 1), 1, 1); M_rotate.set(buff.get(1, 2), 1, 2);
    M_rotate.set(buff.get(2, 0), 2, 0); M_rotate.set(buff.get(2, 1), 2, 1); M_rotate.set(buff.get(2, 2), 2, 2);
}

// updating working place

void DrawField::refresh_display()
{
    for(size_t li = 0; li < H; ++li)
    {
        for(size_t lj = 0; lj < W; ++lj)
        {
            display[li][lj] = 0;
        }
    }
}

// bilinear surface drawing function 1 (drawing the surface)

void DrawField::drawBilinearSurface()
{
    double u, w;

    for(w = 0; w <= 1.0; w+=0.1)
        for(u = 0; u <= 1.0; u += 0.001)
        {
            sPoint buffP = calBilinearSurface(u, w);
            putPoint(buffP.x(), buffP.y(), buffP.z());
        }
    
    for(u = 0; u <= 1.0; u += 0.1)
        for(w = 0; w <= 1.0; w += 0.001)
        {
            sPoint buffP = calBilinearSurface(u, w);
            putPoint(buffP.x(), buffP.y(), buffP.z());
        }
}

// bilinear surface drawing function 2 (counting the surface)

sPoint DrawField::calBilinearSurface(double u, double w)
{
    //https://scask.ru/a_book_mm3d.php?id=105
    Matrix<double> vold1(3, 1);
    Matrix<double> vold2(3, 1);
    Matrix<double> vold3(3, 1);
    Matrix<double> vold4(3, 1);

    vold1.set(p1.x(), 0, 0); vold2.set(p2.x(), 0, 0); vold3.set(p3.x(), 0, 0); vold4.set(p4.x(), 0, 0);
    vold1.set(p1.y(), 1, 0); vold2.set(p2.y(), 1, 0); vold3.set(p3.y(), 1, 0); vold4.set(p4.y(), 1, 0);
    vold1.set(p1.z(), 2, 0); vold2.set(p2.z(), 2, 0); vold3.set(p3.z(), 2, 0); vold4.set(p4.z(), 2, 0);

    Matrix<double> vnew1(M_rotate.multiply(vold1));
    Matrix<double> vnew2(M_rotate.multiply(vold2));
    Matrix<double> vnew3(M_rotate.multiply(vold3));
    Matrix<double> vnew4(M_rotate.multiply(vold4));

    sPoint _p1(vnew1.get(0, 0), vnew1.get(1, 0), vnew1.get(2, 0));
    sPoint _p2(vnew2.get(0, 0), vnew2.get(1, 0), vnew2.get(2, 0));
    sPoint _p3(vnew3.get(0, 0), vnew3.get(1, 0), vnew3.get(2, 0));
    sPoint _p4(vnew4.get(0, 0), vnew4.get(1, 0), vnew4.get(2, 0));

    double x_res = _p1.x()*(1-u)*(1-w)
                +  _p2.x()*(1-u)*w
                +  _p3.x()*u*(1-w)
                +  _p4.x()*u*w;
    double y_res = _p1.y()*(1-u)*(1-w)
                +  _p2.y()*(1-u)*w
                +  _p3.y()*u*(1-w)
                +  _p4.y()*u*w;
    double z_res = _p1.z()*(1-u)*(1-w)
                +  _p2.z()*(1-u)*w
                +  _p3.z()*u*(1-w)
                +  _p4.z()*u*w;

    return sPoint(x_res, y_res, z_res);
}
