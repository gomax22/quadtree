#include "node.h"
using namespace std;

QuadTreeNode::QuadTreeNode() {
    this->boundary = new Rectangle();
    this->capacity = 0;
    this->points = new vector<Point*>();
    this->divided = false;
    this->NE = this->NW = this->SW = this->SE = this->parent = nullptr;
}

QuadTreeNode::QuadTreeNode(Rectangle* boundary, unsigned int capacity, QuadTreeNode *parent, unsigned int id) {
    this->boundary = boundary;
    this->capacity = capacity;
    this->points = new vector<Point*>();
    this->divided = false;
    this->parent = parent;
    this->NE = this->NW = this->SW = this->SE = nullptr;
    this->id = id;
}

//La funzione getBoundary() restituisce il quadrante corrispondente al QuadTreeNode
Rectangle *QuadTreeNode::getBoundary() {
    return this->boundary;
}

//La funzione getCapacity() resituisce la capacità del nodo
unsigned int QuadTreeNode::getCapacity() {
    return this->capacity;
}

//La funzione getPoints() restituisce il vettore contenente i punti all'interno del quadrante corrispondente al QuadTreeNode
vector<Point*> *QuadTreeNode::getPoints() {
    return this->points;
}

//La funzione getNE() restituisce il puntatore del figlio a NORTH-EAST del QuadTreeNode
QuadTreeNode *QuadTreeNode::getNE() {
    return this->NE;
}

//La procedura setNE() prende in input un puntatore ad un QuadTreeNode cui deve essere impostato come figlio a NORTH-EAST
void QuadTreeNode::setNE(QuadTreeNode *node) {
    this->NE = node;
}

//La funzione getNW() restituisce il puntatore del figlio a NORTH-WEST del QuadTreeNode
QuadTreeNode *QuadTreeNode::getNW() {
    return this->NW;
}

//La procedura setNW() prende in input un puntatore ad un QuadTreeNode cui deve essere impostato come figlio a NORTH-WEST
void QuadTreeNode::setNW(QuadTreeNode *node) {
    this->NW = node;
}

//La funzione getSE() restituisce il puntatore del figlio a SOUTH-EAST del QuadTreeNode
QuadTreeNode *QuadTreeNode::getSE() {
    return this->SE;
}

//La procedura setSE() prende in input un puntatore ad un QuadTreeNode cui deve essere impostato come figlio a SOUTH-EAST
void QuadTreeNode::setSE(QuadTreeNode *node) {
    this->SE = node;
}

//La funzione getSW() restituisce il puntatore del figlio a SOUTH-WEST del QuadTreeNode
QuadTreeNode *QuadTreeNode::getSW() {
    return this->SW;
}

//La procedura setSW() prende in input un puntatore ad un QuadTreeNode cui deve essere impostato come figlio a SOUTH-WEST
void QuadTreeNode::setSW(QuadTreeNode *node) {
    this->SW = node;
}

//La funzione getParent() restituisce il puntatore al padre del QuadTreeNode
QuadTreeNode *QuadTreeNode::getParent() {
    return this->parent;
}

//La funzione getDivided() restituisce il valore dell'attributo booleano divided del QuadTreeNode
bool QuadTreeNode::getDivided() {
    return this->divided;
}

//La procedura setDivided() prende in input un valore booleano che dovrà assumere l'attributo divided del QuadTreeNode
void QuadTreeNode::setDivided(bool divided) {
    this->divided = divided;
}

void QuadTreeNode::setID(unsigned int id) {
    this->id = id;
}

unsigned int QuadTreeNode::getID() {
    return id;
}

