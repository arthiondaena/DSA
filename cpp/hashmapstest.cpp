#include <iostream>

int hashing(int);

template <typename T>
class Node {
public:
    T value;
    Node* next;

    Node() : value(0), next(nullptr) {}
    Node(T data) : value(data), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    Node<T>* head;
    unsigned int size;

    LinkedList() : head(nullptr), size(0) {}

    LinkedList<T>& operator=(LinkedList<T>& rhs) {
        this->head = rhs.head;
        this->size = rhs.size;
        return *this;
    }

    void insert_first(T data);
    void insert_last(T data);
    void insert_at(int offset, T data);
    void add(T data);
    void delete_first();
    void delete_last();
    void delete_at(int offset);
    void delete_value(T data);
    void print();
    unsigned int get_size();
};

template <typename T>
void LinkedList<T>::insert_first(T data) {
    Node<T>* temp = new Node<T>(data);
    size++;
    if (this->head == nullptr) {
        head = temp;
        return;
    }
    temp->next = head;
    this->head = temp;
}

template <typename T>
void LinkedList<T>::insert_last(T data) {
    Node<T>* temp = new Node<T>(data);
    size++;
    if (this->head == nullptr) {
        head = temp;
        return;
    }
    Node<T>* thead = this->head;
    while (thead->next) {
        thead = thead->next;
    }
    thead->next = temp;
}

template <typename T>
void LinkedList<T>::insert_at(int offset, T data) {
    if (offset > size) {
        std::cout << "Offset is out of bounds" << std::endl;
        return;
    }
    if (offset == 1 || offset == 0) {
        insert_first(data);
        return;
    }
    Node<T>* temp = new Node<T>(data);
    Node<T>* thead = this->head;
    while (--offset > 1) {
        thead = thead->next;
    }
    Node<T>* t2 = thead->next;
    thead->next = temp;
    temp->next = t2;
    size++;
}

template <typename T>
void LinkedList<T>::add(T data) {
    insert_last(data);
}

template <typename T>
void LinkedList<T>::delete_first() {
    if (size == 0) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    this->head = this->head->next;
    size--;
}

template <typename T>
void LinkedList<T>::delete_last() {
    if (size == 0) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node<T>* temp = head;
    Node<T>* t2 = nullptr;
    while (temp->next != nullptr) {
        t2 = temp;
        temp = temp->next;
    }
    t2->next = nullptr;
    size--;
}

template <typename T>
void LinkedList<T>::delete_at(int offset) {
    if (offset > size) {
        std::cerr << "Offset is out of bounds: delete_at" << std::endl;
        return;
    }
    if (offset == 1) {
        delete_first();
        return;
    }
    Node<T>* temp = head;
    Node<T>* t2 = nullptr;
    while (--offset > 0) {
        t2 = temp;
        temp = temp->next;
    }
    t2->next = temp->next;
    temp->next = nullptr;
    size--;
}

template <typename T>
void LinkedList<T>::delete_value(T data) {
    if (head->value == data) {
        delete_first();
        return;
    }
    Node<T>* temp = head;
    Node<T>* t2 = nullptr;
    while (temp->value != data && temp != nullptr) {
        t2 = temp;
        temp = temp->next;
    }
    if (temp != nullptr && temp->value == data) {
        t2->next = temp->next;
        temp->next = nullptr;
        size--;
    } else {
        std::cout << "delete_value(): value not found" << std::endl;
    }
}

template <typename T>
void LinkedList<T>::print() {
    Node<T>* temp = this->head;
    while (temp != nullptr) {
        std::cout << temp->value << ' ';
        temp = temp->next;
    }
    std::cout << std::endl;
}

template <typename T>
unsigned int LinkedList<T>::get_size() {
    return size;
}

class Entry {
public:
    int key;
    int hash;
    int value;

    Entry(int k, int v) : key(k), value(v) {
        hash = hashing(k);
    }

    Entry() : key(0), value(0) {
        hash = hashing(key);
    }

    bool equal(const Entry& e) const {
        if (this->hash == e.hash) return true;
        return this->key == e.key;
    }

