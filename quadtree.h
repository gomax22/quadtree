#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include "node.h"
#include "node.cpp"
#include <vector>
#include <iterator>
#include <fstream>
#include "rectangle.h"
#include "rectangle.cpp"
using namespace std;

class QuadTree {
private:
    unsigned int counterID;
    QuadTreeNode *root;
    ifstream file;

    void subdivide(QuadTreeNode *node);
    void insert(Point* point);
    bool checkInput(string inputString);
    bool readText(string inputString);
    bool Wrapper_insert(Point* point, QuadTreeNode *node, QuadTreeNode* &splittedNode);
    bool FixUp_insert(Point* point, QuadTreeNode *node);
    QuadTreeNode *N_NEIGHBOR(QuadTreeNode *node);
    QuadTreeNode *S_NEIGHBOR(QuadTreeNode *node);
    QuadTreeNode *W_NEIGHBOR(QuadTreeNode *node);
    QuadTreeNode *E_NEIGHBOR(QuadTreeNode *node);
public:
    QuadTree();
    QuadTree(Rectangle* boundary, int capacity);
    ~QuadTree() {} 
    void insertFromTextFile(string inputString);
    bool search(Point* point, QuadTreeNode *node, QuadTreeNode* &result);
    QuadTreeNode *NEIGHBOR(Point *point, unsigned int direction);
};

#endif /* QUADTREE_H */