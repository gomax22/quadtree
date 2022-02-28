#include <iostream>
#include <string>
#include "quadtree.h"
#include "quadtree.cpp"

using namespace std;

int main() {
    QuadTree *qtree = new QuadTree(new Rectangle(64, 64, 64, 64), 2);
    QuadTreeNode *neighbor = nullptr;
    unsigned int direction, choice, node_id;
    float x, y;
    string inputString;
    cout << "-----------------QUADTREE----------------" << endl;
    
    do {
        cout << "1. Inserisci i punti dal file di testo\n";
        cout << "2. NEIGHBOR()\n";
        cout << "3. Esci\n";
        cin >> choice; fflush(stdin);

        system("cls");
        switch (choice) {
            case 1:

                cout << "Inserisci il nome del file di testo: " << endl;
                getline(cin, inputString);

                cout << "\nInserimento dei punti nel file di testo\n" << endl;
                qtree->insertFromTextFile(inputString);

                system("pause"); system("cls");
                break;
            case 2:

                cout << "Inserisci le coordinate del punto (una dopo l'altra) che identificano il nodo di cui vuoi conoscere il NEIGHBOR():" << endl;
                cin >> x >> y; fflush(stdin);
                cout << "\nSeleziona una direzione:\n1. N\n2. S\n3. W\n4. E" << endl;
                cin >> direction; fflush(stdin);

                neighbor = qtree->NEIGHBOR(new Point(x,y), direction);

                if (neighbor)
                    cout << "\tID_NEIGHBOR: " << neighbor->getID() << endl; 
                else cout << "\tNEIGHBOR NON TROVATO" << endl;

                system("pause"); system("cls");
                break;
            case 3:

                cout << "Uscita in corso..." << endl;
                break;
            default:

                cout << "Errore: scelta non valida!" << endl;
                cout << "Inserisci un'opzione valida! (0 <= choice <= 3)" << endl;
                system("pause"); system("cls");
                break;
        }
    }while (choice != 3);
    system("pause");
    return 0;
}