#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

struct Stack{
    Node* top_node;
};

void init(Stack &st);
void push(Stack &st, int val);
void pop(Stack &st);
int top(Stack &st);

void init(Stack &st){
    st.top_node = nullptr;
}

void push(Stack &st, int val){
    Node* new_top = new Node{val, st.top_node};
    st.top_node = new_top;
}

void pop(Stack &st){
    if (st.top_node == nullptr){
        cout << "Stack is empty!\n";
        return;
    }
    Node* tmp = st.top_node;
    st.top_node = st.top_node->next;
    delete tmp; 
}

int top(Stack &st){
    if (st.top_node == nullptr){
        cout << "Stack is empty!\n";
        return -1; // present for empty stack
    }
    return st.top_node->data;
}


int main(){
    Stack st;
    init(st);

    push(st, 1);
    push(st, 2);
    push(st, 3);
    cout << "Top element is: " << top(st) << "\n"; 
    
    pop(st); 
    cout << "Top element is: " << top(st) << "\n";
    return 0;
}