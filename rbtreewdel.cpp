//used the site programiz.com for reference in creating the red black tree

#include <iostream>
using namespace std;

struct Node {

    int value;
    Node *parent;
    Node *left;
    Node *right;
    bool color;

};

typedef Node *ptr;

class rbTree {
    private:
    ptr root;
    ptr T;

void initializeNULLNode(ptr node, ptr parent) {

    node->value = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = true;
}

void preOrderHelper(ptr node) {
    if (node != T) {
    cout << node->value << " ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
    }
}

ptr searchTreeHelper(ptr node, int key) {

    if (node == T || key == node->value){
        return node;
    }

    if (key < node->value) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}
  

  
void deleteFix(ptr x){
    ptr s;
    while (x != root && x->color){
      if (x == x->parent->left){
        s = x->parent->right;
        if (s->color == 1){
            s->color = true;
            x->parent->color = 1;
            leftRotate(x->parent);
            s = x->parent->right;
        }

        if (s->left->color && s->right->color){
            s->color = 1;
            x = x->parent;
        } 
        else{
            if (s->right->color){
                s->left->color = true;
                s->color = 1;
                rightRotate(s);
                s = x->parent->right;
        }

            s->color = x->parent->color;
            x->parent->color = true;
            s->right->color = true;
            leftRotate(x->parent);
            x = root;
        }
    } 
    else{
        s = x->parent->left;
        if (!s->color){
            s->color = true;
            x->parent->color = false;
            rightRotate(x->parent);
            s = x->parent->left;
        }

        if (s->right->color && s->right->color) {
            s->color = false;
            x = x->parent;
        }
        else {
            if (s->left->color) {
                s->right->color = true;
                s->color = false;
                leftRotate(s);
                s = x->parent->left;
        }

            s->color = x->parent->color;
            x->parent->color = true;
            s->left->color = true;
            rightRotate(x->parent);
            x = root;
        }
      }
    }
    x->color = true;
}


void rbTransplant(ptr u, ptr v) {
    if (u->parent == nullptr) {
        root = v;
    } 
    else if (u == u->parent->left){
        u->parent->left = v;
    } 
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}
  

void deleteNodeHelper(ptr node, int key) {
    ptr z = T;
    ptr x, y;
    while (node != T) {
      if (node->value == key) {
        z = node;
      }

      if (node->value <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == T) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == T){
        x = z->right;
        rbTransplant(z, z->right);
    } 
    else if (z->right == T){
        x = z->left;
        rbTransplant(z, z->left);
    } 
    else{
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
    } 
    else{
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
    }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color){
        deleteFix(x);
    }
}

    
void insertFix(ptr k) {
    ptr u;
    while (!k->parent->color) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (!u->color) {
            u->color = true;
            k->parent->color = true;
            k->parent->parent->color = false;
            k = k->parent->parent;
        } 
        else{
            if (k == k->parent->left) {
                k = k->parent;
                rightRotate(k);
            }
                k->parent->color = true;
                k->parent->parent->color = false;
                leftRotate(k->parent->parent);
            }
        } 
        else{
            u = k->parent->parent->right;

            if (!u->color){
                u->color = true;
                k->parent->color = true;
                k->parent->parent->color = false;
                k = k->parent->parent;
        } 
        else{
            if (k == k->parent->right) {
                k = k->parent;
                leftRotate(k);
            }
            k->parent->color = true;
            k->parent->parent->color = false;
            rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = true;
}
  

void printHelper(ptr root, string indent, bool last) {
    if (root != T) {
        cout << root->value << " ";
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}

   public:
    rbTree() {
    T = new Node;
    T->color = true;
    T->left = nullptr;
    T->right = nullptr;
    root = T;
  }

void preorder() {
    preOrderHelper(this->root);
}

ptr searchTree(int k){
    return searchTreeHelper(this->root, k);
}

    
ptr minimum(ptr node){
    while (node->left != T) {
      node = node->left;
    }
    return node;
}

ptr maximum(ptr node){
    while (node->right != T) {
      node = node->right;
    }
    return node;
  }

ptr successor(ptr x) {
    if (x->right != T) {
      return minimum(x->right);
    }

ptr y = x->parent;
    while (y != T && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

ptr predecessor(ptr x) {
    if (x->left != T) {
      return maximum(x->left);
    }

    ptr y = x->parent;
    while (y != T && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }
  

    
void leftRotate(ptr x) {
    ptr y = x->right;
    x->right = y->left;
    if (y->left != T) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr){
        this->root = y;
    } 
    else if (x == x->parent->left){
        x->parent->left = y;
    } 
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
  

    
  void rightRotate(ptr x) {
    ptr y = x->left;
    x->left = y->right;
    if (y->right != T){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr){
        this->root = y;
    } 
    else if (x == x->parent->right){
        x->parent->right = y;
    } 
    else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}
  


void insert(int key) {
    ptr node = new Node;
    node->parent = nullptr;
    node->value = key;
    node->left = T;
    node->right = T;
    node->color = false;

    ptr y = nullptr;
    ptr x = this->root;

    while (x != T) {
        y = x;
        if (node->value < x->value) {
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->value < y->value){
        y->left = node;
    }
    else{
        y->right = node;
    }

    if (node->parent == nullptr){
        node->color = true;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    insertFix(node);
}

ptr getRoot(){
    return this->root;
}

void deleteNode(int value){
    deleteNodeHelper(this->root, value);
}

void printTree(){
        if (root){
            printHelper(this->root, "", true);
        }
    }
};

int main(int argc, char **argv)
{
    rbTree tree;

   int sizearr=0;
    int arr[100];
    for(int i=0;i<argc-1;i++){
        arr[i] = atoi(argv[i+1]);
        sizearr++;
        tree.insert(arr[i]);
    }
    
    cout<<"pre order traversal"<<endl;
    tree.preorder();
    
    cout<<endl;
    cout<<"delete 5, 2, 47, 12"<<endl;
    tree.deleteNode(5);
    tree.deleteNode(2);
    tree.deleteNode(47);
    tree.deleteNode(12);
    tree.preorder();
    
    cout<<endl;
    


    return 0;
}