#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

struct Queue{
    Node* front_node;
    Node* rear_node;
};

void init(Queue &q);
void enqueue(Queue &q, int val);
void dequeue(Queue &q);
int front(Queue &q);

void init(Queue &q){
    q.front_node = nullptr;
    q.rear_node = nullptr;
}

void enqueue(Queue &q, int val){
    Node* new_item = new Node{val, nullptr};
    if (q.rear_node == nullptr){
        q.front_node = q.rear_node = new_item;
    } else{
        q.rear_node->next = new_item;
        q.rear_node = new_item;
    }
}

void dequeue(Queue &q){
    if (q.front_node == nullptr){
        cout << "Queue is empty!\n";
        return;
    }
    Node* tmp = q.front_node;
    q.front_node = q.front_node->next;
    delete tmp;
}

int front(Queue &q){
    if (q.front_node == nullptr){
        cout << "Queue is empty!\n";
        return -1; // present for empty queue
    }
    return q.front_node->data;
}


int main(){
    Queue q;
    init(q); 

    enqueue(q, 1); 
    enqueue(q, 2);
    enqueue(q, 3);
    cout << "Front element is: " << front(q) << "\n";  
    
    dequeue(q); 
    cout << "Front element is: " << front(q) << "\n"; 
    return 0;
}