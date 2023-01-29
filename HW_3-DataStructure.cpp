#include <iostream>
#include <fstream>
#include <vector>
#include<cmath>
using namespace std;
int x, y;
const int MAX_CHILD = 2;

struct Node {
    int index;
    int data;
    int child_count;
    int children[MAX_CHILD];
    int color; // -1(uncolored) , 1(White), 0(Black)
    int bf; // balance factor
    Node* left;
    Node* right;

};

void print_inorder(Node* root)
{
    if (root == NULL)
        return;
   
    print_inorder(root->left);
    
    cout << root->data << endl;
    
    print_inorder(root->right);
}

int closest(double x, vector<Node*>T) {
    int c=T[0]->data;
    for (int i = 1; i < T.size(); i++) {
        if (abs((T[i]->data) - x) < abs(c-x)) c =(T[i]->data);
    }
    return c;
}


void create(string FileName, vector <Node*> &T1, vector <Node*>&T2) {
    int size,data,childcount;
    ifstream f(FileName);
    f >> size;
    Node* temp;
    for (int i = 0; i < size; i++) {
        temp = new Node;
        f >> (temp->index);
        f >> temp->data;
        f >> temp->child_count;
        for (int j = 0; j < temp->child_count; j++) {
            f >> temp->children[j];
        }
        f >> temp->color;
        T1.push_back(temp);
    }

    for (int i = 0; i < size; i++) {

        switch (T1[i]->child_count) {
        case 0:
            
            T1[i]->left = NULL;
            T1[i]->right = NULL;
            break;
        case 1:
            T1[i]->left = NULL;
            T1[i]->right = NULL;
            Node* p;
            p = T1[T1[i]->children[0]];
            if (T1[T1[i]->children[0]]->data > T1[i]->data)  T1[i]->right=p;
            else  T1[i]->left=p;
            break;
        case 2:
            if (T1[T1[i]->children[0]]->data > T1[T1[i]->children[1]]->data) { x = 0; y = 1; }
            else { x = 1; y = 0; }
            T1[i]->left = T1[T1[i]->children[y]];
            T1[i]->right = T1[T1[i]->children[x]];
            break;
        }
    }


    f >> size;
    for (int i = 0; i < size; i++) {
        temp = new Node;
        f >> (temp->index);
        f >> temp->data;
        f >> temp->child_count;
        for (int j = 0; j < temp->child_count; j++) {
            f >> temp->children[j];
        }
        f >> temp->color;
        T2.push_back(temp);
    }
    for (int i = 0; i < size; i++) {

        switch (T2[i]->child_count) {
        case 0:
            T2[i]->left = NULL;
            T2[i]->right = NULL;
            break;
        case 1:
            T2[i]->left = NULL;
            T2[i]->right = NULL;
            Node* p;
            p = T2[T2[i]->children[0]];
            if (T2[T2[i]->children[0]]->data > T2[i]->data)  T2[i]->right = p;
            else  T2[i]->left = p;
            break;
        case 2:
            if (T2[T2[i]->children[0]]->data > T2[T2[i]->children[1]]->data) { x = 0; y = 1;}
            else { x = 1; y = 0; }
            T2[i]->left = T2[T2[i]->children[y]];
            T2[i]->right = T2[T2[i]->children[x]];
            break;
        }
    }
}

double HightBST(Node* root){
    if (root == NULL) {
        return -1; 
    }
    return(fmax(HightBST(root->right) , HightBST(root->left))+1);
}


void BF(vector <Node*>& tree) {
    for (int i = 0; i < tree.size(); i++) {
        tree[i]->bf = HightBST(tree[i]->right) - HightBST(tree[i]->left);
    }
}



int i = 0;
void Ch_setter(Node *&p) {

    if (p == NULL)return;

    if (p->left != NULL) {
        p->children[0] = p->left->index;
        i++;
    }
    if (p->right != NULL) {
        p->children[1] = p->right->index;
        i++;
    }

    p->child_count = i;
    i = 0;
    Ch_setter(p->right);
    Ch_setter(p->left);
    
}
void mearger(Node* A, Node* B, Node*& ResMrg) {
    
    ResMrg = new Node;
    if (A == NULL && B == NULL) {
        ResMrg = NULL;
        return;
    }
    if (A == NULL) {
        A = new Node;
        A->data = 0;
        A->left = A->right = NULL;

    }
    if (B == NULL) {
        B = new Node;
        B->data = 0;
        B->left = B->right = NULL;
    }
    ResMrg->index = (i++);
    ResMrg->data = (A->data + B->data);
    mearger(A->right, B->right,ResMrg->right);
    mearger(A->left, B->left,ResMrg->left);
    return;
}

void mearge(Node* A, Node* B, Node*& ResMrg) {
    mearger(A, B, ResMrg);
    Ch_setter(ResMrg);
    
}




int main()
{

    double N;
    int option, choice;
    vector <Node*>m;
    vector <Node*> n;

    while (true) {

        cout << " ____________________________ Main Menu ____________________________ " << endl;
        cout << "|                                                                   |" << endl;
        cout << "| 1. creating tow BST by reading their data from file               |" << endl;
        cout << "| 2. Printing them in-order                                         |" << endl;
        cout << "| 3. Testing the value rounding function                            |" << endl;
        cout << "| 4. computes the height for two trees.                             |" << endl;
        cout << "| 5. stores the balance factor (bf) for each node in any given tree |" << endl;
        cout << "| 6. merge two trees in new one                                     |" << endl;
        cout << "| 7. Exit                                                           |" << endl;
        cout << "|___________________________________________________________________|" << endl;
        cout << " Enter your choice:";
        cin >> choice;

        switch (choice) {
        case 1:
            create("Text.txt", m, n);
            cout << "Done" << endl;
            break;
        case 2:
            cout << "\n\nfor 1st tree :-" << endl;
            print_inorder(m[0]);
            cout << "\nfor 2nd tree :-" << endl;
            print_inorder(n[0]);
            break;
        case 3:
            cout << "Enter a number to round it : ";
            cin >> N;
            cout << "Which tree do you want to round from? (enter 1 or 2) : ";
            cin >> option;
            switch (option) {
            case 1:  cout << "the closest number in 1st tree is :" << closest(N, m) << endl; break;
            case 2:  cout << "the closest number in 2nd tree is :" << closest(N, n) << endl; break;
            }
            break;
        case 4:
            cout << "the hight of 1st tree is : " << HightBST(m[0]) << endl;
            cout << "the hight of 2nd tree is : " << HightBST(n[0]) << endl;
            break;
        case 5:
            BF(m);
            BF(n);
            cout << "...Done"<<endl;
            break;
        case 6:
            Node * s;
            mearge(m[0], n[0], s);
            cout << "...Done\n" << "print result tree :-" << endl;
            print_inorder(s);
            break;

        case 7:return 0;
        }

    }
}
