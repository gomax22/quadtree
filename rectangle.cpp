#include "rectangle.h"

Rectangle::Rectangle() {
    center = new Point();
    this->w = 0;
    this->h = 0;
}

/*
Il costruttore con parametro prende in input le coordinate del centro del rettangolo/quadrato, 
la larghezza, l'altezza e le assegna al quadrante.
*/ 
Rectangle::Rectangle(float x, float y, float w, float h)  {
    center = new Point(x,y);
    this->w = w;
    this->h = h;
}

//La funzione contains() prende in input il puntatore ad un punto e restituisce un valore booleano,
//TRUE se il punto è contenuto nel quadrante, altrimenti FALSE.
bool Rectangle::contains(Point* point) {
    return (point->getX() >= this->center->getX() - this->w && 
            point->getX() <= this->center->getX() + this->w &&
            point->getY() >= this->center->getY() - this->h &&
            point->getY() <= this->center->getY() + this->h);
}

//La funzione getCenter() restituisce il centro del quadrante
Point* Rectangle::getCenter() {
    return this->center;
}


//La funzione getW() restituisce la larghezza del quadrante
float Rectangle::getW() {
    return this->w;
}

//La funzione getH() restituisce l'altezza del quadrante
float Rectangle::getH() {
    return this->h;
}
