#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "point.cpp"

class Rectangle {
private:
    Point *center;
    float w;
    float h;
public:
    Rectangle();
    Rectangle(float x, float y, float w, float h);
    ~Rectangle() {}
    bool contains(Point* point);
    Point *getCenter();
    float getW();
    float getH();
};


#endif /* RECTANGLE_H */