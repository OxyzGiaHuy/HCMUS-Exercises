#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

void traversalNodes(Node* head);
int countNodes(Node* head);
void addHead(Node* &head, int val);
void addTail(Node* &head, int val);
void removeHead(Node* &head);
void removeTail(Node* &head);
void removeDuplicate(Node* head);

void traversalNodes(Node* head){
    for (Node* tmp = head; tmp != nullptr; tmp = tmp->next){
        cout << tmp->data << " ";
    }
    cout << "\n";
}

int countNodes(Node* head){
    int count = 0;
    for (Node* tmp = head; tmp != nullptr; tmp = tmp->next){
        count++;
    }
    return count;
}

void addHead(Node* &head, int val){
    Node* new_head = new Node{val, head}; // trick to create Node
    head = new_head;
}

void addTail(Node* &head, int val){
    if (head == nullptr){
        head = new Node{val, nullptr};
        return;
    }
    Node* tail = head;
    for (; tail->next != nullptr; tail = tail->next); // find tail
    Node* new_tail = new Node{val, nullptr};
    tail->next = new_tail;
}

void removeHead(Node* &head){
    if (head == nullptr) return;
    Node* tmp = head;
    head = head->next;
    delete tmp;
}

void removeTail(Node* &head){
    if (head == nullptr) return;
    if (head->next == nullptr){ // LL has 1 node
        delete head;
        head = nullptr; // avoid dangling pointer
        return;
    }
    Node* tail = head;
    Node* prev_tail = nullptr;
    while (tail->next != nullptr){
        prev_tail = tail;
        tail = tail->next;
    } // find tail and prev node of tail
    prev_tail->next = nullptr;
    delete tail;
}

void removeDuplicate(Node* head){
    for (Node* curr = head; curr->next != nullptr; curr = curr->next){
        Node* prev = curr; // to track prev node of next_
        for (Node* next_ = curr->next; next_ != nullptr;){
            if (next_->data == curr->data){
                // remove node next_
                Node* dup = next_;
                prev->next = next_->next;
                next_ = next_->next;
                delete dup;
            }
            else{
                prev = next_;
                next_ = next_->next;
            }
        }
    }
}

void freeList(Node* head){
    Node* curr = head;
    Node* next_;
    while (curr != nullptr){
        next_ = curr->next;
        delete curr;
        curr = next_;
    }
}

int main(){
    Node* head = nullptr;
    
    addHead(head, 10);
    addHead(head, 20);
    addHead(head, 30);
    addHead(head, 10);
    addTail(head, 20);
    addTail(head, 40);
    addTail(head, 10);
    addTail(head, 20);
    cout << "Linked List: ";
    traversalNodes(head); 
    cout << "Number of nodes: " << countNodes(head) << "\n";
    
    removeHead(head);
    cout << "Linked List after removing head: ";
    traversalNodes(head);

    removeTail(head);
    cout << "Linked List after removing tail: ";
    traversalNodes(head);

    removeDuplicate(head);
    cout << "Linked List after removing duplicates: ";
    traversalNodes(head); 

    freeList(head);
    return 0;
}