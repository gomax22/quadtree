#ifndef POINT_H
#define POINT_H

class Point {
private:
    float x;
    float y;
public:
    Point()  {}
    Point(float x, float y);
    ~Point() {}
    float getX();
    float getY();
};

#endif /* POINT_H */