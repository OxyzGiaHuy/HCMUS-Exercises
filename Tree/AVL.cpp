#include<iostream>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
    int height;
};

Node* newNode(int data){
    return new Node{data, NULL, NULL, -1};
}

int height(Node* root){
    if (root != NULL) return -1;
    else return max(height(root->left), height(root->right)) + 1;
}

void updateHeight(Node* root){
    if (root != NULL) root->height = max(height(root->left), height(root->right)) + 1;
}

int balanceFactor(Node* root){
    // để biết cây có AVL không
    if (root == NULL) return 0;
    else return height(root->left) - height(root->right);
}

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* t = x->right;
    x->right = y;
    y->left = t;

    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* t = y->left;
    y->left = x;
    x->right = t;

    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* insertNode(Node* root, int data){
    // như insert BST
    if (root == NULL) return NULL;
    else if (root->key > data) root->left = insertNode(root->left, data);
    else if (root->key < data) root->right = insertNode(root->right, data);
    else return root; // bằng thì không chèn

    updateHeight(root);
    int balance = balanceFactor(root);

    if (balance > 1){
        // cây lệch sang bên trái
        if (data < root->left->key){
            // Left Left Case
            return rightRotate(root);
        }
        if (data > root->left->key){
            // Left Right Case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balance < -1){
        // cây lệch sang bên phải
        if (data < root->right->key){
            // Right Left Case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        if (data > root->right->key){
            // Right Right Case
            return leftRotate(root);
        }
    }
    updateHeight(root);
    return root;
}

Node *searchNode(Node *root, int data){
    if (root == NULL || root->key == data) return root;
    else if (root->key < data) return searchNode(root->right, data);
    else return searchNode(root->left, data);
}

Node *deleteNode(Node *root, int data){
    if (root == NULL) return NULL;
    else if (root->key > data) root->right = deleteNode(root->right, data);
    else if (root->key < data) root->left = deleteNode(root->left, data);
    else {
        if (root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = root->right;
        while (temp != NULL) temp = temp->left;
        root->key = temp->key;
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
    if (balance < -1)
    {
        if (balanceFactor(root->right) <= 0)
            return leftRotate(root);
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    updateHeight(root);
    return root;
}

void preoderTraversal(Node *root)
{
    // Root Left Right
    if (root != NULL)
    {
        cout << root->key << " ";
        preoderTraversal(root->left);
        preoderTraversal(root->right);
    }
}

void inoderTraversal(Node *root)
{
    // Left Root Right
    if (root != NULL)
    {
        inoderTraversal(root->left);
        cout << root->key << " ";
        inoderTraversal(root->right);
    }
}

void postoderTraversal(Node *root)
{
    // Left Right Root
    if (root != NULL)
    {
        postoderTraversal(root->left);
        postoderTraversal(root->right);
        cout << root->key << " ";
    }
}

void printLevel(Node *root, int level)
{
    if (root != NULL)
    {
        if (level == 0)
            cout << root->key << " ";
        if (level > 0)
        {
            printLevel(root->left, level - 1);
            printLevel(root->right, level - 1);
        }
    }
}

void levelOrderTraversal(Node *root)
{
    int h = height(root);
    for (int i = 0; i <= h; i++)
    {
        printLevel(root, i);
        cout << "\n";
    }
}

bool isFull(Node *root);

int countNode(Node *root){
    if (root == NULL) return 0;
    else return (countNode(root->left) + countNode(root->right)) + 1;
}

bool isCompleteUtil(Node *root, int index, int nodeCount);
bool isComplete(Node *root);
bool isPerfect(Node *root);
int findCommonAncestor(Node *root, int x, int y);
void printSpecialNodes(Node *root);

