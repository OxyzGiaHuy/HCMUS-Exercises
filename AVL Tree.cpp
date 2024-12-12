#include<iostream>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
    int height;
};

Node* newNode(int data);
int height(Node* root);
void updateHeight(Node* root);
int balanceFactor(Node* root);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
Node* insertNode(Node* root, int data);
Node* searchNode(Node* root, int data);
Node* deleteNode(Node* root, int data);
void NLR(Node* root);
void LNR(Node* root);
void LRN(Node* root);
void printLevel(Node* root, int level);
void LevelOrder(Node* root);

bool isFull(Node* root);
int countNode(Node* root);
bool isCompleteUtil(Node* root, int index, int nodeCount);
bool isComplete(Node* root);
bool isPerfect(Node* root);
int findCommonAncestor(Node* root, int x, int y);
void printSpecialNodes(Node* root);


Node* newNode(int data){
    Node* temp = new Node;
    temp->key = data;
    temp->left = temp->right = NULL;
    temp->height = -1;
    return temp;
}

int height(Node* root){
    if (root == NULL) return -1;
    else {
        int lheight = height(root->left);
        int rheight = height(root->right);
        return max(lheight, rheight) + 1;
    }
}

void updateHeight(Node* root){
    if (root != NULL) root->height = 1 + max(height(root->left), height(root->right));
}

int balanceFactor(Node* root){
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

// INSERT IN AVL TREE (cre: geeksforgeeks)
// T1, T2 and T3 are subtrees of the tree, rooted with y (on the left side) or x (on the right side)           
//      y                               x
//     / \     Right Rotation          /  \
//    x   T3   - - - - - - - >        T1   y 
//   / \       < - - - - - - -            / \
//  T1  T2     Left Rotation            T2  T3

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    
    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;  

    return y;
}

Node* insertNode(Node* root, int data){
    if (root == NULL) return newNode(data);
    if (data < root->key) root->left = insertNode(root->left, data);
    else if (data > root->key) root->right = insertNode(root->right, data);
    else return root;

    updateHeight(root);

    int balance = balanceFactor(root);

    if (balance > 1){
        if (data < root->left->key){
            // Left left Case
            //             T1, T2, T3 and T4 are subtrees.
            //          z                                       y 
            //         / \                                   /    \
            //        y   T4      Right Rotate (z)          x      z
            //       / \          - - - - - - - - ->      /  \    /  \ 
            //      x   T3                               T1  T2  T3  T4
            //     / \
            //   T1   T2
            return rightRotate(root);
        } else if (data > root->left->key){
            // Left Right Case
            //      z                               z                           x
            //     / \                            /   \                        /  \ 
            //    y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
            //   / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \ 
            // T1   x                          y    T3                    T1  T2 T3  T4
            //     / \                        / \ 
            //   T2   T3                    T1   T2
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if (balance < -1){
        if (data < root->right->key){
            // Right Left Case
            //    z                            z                            x
            //   / \                          / \                          /  \ 
            // T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
            //     / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
            //    x   T4                      T2   y                  T1  T2  T3  T4
            //   / \                              /  \
            // T2   T3                           T3   T4
            root->right = rightRotate(root->right);
            return leftRotate(root);
        } else if (data > root->right->key){
            // Right Right Case
            //   z                                y
            //  /  \                            /   \ 
            // T1   y     Left Rotate(z)       z      x
            //     /  \   - - - - - - - ->    / \    / \
            //    T2   x                     T1  T2 T3  T4
            //        / \
            //      T3  T4
            return leftRotate(root);
        }
    }

    updateHeight(root);
    return root;
}

Node* searchNode(Node* root, int data){
    if (root == NULL || root->key == data) return root;
    if (data < root->key) return searchNode(root->left, data);
    else return searchNode(root->right, data);
}

Node* deleteNode(Node* root, int data){
    if (root == NULL) return root;
    if (data < root->key){
        root->left = deleteNode(root->left, data);
    } else if (data > root->key) {
        root->right = deleteNode(root->right, data);
    } else {
        // 1 child or no child
        if (root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL){
            Node* temp = root-> left;
            delete root;
            return temp;
        }

        // 2 childs
        // find smallest in right subtree (inorder successor)
        Node* temp = root->right;
        while (temp->left != NULL){
            temp = temp->left;
        }

        root->key = temp->key;

        // delete inorder successor
        root->right = deleteNode(root->right, temp->key);
    }

    updateHeight(root);
    int balance = balanceFactor(root);

    if (balance > 1){
        if (balanceFactor(root->left) >= 0) return rightRotate(root);
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root); 
        }
    }

    if (balance < -1){
        if (balanceFactor(root->right) <= 0) return leftRotate(root);
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    updateHeight(root);
    return root;
}

void NLR(Node* root){
    if (root != NULL){
        cout << root->key << " ";
        NLR(root->left);
        NLR(root->right);
    }
}

void LNR(Node* root){
    if (root != NULL){
        LNR(root->left);
        cout << root->key << " ";
        LNR(root->right);
    }
}

void LRN(Node* root){
    if (root != NULL){
        LRN(root->left);
        LRN(root->right);
        cout << root->key << " ";
    }
}

void printLevel(Node* root, int level){
    if (root == NULL) return;
    if (level == 0) cout << root->key << " ";
    else if (level > 0) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void LevelOrder(Node* root){
    for (int i = 0; i <= height(root); i++){
        printLevel(root, i);
    }
}

bool isFull(Node* root){
    if (root == NULL) return true;
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)) return false;
    return isFull(root->left) && isFull(root->right);
}

