#include "quadtree.h"
#include <iostream>
using namespace std;

QuadTree::QuadTree() {
    this->root = nullptr;
    counterID = 0;
}

QuadTree::QuadTree(Rectangle* boundary, int capacity) {
    counterID = 0;
    root = new QuadTreeNode(boundary, capacity, nullptr, counterID++);
}

/*
Il metodo NEIGHBOR() prende in input le coordinate di un punto e una direzione e restituisce il puntatore al nodo adiacente nella direzione richiesta.
Se esiste il nodo adiacente in quella direzione, che abbia al più la stessa profondità nell'albero, restituisce il puntatore di quel nodo altrimenti
restituisce un puntatore nullo.
*/
QuadTreeNode *QuadTree::NEIGHBOR(Point *point, unsigned int direction) {
    QuadTreeNode *result = nullptr;
    if (!search(point, root, result)) {
        cout << "ID non trovato" << endl;
        return result;
    }

    cout << "ID_NODO: " << result->getID();
    switch (direction)  {
        case 1:
            return N_NEIGHBOR(result);
            break;
        case 2:
            return S_NEIGHBOR(result);
            break;
        case 3:
            return W_NEIGHBOR(result);
            break;
        case 4:
            return E_NEIGHBOR(result);
            break;
        default:
            cout << "invalid input" << endl;
            return nullptr;
            break;
    }
}


//La procedura insertFromTextFile() stampa a video se l'apertura e la lettura del file di testo è avvenuta con successo o meno.
void QuadTree::insertFromTextFile(string inputString) {
    if (readText(inputString)) cout << "\nInsert from TextFile: success!" << endl;
    else cout << "\nInsert from TextFile: failed!" << endl;
}

/*
La funzione readText() prende in input una stringa corrispondente al nome del file di testo e restituisce un valore booleano, 
TRUE se la lettura è avvenuta con successo, altrimenti FALSE.
Inoltre, controlla se il contenuto del file di testo rispetta i vincoli imposti dal quesito.
*/
bool QuadTree::readText(string inputString) {
    if (!checkInput(inputString)) return false;

    float x, y;
    char comma;

    while(file >> x >> comma >> y) {
        insert(new Point(x,y));
    }
    return true;
}

/*
La funzione checkInput() prende in input una stringa corrispondente al nome del file di testo e restituisce un valore booleano, 
TRUE se l'apertura è avvenuta con successo, altrimenti FALSE.
*/
bool QuadTree::checkInput(string inputString) {
    file.open(inputString.c_str());

    if(!file.fail()){
        cout << "FILE: " << inputString << "\nStatus: Successfully opened!\n" << endl;
        return true;
    } else cout << "Error: cannot open input file!" << endl;
    return false;
} 


//La procedura insert() prende in input un puntatore ad un punto e stampa a video se questo è stato inserito con successo o meno 
void QuadTree::insert(Point* point) {
    QuadTreeNode *splittedNode = nullptr;
    if(Wrapper_insert(point, this->root, splittedNode))
        cout << "Insert for (" << point->getX() << "," << point->getY() << "): success!" << endl;
    else
        cout << "Insert for (" << point->getX() << "," << point->getY() << "): failed!" << endl;

    if (splittedNode) {
        while (!splittedNode->getPoints()->empty()) {
            Point *point = splittedNode->getPoints()->back();
            splittedNode->getPoints()->pop_back();
            if (!FixUp_insert(point, this->root))
                return;
        }
    }
} 

/*
Il metodo Wrapper_insert() è una funzione ausiliaria ricorsiva per l'inserimento del punto nella struttura QuadTree.
Questa funzione prende in input due puntatori, uno ad un punto e l'altro ad un nodo, e una refererence ad un puntatore a nodo e
restituisce un valore booleano, TRUE se il punto è stato inserito, altrimenti FALSE.
Al suo interno, verifica se il punto è contenuto nel quadrante corrispondente al nodo passato in input e successivamente, 
se questo non supera la capacità del quadrante stesso.

Se il punto non è contenuto nel quadrante, restituisce FALSE.
Se il punto non può essere contenuto poichè supererebbe la capacità del quadrante corrispondente al nodo, allora il medesimo nodo viene
suddiviso e il metodo viene richiamato ricorsivamente per i sottoquadranti appena creati.
Inoltre, ricorda se e quale nodo viene suddiviso, in maniera tale da richiamare all'esterno la funzione FixUp_insert().
*/
bool QuadTree::Wrapper_insert(Point* point, QuadTreeNode *node, QuadTreeNode* &splittedNode) {
    if(!(node->getBoundary()->contains(point)))
        return false;
        
    if(node->getPoints()->size() < node->getCapacity() && (!node->getDivided())) {
        node->getPoints()->push_back(point);
        return true;
    }
    
    if(!node->getDivided()) {
        this->subdivide(node);
        splittedNode = node;
    }
        
    if(Wrapper_insert(point, node->getNE(), splittedNode))
        return true;
    if(Wrapper_insert(point, node->getNW(), splittedNode))
        return true;
    if(Wrapper_insert(point, node->getSE(), splittedNode))
        return true;
    if(Wrapper_insert(point, node->getSW(), splittedNode))
        return true;
    return false;
}

