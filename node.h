#ifndef NODE_H
#define NODE_H

#include "rectangle.h"
#include <vector>
using namespace std;

class QuadTreeNode {
private:
    bool divided;
    unsigned int capacity;
    unsigned int id;
    vector<Point*>* points;
    Rectangle* boundary;
    QuadTreeNode *NE, *NW, *SW, *SE;
    QuadTreeNode *parent;
public:
    QuadTreeNode();
    QuadTreeNode(Rectangle* boundary, unsigned int capacity, QuadTreeNode *parent, unsigned int id);
    ~QuadTreeNode() {}
    void setNE(QuadTreeNode *node);
    void setNW(QuadTreeNode *node);
    void setSE(QuadTreeNode *node);
    void setSW(QuadTreeNode *node);
    void setDivided(bool divided);
    void setID(unsigned int id);
    bool getDivided();
    unsigned int getCapacity();
    unsigned int getID();
    vector<Point*> *getPoints();
    Rectangle *getBoundary();
    QuadTreeNode *getNE();
    QuadTreeNode *getNW();
    QuadTreeNode *getSE();
    QuadTreeNode *getSW();
    QuadTreeNode *getParent();
};

#endif /* NODE_H */