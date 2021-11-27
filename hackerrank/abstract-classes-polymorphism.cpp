// https://www.hackerrank.com/challenges/abstract-classes-polymorphism/problem?isFullScreen=true


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <fstream>
#include <chrono>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
    map<int, Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};


class LRUCache : public Cache
{
public:
    LRUCache() {};
    LRUCache(int cp) {
        this->cp = cp;
        head = nullptr;
        tail = nullptr;
    };
    ~LRUCache() {
        for (auto entry : mp)
        {
            delete entry.second;
        }
    };
    LRUCache(const LRUCache& object) {

    };
    LRUCache& operator=(const LRUCache& object) {
        if (this != &object)
        {
            // normal assignment
        }
        return *this;
    };
    virtual void set(int k, int v) {

        if (get(k) == -1) // cache miss
        {
            if (cp == mp.size()  // we are full
                && cp > 0)  // just in case if cp is zero, though it should not be 0
            {
                // so we have to remove tail
                Node* old_tail = tail;

                Node* prev_tail = nullptr;
                if (tail->prev != nullptr)
                {
                    prev_tail = tail->prev;
                }
                if (tail->prev != nullptr)
                {
                    tail->prev->next = nullptr;
                }

                mp.erase(tail->key);
                if (tail)
                    delete tail;

                tail = prev_tail;
            }
            // after deleting adding new node;

            Node* newNode = new Node(k, v);

            if (head != nullptr)
            {
                newNode->next = head;
                newNode->prev = nullptr;
                head->prev = newNode;
            }
            else
            {
                tail = newNode;
            }

            head = newNode;
            mp[k] = newNode;
        }
        else { // cache hit
            Node* nth = mp.at(k); 
            Node* nth_next = nth->next; 
            Node* nth_prev = nth->prev; 

            if (nth_next && nth_prev) // both left and right counterparts are present
            {
                nth->next->prev = nth_prev;
                nth->prev->next = nth_next;

                nth->value = v;
                nth->next = head;
                nth->prev = nullptr;
                head->prev = nth;
                head = nth;
            }
            else if (nth_next && !nth_prev) // this is head  and further elements present)
            {
                nth->value = v;
            }
            else if (!nth_next && nth_prev) // this is tail and previous elements present)
            {
                nth->prev->next = nullptr;

                tail = nth_prev;

                nth->value = v;
                nth->next = head;
                nth->prev = nullptr;
                head->prev = nth;
                head = nth;
            }
            else if (!nth_next && !nth_prev) // head is a tall
            {
                nth->value = v;
            }
        }

    }
    virtual int get(int k) {
        bool found = false;
        auto iterator = mp.find(k);
        if (iterator == mp.end()) // not found
        {
            return -1;
        }
        else
        {
            Node* n = mp.at(k);
            return n->value;
        }
    }

};

int main() {
    int n, capacity, i;

    ifstream in("input01.txt");
    ofstream out("actual_output01.txt", ios::binary);

    in >> n >> capacity;
    auto start = std::chrono::steady_clock::now();

    LRUCache l(capacity);
    for (i = 0; i < n; i++) {
        string command;
        in >> command;
        if (command == "get") {
            int key;
            in >> key;
            out << l.get(key) << endl;
        }
        else if (command == "set") {
            int key, value;
            in >> key >> value;
            l.set(key, value);
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