int countNode(Node* root){
    if (root == NULL) return 0;
    else {
        int lcount = countNode(root->left);
        int rcount = countNode(root->right);
        return lcount + rcount + 1;
    }
}

bool isCompleteUtil(Node* root, int index, int nodeCount) {
    if (root == NULL) {
        return true;
    }
    if (index >= nodeCount) {
        return false;
    }
    return isCompleteUtil(root->left, 2 * index + 1, nodeCount) && isCompleteUtil(root->right, 2 * index + 2, nodeCount);
}

bool isComplete(Node* root) {
    int nodeCount = countNode(root);
    return isCompleteUtil(root, 0, nodeCount);
}

bool isPerfect(Node* root){
    int h = height(root);
    if (root == NULL) return true;
    if (root->left == NULL && root->right == NULL) return (h == 0);
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)) return false;
    return isPerfect(root->left) && isPerfect(root->right);
}

int findCommonAncestor(Node* root, int x, int y){
    if (root == NULL) return -1;
    if (x < root->key && y < root->key) return findCommonAncestor(root->left, x, y);
    if (x > root->key && y > root->key) return findCommonAncestor(root->right, x, y);
    return root->key;
}

// left child is a divisor of right child
void printSpecialNodes(Node* root){
    if (root == NULL) return;
    if (root->left != NULL && root->right != NULL){
        if (root->right->key % root->left->key == 0){
            cout << root->key << " ";
        }
    }
    printSpecialNodes(root->left);
    printSpecialNodes(root->right);
}

int main(){
    Node* root = NULL;
    root = insertNode(root, 8);
    root = insertNode(root, 6);
    root = insertNode(root, 4);
    root = insertNode(root, 7);
    root = insertNode(root, 10);
    // root = insertNode(root, 9);
    root = insertNode(root, 3);
    root = insertNode(root, 5);
    // root = insertNode(root, 11);
    NLR(root);
    cout << "\n";

    cout << "Is Full: " << isFull(root) << endl;
    cout << "Is Complete: " << isComplete(root) << endl;
    cout << "Is Perfect: " << isPerfect(root) << endl;
    cout << "LCA of 4 and 7: " << findCommonAncestor(root, 4, 7) << endl;
    cout << "Special Nodes: ";
    printSpecialNodes(root);
    cout << endl;

    return 0;
}