#include "point.h"
using namespace std;

//Il costruttore con parametro prende in input le coordinate x ed y e le assegna ad un punto
Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
}

//La funzione getX() restituisce la coordinata x del punto
float Point::getX() {
    return this->x;
}

//La funzione getY restitituisce la coordinata y del punto
float Point::getY() {
    return this->y;
}