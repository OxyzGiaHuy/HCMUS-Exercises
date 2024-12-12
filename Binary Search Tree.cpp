#include<iostream>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* newNode(int data);
Node* insertNode(Node* root, int data);
Node* searchNode(Node* root, int data);
Node* deleteNode(Node* root, int data);
void NLR(Node* root);
void LNR(Node* root);
void LRN(Node* root);
void printLevel(Node* root, int level);
void LevelOrder(Node* root);

int height(Node* root);
int countNode(Node* root);
int countInternal(Node* root);
int sumNode(Node* root);
int countLeaf(Node* root);
int countLess(Node* root, int x);
int countGreater(Node* root, int x);

// Exercise 1

// 1.
Node* newNode(int data){
    Node* temp = new Node;
    temp->key = data;
    temp->left = temp->right = NULL;
    return temp;   
}

// 2.
Node* insertNode(Node* root, int data){
    if (root == NULL) return newNode(data);
    if (data < root->key){
        root->left = insertNode(root->left, data);
    } else if (data > root->key){
        root->right = insertNode(root->right, data);
    }
    return root;
}

// 3.
Node* searchNode(Node* root, int data){
    if (root == NULL || data == root->key) return root;
    if (data < root->key){
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}

// 4.
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
    return root;
}

// 5.
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

// Exercise 2

// 1. 
int height(Node* root){
    if (root == NULL) return -1;
    else {
        int lheight = height(root->left);
        int rheight = height(root->right);
        return max(lheight, rheight) + 1;
    }
}

// 2.
int countNode(Node* root){
    if (root == NULL) return 0;
    else {
        int lcount = countNode(root->left);
        int rcount = countNode(root->right);
        return lcount + rcount + 1;
    }
}

int countInternal(Node* root){
    if (root == NULL || (root->left == NULL && root->right == NULL)) return 0;
    else {
        int lcount = countInternal(root->left);
        int rcount = countInternal(root->right);
        return lcount + rcount + 1;
    }
}

int sumNode(Node* root){
    if (root == NULL) return 0;
    else {
        int lsum = sumNode(root->left);
        int rsum = sumNode(root->right);
        return lsum + rsum + root->key;
    }
}

int countLeaf(Node* root){
    if (root == NULL) return 0;
    else if (root->left == NULL && root->right == NULL) return 1;
    else {
        int lcount = countLeaf(root->left);
        int rcount = countLeaf(root->right);
        return lcount + rcount;
    }
}

int countLess(Node* root, int x){
    if (root == NULL) return 0;
    if (root->key < x) return 1 + countLess(root->left, x) + countLess(root->right, x);
    else return countLess(root->left, x);
}

int countGreater(Node* root, int x){
    if (root == NULL) return 0;
    if (root->key > x) return 1 + countGreater(root->left, x) + countGreater(root->right, x);
    else return countGreater(root->right, x);
}


int main(){
    // Exercise 1
    Node* root = NULL;
    root = insertNode(root, 8);
    root = insertNode(root, 6);
    root = insertNode(root, 5);
    root = insertNode(root, 7);
    root = insertNode(root, 10);
    root = insertNode(root, 9);
    root = insertNode(root, 3);
    root = insertNode(root, 4);
    root = insertNode(root, 11);

    cout << "Pre-order: ";
    NLR(root);
    cout << "\n";
    cout << "In-order: ";
    LNR(root);
    cout << "\n";
    cout << "Post-order: ";
    LRN(root);
    cout << "\n";
    deleteNode(root, 8);
    LevelOrder(root);
    cout << "\n";

    // Exercise 2
    cout << height(root) << "\n";
    cout << countNode(root) << "\n";
    cout << countInternal(root) << "\n";
    cout << sumNode(root) << "\n";
    cout << countLeaf(root) << "\n";
    cout << countLess(root, 7) << "\n";
    cout << countGreater(root, 7) << "\n";
    return 0;
}