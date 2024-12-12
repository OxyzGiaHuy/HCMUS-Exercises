#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

struct Trailer;

struct Leader {
    int key;
    int count;
    Leader* next;
    Trailer* trailer;
};

struct Trailer {
    Leader* id;
    Trailer* next;
};

vector<Leader*> allNodes;

Leader* addList(Leader*& head, Leader*& tail, int key, int& size) {
    Leader* temp = head;
    tail->key = key;
    while (temp->key != key) {
        temp = temp->next;
    }
    if (temp == tail) {
        tail = new Leader();
        temp->next = tail;
        temp->count = 0;
        temp->trailer = nullptr;
        size++;
        allNodes.push_back(temp);
    }
    return temp;
}

void topoSort(Leader*& head, Leader*& tail, int size, ofstream& output) {
    Leader* p = head;
    Leader* q;
    head = nullptr;

    while (p != tail) {
        q = p;
        p = p->next;
        size--;
        if (q->count == 0) {
            q->next = head;
            head = q;
        }
    }

    q = head;
    while (q) {
        output << q->key << " "; 
        Trailer* t = q->trailer;
        q = q->next;
        while (t) {
            Leader* p = t->id;
            p->count--;
            if (p->count == 0) {
                p->next = q;
                q = p;
            }
            t = t->next;
        }
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        cerr << "Cannot open file!" << endl;
        return 1;
    }

    Leader* head = new Leader();
    Leader* tail = head;
    int size = 0;

    string data;
    input >> data;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == '(') {
            int u = 0, v = 0;
            i++;
            while (data[i] != ',') {
                u = u * 10 + (data[i] - '0');
                i++;
            }
            i++;
            while (data[i] != ')') {
                v = v * 10 + (data[i] - '0');
                i++;
            }

            Leader* leaderU = addList(head, tail, u, size);
            Leader* leaderV = addList(head, tail, v, size);

            Trailer* newTrailer = new Trailer();
            newTrailer->id = leaderV;
            newTrailer->next = leaderU->trailer;
            leaderU->trailer = newTrailer;
            leaderV->count++;
        }
    }

    input.close();

    topoSort(head, tail, size, output);

    output.close();

    for (Leader* node : allNodes) {
        delete node;
    }

    return 0;
}