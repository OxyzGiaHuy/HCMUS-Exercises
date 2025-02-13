#include<iostream>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
};


Node* newNode(int data){
    return new Node{data, NULL, NULL};
}

Node* insertNode(Node* root, int data){
    if (root == NULL) return newNode(data);
    // chạy xuống 2 nhánh
    else if (root->key < data) root->right = insertNode(root->right, data);
    else if (root->key > data) root->left = insertNode(root->left, data);
    return root; // trả về root để duy trì cây
}

Node* searchNode(Node* root, int data){
    if (root == NULL || root->key == data) return root;
    else if (root->key < data) return searchNode(root->right, data);
    else return searchNode(root->left, data);
}

Node* deleteNode(Node* root, int data){
    // search node cần xóa
    // hao hao insertNode
    if (root == NULL) return NULL;
    else if (root->key < data) root->right = deleteNode(root->right, data);
    else if (root->key > data) root->left = deleteNode(root->left, data);
    else {
        // tìm đc node cần xóa

        // 1 child or 0 child
        // xóa node đó và đẩy node con lên
        if (root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // 2 child
        // thay thế root bằng số nhỏ nhất ở cây con bên phải
        Node* temp = root->right;
        while (temp->left != NULL) temp = temp->left;
        root->key = temp->key;

        // xóa nút temp đó (inoder successor)
        root->right = deleteNode(root->right, temp->key);
    } 
    return root;
}

void preoderTraversal(Node *root){
    // Root Left Right
    if (root != NULL){
        cout << root->key << " ";
        preoderTraversal(root->left);
        preoderTraversal(root->right);
    }
}

void inoderTraversal(Node *root){
    // Left Root Right
    if (root != NULL){
        inoderTraversal(root->left);
        cout << root->key << " ";
        inoderTraversal(root->right);
    }
}

void postoderTraversal(Node *root){
    // Left Right Root
    if (root != NULL){
        postoderTraversal(root->left);
        postoderTraversal(root->right);
        cout << root->key << " ";
    }
}

void printLevel(Node *root, int level){
    if (root != NULL){
        if (level == 0) cout << root->key << " ";
        if (level > 0){
            printLevel(root->left, level - 1);
            printLevel(root->right, level - 1);
        }
    }
}

int height(Node *root){
    if (root == NULL) return -1;
    else return max(height(root->left), height(root->right)) + 1;
}

void levelOrderTraversal(Node *root){
    int h = height(root);
    for (int i = 0; i <= h; i++){
        printLevel(root, i);
        cout << "\n";
    }
}

int countNode(Node *root){
    if (root == NULL) return 0;
    else return (countNode(root->left) + countNode(root->right)) + 1;
}

int countLeaf(Node* root){
    if (root == NULL) return 0;
    else if (root->left == NULL && root->right == NULL) return 1;
    else return countLeaf(root->left) + countLeaf(root->right); 
}

int countInternal(Node *root){
    // đếm số đỉnh trong
    if (root == NULL || (root->left == NULL && root->right)) return 0;
    else return countInternal(root->left) + countInternal(root->right) + 1;

    // hoặc có thể tận dụng hàm countLeaf
    // return countNode(root) - countLeaf(root);
}

int sumNode(Node *root){
    if (root == NULL) return 0;
    else return sumNode(root->left) + sumNode(root->right) + root->key;
}

int countLess(Node *root, int x){
    // đếm bao nhiêu số < x
    if (root == NULL) return 0;
    else if (root->key > x) return countLess(root->left, x);
    else return countLess(root->left, x) + countLess(root->right, x) + 1; 
}

int countGreater(Node *root, int x){
    // đếm bao nhiêu số > x
    if (root == NULL) return 0;
    else if (root->key < x) return countGreater(root->right, x);
    else return countGreater(root->left, x) + countGreater(root->right, x) + 1;
}

int main()
{
    Node *root = NULL;
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
    preoderTraversal(root);
    cout << "\nIn-order: ";
    inoderTraversal(root);
    cout << "\nPost-order: ";
    postoderTraversal(root);
    cout << "\nLevel Order (after deleting 8):\n";
    deleteNode(root, 8);
    levelOrderTraversal(root);
    cout << "\n";

    cout << "Height: " << height(root) << "\n";
    cout << "Number of Nodes: " << countNode(root) << "\n";
    cout << "Number of Leaves:" << countLeaf(root) << "\n";
    cout << "Number of Internal Nodes: " << countInternal(root) << "\n";
    cout << "Sum all of nodes: " << sumNode(root) << "\n";
    cout << "Number of nodes smaller than 7: " << countLess(root, 7) << "\n";
    cout << "Number of nodes bigger than 7: " << countGreater(root, 7) << "\n";
    return 0;
}