    friend bool operator==(const Entry& lhs, const Entry& rhs) {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const Entry& lhs, const Entry& rhs) {
        return lhs.value != rhs.value;
    }
};

class HashTableChaining {
private:
    const int default_capacity = 5;
    const double default_loadfactor = 0.75;

    double maxloadfactor;
    int capacity, threshold, size;
    LinkedList<Entry>* table;

    int normalizeindex(int n) {
        return n % capacity;
    }

    Entry* bucketSeekEntry(int, int);
    void bucketInsertEntry(int, Entry);
    int bucketRemoveEntry(int, int);
    void resizeTable();

public:
    HashTableChaining(int cap, double load) : capacity(cap), maxloadfactor(load), size(0) {
        threshold = cap * maxloadfactor;
        table = new LinkedList<Entry>[cap];
    }

    HashTableChaining(int cap) : capacity(cap), maxloadfactor(default_loadfactor), size(0) {}

    HashTableChaining() : capacity(default_capacity), maxloadfactor(default_loadfactor), size(0) {}

    int get_size() {
        return size;
    }

    void insert(int, int);
    int remove(int);
    int get(int);
    bool haskey(int);
};

Entry* HashTableChaining::bucketSeekEntry(int bucketIndex, int key) {
    LinkedList<Entry>& bucket = table[bucketIndex];
    Node<Entry>* current = bucket.head;
    while (current != nullptr) {
        if (current->value.key == key) {
            return &(current->value);
        }
        current = current->next;
    }
    return nullptr;
}


void HashTableChaining::bucketInsertEntry(int bucketIndex, Entry entry) {
    LinkedList<Entry>& bucket = table[bucketIndex];
    Entry* existent = bucketSeekEntry(bucketIndex, entry.key);
    if (existent == nullptr) {
        bucket.insert_last(entry);
        size++;
    } else {
        existent->value = entry.value;
    }
}

int HashTableChaining::bucketRemoveEntry(int bucketIndex, int key) {
    LinkedList<Entry>& bucket = table[bucketIndex];
    Node<Entry>* current = bucket.head;
    Node<Entry>* prev = nullptr;

    while (current != nullptr) {
        if (current->value.key == key) {
            if (prev == nullptr) {
                bucket.head = current->next;
            } else {
                prev->next = current->next;
            }
            int value = current->value.value;
            delete current;
            size--;
            return value;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}

void HashTableChaining::insert(int key, int value) {
    Entry newentry(key, value);
    int bucketIndex = normalizeindex(newentry.hash);
    bucketInsertEntry(bucketIndex, newentry);

    if (size > threshold) {
        resizeTable();
    }
}

int HashTableChaining::remove(int key) {
    int bucketIndex = normalizeindex(hashing(key));
    return bucketRemoveEntry(bucketIndex, key);
}

int HashTableChaining::get(int key) {
    int bucketIndex = normalizeindex(hashing(key));
    Entry* ent = bucketSeekEntry(bucketIndex, key);
    if (ent == nullptr) {
        return -1;
    } else {
        return ent->value;
    }
}

bool HashTableChaining::haskey(int key) {
    int bucketIndex = normalizeindex(hashing(key));
    return bucketSeekEntry(bucketIndex, key) != nullptr;
}

void HashTableChaining::resizeTable() {
    int newCapacity = capacity * 2;
    LinkedList<Entry>* newTable = new LinkedList<Entry>[newCapacity];

    for (int i = 0; i < capacity; i++) {
        LinkedList<Entry>& bucket = table[i];
        Node<Entry>* current = bucket.head;
        while (current != nullptr) {
            Entry entry = current->value;
            int newBucketIndex = normalizeindex(entry.hash);
            newTable[newBucketIndex].insert_last(entry);
            current = current->next;
        }
    }

    delete[] table;
    table = newTable;
    capacity = newCapacity;
    threshold = capacity * maxloadfactor;
}

int hashing(int data) {
    int num = 0;
    while (data) {
        num += num * 10 + (data % 10);
        data /= 10;
    }
    return num % 16;
}

int main() {
    HashTableChaining tab;
    tab.insert(69, 100);
    tab.insert(70, 102);
    std::cout << tab.get(70) << std::endl;
    return 0;
}
