#include <iostream>
using namespace std;

enum order {IN,PRE,POST};
enum position {NONE,LEFT,RIGHT};

typedef struct node {
    struct node* parent;
    int data;
    short balance;
    struct node* left;
    struct node* right;
} tree;

tree* root = NULL;

/*###################### Funciones de administración del árbol ######################*/
bool is_empty_tree(tree* T){
    return T == NULL;
}

tree* create_node(int value){
    tree* n = (tree*) malloc( sizeof(tree) );
    n->data = value;
    n->balance = 0;
    n->parent = n->left = n->right = NULL;

    return n;
}

position check_position(tree* node){
    if(node->parent == NULL) return NONE;
    if(node->parent->left == node) return LEFT;
    else return RIGHT;
}

/*###################### Funciones de Rotación de Nodos ######################*/
void L_rotation(tree* A, tree* B){
	tree* temp = B->left;

    A->right = temp;
    if(temp != NULL) temp->parent = A;
    
    B->left = A;
    A->parent = B;
}

tree* RR_rotation(tree* p, tree* n){
	L_rotation(p, n);

    if(n->balance == 0){
        n->balance = -1;
        n->left->balance = 1;
    }else{
        n->balance = 0;
        n->left->balance = 0;
    }

    return n;
}

void R_rotation(tree* B, tree* A){
	tree* temp = A->right;

    B->left = temp;
    if(temp != NULL) temp->parent = B;

    A->right = B;
    B->parent = A;
}

tree* LL_rotation(tree* parent, tree* T){
	R_rotation(parent, T);

    if(T->balance == 0){
        T->balance = 1;
        T->right->balance = -1;
    }else{
        T->balance = 0;
        T->right->balance = 0;
    }

    return T;
}

tree* RL_rotation(tree* p, tree* n){
    tree* Y = n->left;
    
    R_rotation(n, Y);

    L_rotation(p, Y);
    
    switch(Y->balance){
        case -1:
            Y->left->balance = 0;
            Y->right->balance = 1;
            break;

        case 0:
            Y->left->balance = 0;
            Y->right->balance = 0;
            break;

        case 1:
            Y->left->balance = -1;
            Y->right->balance = 0;
            break;
    }

    Y->balance = 0;

    return Y;
}

tree* LR_rotation(tree* p, tree* n){
    tree* Y = n->right;

    L_rotation(n, Y);

    R_rotation(p, Y);

    switch(Y->balance){
        case -1:
            Y->left->balance = 0;
            Y->right->balance = 1;
            break;

        case 0:
            Y->left->balance = 0;
            Y->right->balance = 0;
            break;

        case 1:
            Y->left->balance = -1;
            Y->right->balance = 0;
            break;
    }

    Y->balance = 0;

    return Y;
}

/*###################### Funciones para la Inserción de Nodos ######################*/
void insertion_rebalance(tree* n){
    position parent_position;
    tree *p, *g, *anchor;

    while(n->parent != NULL){
        p = n->parent;

        if(check_position(n) == LEFT){ //n es hijo izquierdo de p
            if(p->balance == -1){ //p era Left-Heavy
				g = p->parent;
                parent_position = check_position(p);
				
                if(n->balance == 1) anchor = LR_rotation(p, n);
                else anchor = LL_rotation(p, n);
			}else{
				if(p->balance == 0){ //p era Neutral
                    p->balance = -1;

                    n = p;

					continue;
				}

				p->balance = 0;

				break;
			}
		}else{ //n es hijo derecho de p
			if(p->balance == -1){ //p era Left-Heavy
				p->balance = 0;

				break;
			}else{
				if(p->balance == 0){ //p era Neutral
					p->balance = 1;

                    n = p;

					continue;
				}

                g = p->parent;
                parent_position = check_position(p);
				
                if(n->balance == -1) anchor = RL_rotation(p, n);
                else anchor = RR_rotation(p, n);
			}
		}
		
		anchor->parent = g;
		if(g != NULL)
			if(parent_position == LEFT) g->left = anchor;
			else g->right = anchor;
		else root = anchor;
		
		break;
    }
}

tree* insert_aux(tree* T, int value){
    if(value <= T->data)
        if(T->left == NULL){
            T->left = create_node(value);
            T->left->parent = T;

            return T->left;
        }
        else return insert_aux(T->left, value);
    else
        if(T->right == NULL){
            T->right = create_node(value);
            T->right->parent = T;

            return T->right;
        }
        else return insert_aux(T->right, value);
}

void insert(tree* T, int value){
    if(is_empty_tree(T)) root = create_node(value);
    else{
        tree* n = insert_aux(T, value);

        insertion_rebalance(n);
    }
}

/*###################### Funciones utilitarias para búsqueda en el árbol ######################*/
bool find(tree* T, int value){
    if(T == NULL) return false;

    if(value == T->data) return true;

    if(value < T->data) return find(T->left, value);
    else return find(T->right, value);
}

tree* extract_node(tree* T, int value){
    if(value == T->data) return T;

    if(value < T->data) return extract_node(T->left, value);
    else return extract_node(T->right, value);
}

/*###########################################################*/
void destroy(tree* T){
    if(T == NULL) return;

    destroy(T->left);

    destroy(T->right);

    free(T);
}

int MDD(tree* T){
    if(T->right == NULL) return T->data;
    return MDD(T->right);
}

int main(void){
    int n, d;
    while (cin >> n){
        root = NULL;
        for(int i = 0; i < n; ++i){
            cin >> d;
            insert(root,d);
        }
        cout << "This person died with a MDD of: " << MDD(root->left) << "\n";
        destroy(root);
    }
    return 0;
}
