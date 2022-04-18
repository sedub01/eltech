// point class

#ifndef SPOINT_H
#define SPOINT_H

#include <string>

class sPoint
{
    private:
    /*const */double _x;
    /*const */double _y;
    /*const */double _z;

    public:

    sPoint();
    sPoint(double x, double y, double z);
    sPoint(const sPoint& toCopied);

    double getX() const;

    double getY() const;

    double getZ() const;
    
    void setX(double new_x);

    void setY(double new_y);

    void setZ(double new_z);

    double x() const;

    double y() const;

    double z() const;

    void add(const sPoint& other);

    void sub(const sPoint& other);

    void mul(double x);

    std::string print(std::string prefix) const;

    double vector_len() const;
};

#endif // SPOINT_H
