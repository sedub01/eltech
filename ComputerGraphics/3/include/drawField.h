// draw field class

#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>
#include <QMouseEvent>

#include <cmath>

#include "../include/sPoint.h"
#include "../include/sCamera.h"
#include "../include/matrix.h"

class DrawField : public QWidget
{

  //Q_OBJECT

  private:
    const size_t W = 1280;
    const size_t H = 720;
    const double aspect = (double)W / (double)H;

    const double n = 1;
    const double f = 10000;
    const double fov = 65;
    const double t = n * tan(fov/2); // top
    const double r = t*aspect;      //right

    Matrix<double> *C_;

    int **display;

    sCamera cam;

    void refresh_C_();
    void refresh_display();

    sPoint p1, p2, p3, p4;
    Matrix<double> M_rotate;
    void M_rotate_refresh();
    double angleX;
    double angleY;
    void drawBilinearSurface();
    sPoint calBilinearSurface(double u, double w);

  public:
    DrawField(QWidget *parent,
      double x1, double y1, double z1, 
      double x2, double y2, double z2, 
      double x3, double y3, double z3,
      double x4, double y4, double z4
    );
    ~DrawField();

    void keyPressEventFU(QKeyEvent *event);
    
    void putPoint(double x, double y, double z);
    void putLine3D(double x1, double y1, double z1, double x2, double y2, double z2);
    void putLine3D(const sPoint& b, const sPoint& e);

    void putParallelepiped(const sPoint p1, const sPoint p2);
    void putSphere(const sPoint c, double r);
 
  private:
    void paintEvent(QPaintEvent *event);

    //void drawPoint(const sPoint& p, QPainter& qp, QColor *colo = 0);


  protected:
    //void keyPressEvent(QKeyEvent *event);
};

#endif // DRAWFIELD_H