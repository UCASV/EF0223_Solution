#include <iostream>

enum Color {BLACK, RED};

typedef struct Nodo{
    int dato;
    Color col;
    struct Nodo* parent;
    struct Nodo* izq;
    struct Nodo* der;
} Nodo;

enum Side {LEFT,RIGHT};

using namespace std;

Nodo* crear(){
    return NULL;
}

bool estaVacio(Nodo* T){
    return (T == NULL)?true:false;
}

Nodo* crearNodo(int n){
    Nodo* nuevo;
    nuevo = (Nodo*) malloc(sizeof(Nodo));
    nuevo->dato = n;
    nuevo->col = RED;
    nuevo->parent = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;
   
    return nuevo;
}

bool esta(Nodo* T, int n){
    if(estaVacio(T)) return false;
    if(T->dato == n) return true;
    if(n <= T->dato) return esta(T->izq, n);
    else return esta(T->der, n);
}

int inOrderSuccessor(Nodo* T){
    if(T->izq == NULL) return T->dato;
    return inOrderSuccessor(T->izq);
}

void destruirArbol(Nodo* T){
    if(estaVacio(T)) return;
    destruirArbol(T->izq);
    destruirArbol(T->der);
    free(T);
}

///////////////////////////////ROTATIONS//////////////////////////////

void rotarLEFT(Nodo *&A, Nodo *&B){
    Nodo* Adad = A->parent;
    Nodo* Bizq = B->izq;
   
    if(Bizq != NULL) Bizq->parent = A;
    B->izq = A;
    A->der = Bizq;
    A->parent = B;
    B->parent = Adad;
    if(Adad != NULL)
        if(Adad->izq == A)
            Adad->izq = B;
        else
            Adad->der = B;
}

void rotarRIGHT(Nodo *&A, Nodo *&B){
    Nodo* Adad = A->parent;
    Nodo* Bder = B->der;
   
    if(Bder != NULL) Bder->parent = A;
    B->der = A;
    A->izq = Bder;
    A->parent = B;
    B->parent = Adad;
    if(Adad != NULL)
        if(Adad->izq == A)
            Adad->izq = B;
        else
            Adad->der = B;
}

Nodo* getRoot(Nodo* n){
    if(n->parent == NULL) return n;
    else return getRoot(n->parent);
}

void fixRoot(Nodo *&T, Nodo *&recent){
    Nodo* root_actual = getRoot(recent);
    if(T != root_actual) T = root_actual;
}

void fixDoubleRed(Nodo *&T, Nodo *&recent){
    Side s1,s2;
    Nodo* daddy;
    Nodo* grandpa;
    Nodo* uncle;
    while(true){
        grandpa = NULL;
        uncle = NULL;
        daddy = recent->parent;
        if(daddy != NULL) grandpa = daddy->parent;
        if(daddy != NULL && grandpa != NULL && daddy->col != BLACK){
            if(daddy == grandpa->izq){
                s1 = LEFT;
                uncle = grandpa->der;
            }else{
                s1 = RIGHT;
                uncle = grandpa->izq;
            }
            if(recent == daddy->izq) s2 = LEFT;
            else s2 = RIGHT;
            if(uncle == NULL || uncle->col == BLACK){
                if(s1 == LEFT && s2 == LEFT){
                    rotarRIGHT(grandpa,daddy);
                    daddy->col = BLACK;
                    grandpa->col = RED;
                }
                if(s1 == LEFT && s2 == RIGHT){
                    rotarLEFT(daddy,recent);
                    rotarRIGHT(grandpa,recent);
                    recent->col = BLACK;
                    grandpa->col = RED;
                }
                if(s1 == RIGHT && s2 == LEFT){
                    rotarRIGHT(daddy,recent);
                    rotarLEFT(grandpa,recent);
                    recent->col = BLACK;
                    grandpa->col = RED;
                }
                if(s1 == RIGHT && s2 == RIGHT){
                    rotarLEFT(grandpa,daddy);
                    daddy->col = BLACK;
                    grandpa->col = RED;
                }
                break;
            }else{
                daddy->col = BLACK;
                uncle->col = BLACK;
                grandpa->col = RED;
                recent = grandpa;
                continue;
            }
        }else break;
    }
    fixRoot(T,recent);
    T->col = BLACK;
}

Nodo* insertarAux(Nodo *&T, int n){
    Nodo* recent = NULL;
   
    if(n <= T->dato){
        if(T->izq == NULL){
            recent = crearNodo(n);
            recent->parent = T;
            T->izq = recent;
        }else recent = insertarAux(T->izq, n);
    }else{
        if(T->der == NULL){
            recent = crearNodo(n);
            recent->parent = T;
            T->der = recent;
        }else recent = insertarAux(T->der, n);
    }
   
    return recent;
}

void insertar(Nodo *&T, int n){
    if(estaVacio(T)){
        T = crearNodo(n);
        T->col = BLACK;
    }else{
        Nodo* nuevo = insertarAux(T, n);
        if(nuevo->parent->col != BLACK) fixDoubleRed(T,nuevo);
    }
}

int countRedOnes(Nodo *&T){
    if(T == NULL) return 0;
    return ((T->col == RED)?1:0) + countRedOnes(T->izq) + countRedOnes(T->der);
}

int main(){
    int ntc, n, d;
    Nodo* T;
   
    cin >> ntc;

    for(int i = 0; i < ntc; ++i){
        T = crear();
        cin >> n;
        for(int j = 0; j < n; ++j){
            cin >> d;
            insertar(T, d);
        }
        cout << countRedOnes(T) << "\n";
        destruirArbol(T);
    }

    return 0;
}