/*
La funzione FixUp_insert() si occupa di "spostare" i punti che erano assegnati ad un quadrante unico prima di essere suddiviso,
si comporta alla stessa maniera della funzione Wrapper_insert().
*/
bool QuadTree::FixUp_insert(Point* point, QuadTreeNode *node) {
    if(!(node->getBoundary()->contains(point)))
        return false;
        
    if(node->getPoints()->size() < node->getCapacity() && (!node->getDivided())) {
        node->getPoints()->push_back(point);
        return true;
    }
    
    if(!node->getDivided())
        this->subdivide(node);
        
    if(FixUp_insert(point, node->getNE()))
        return true;
    if(FixUp_insert(point, node->getNW()))
        return true;
    if(FixUp_insert(point, node->getSE()))
        return true;
    if(FixUp_insert(point, node->getSW()))
        return true;
    return false;
}
/*
La procedura subdivide() prende in input il puntatore ad un nodo del quadrante, cui è necessario suddividere, 
e restiuisce il nodo diviso in sottoquadranti.
*/
void QuadTree::subdivide(QuadTreeNode *node) {
    float x = node->getBoundary()->getCenter()->getX();
    float y = node->getBoundary()->getCenter()->getY();
    float w = node->getBoundary()->getW();
    float h = node->getBoundary()->getH();

    Rectangle *ne = new Rectangle(x + w/2, y + h/2, w/2, h/2);
    node->setNE(new QuadTreeNode(ne, node->getCapacity(), node, counterID++));
        
    Rectangle *nw = new Rectangle(x - w/2, y + h/2, w/2, h/2);
    node->setNW(new QuadTreeNode(nw, node->getCapacity(), node, counterID++));
    
    Rectangle *sw = new Rectangle(x - w/2, y - h/2, w/2, h/2);
    node->setSW(new QuadTreeNode(sw, node->getCapacity(), node, counterID++));

    Rectangle *se = new Rectangle(x + w/2, y - h/2, w/2, h/2);
    node->setSE(new QuadTreeNode(se, node->getCapacity(), node, counterID++));
    
    node->setDivided(true); 
}

/*
Il metodo N_NEIGHBOR() prende in input un puntatore ad un nodo e restituisce il nodo adiacente nella direzione NORTH.
Se questo esiste, restituisce il suo puntatore altrimenti un puntatore nullo.
*/
QuadTreeNode *QuadTree::N_NEIGHBOR(QuadTreeNode *node) {
    if(node == this->root) return nullptr;
    if(node == node->getParent()->getSW()) return node->getParent()->getNW();
    if(node == node->getParent()->getSE()) return node->getParent()->getNE();

    QuadTreeNode *u = N_NEIGHBOR(node->getParent());
    if(u == nullptr || !u->getDivided())
        return u;
    else if(node == node->getParent()->getNW())
        return (u->getSW());
    else
        return (u->getSE());
}

/*
Il metodo S_NEIGHBOR() prende in input un puntatore ad un nodo e restituisce il nodo adiacente nella direzione SOUTH.
Se questo esiste, restituisce il suo puntatore altrimenti un puntatore nullo.
*/
QuadTreeNode *QuadTree::S_NEIGHBOR(QuadTreeNode *node) {
    if(node == this->root) return nullptr;
    if(node == node->getParent()->getNW()) return node->getParent()->getSW();
    if(node == node->getParent()->getNE()) return node->getParent()->getSE();

    QuadTreeNode *u = S_NEIGHBOR(node->getParent());
    if(u == nullptr || !u->getDivided())
        return u;
    else if(node == node->getParent()->getSW())
        return (u->getNW());
    else
        return (u->getNE());
}

/*
Il metodo W_NEIGHBOR() prende in input un puntatore ad un nodo e restituisce il nodo adiacente nella direzione WEST.
Se questo esiste, restituisce il suo puntatore altrimenti un puntatore nullo.
*/
QuadTreeNode *QuadTree::W_NEIGHBOR(QuadTreeNode *node) {
    if(node == this->root) return nullptr;
    if(node == node->getParent()->getNE()) return node->getParent()->getNW();
    if(node == node->getParent()->getSE()) return node->getParent()->getSW();

    QuadTreeNode *u = W_NEIGHBOR(node->getParent());
    if(u == nullptr || !u->getDivided())
        return u;
    else if(node == node->getParent()->getSW())
        return (u->getSE());
    else
        return (u->getNE());
}

/*
Il metodo E_NEIGHBOR() prende in input un puntatore ad un nodo e restituisce il nodo adiacente nella direzione EAST.
Se questo esiste, restituisce il suo puntatore altrimenti un puntatore nullo.
*/
QuadTreeNode *QuadTree::E_NEIGHBOR(QuadTreeNode *node) {
    if(node == this->root) return nullptr;
    if(node == node->getParent()->getNW()) return node->getParent()->getNE();
    if(node == node->getParent()->getSW()) return node->getParent()->getSE();

    QuadTreeNode *u = E_NEIGHBOR(node->getParent());
    if(u == nullptr || !u->getDivided())
        return u;
    else if(node == node->getParent()->getSE())
        return (u->getSW());
    else
        return (u->getNW());
}

/*
La funzione search() consente, attraverso il passaggio delle coordinate di un punto, di cercare un nodo all'interno del QuadTree.
Prende in input le coordinate del punto appartenente al quadrato del nodo che stiamo cercando, un puntatore a nodo e una reference di un puntatore a nodo e restituisce un valore booleano,
TRUE se il nodo è stato trovato, altrimenti FALSE.
In caso di esito affermativo, il puntatore a nodo viene assegnato alla variabile reference passata come parametro.
*/
bool QuadTree::search(Point *point, QuadTreeNode *node, QuadTreeNode* &result) {
    if(!(node->getBoundary()->contains(point)))
        return false;
        
    if((!node->getDivided())) {
        result = node;
        return true;
    }
        
    if(search(point, node->getNE(), result))
        return true;
    if(search(point, node->getNW(), result))
        return true;
    if(search(point, node->getSE(), result))
        return true;
    if(search(point, node->getSW(), result))
        return true;
    return false;
}

