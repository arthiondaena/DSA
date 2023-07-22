#include "LinkedList_template.h"
#include <vector>

int hashing(int);

class Entry{
    public:
    int key;
    int hash;
    int value;
    
    Entry(int k, int v){
        key=k;
        value=v;
        hash=hashing(k);
    }
    Entry(){
        key=0; 
        value=0;
        hash=hashing(key);
    }
    bool equal(const Entry &e) const{
        if (this->hash==e.hash) return 1;
        return this->key==e.key;
    }
    friend bool operator==(const Entry &lhs, const Entry &rhs){
        return lhs.value==rhs.value;
    }
    friend bool operator!=(const Entry &lhs, const Entry &rhs){
        return lhs.value!=rhs.value;
    }
    
};

class HashTableChaining{
    private:
        const int default_capacity=5;
        const double default_loadfactor=.75;

        double maxloadfactor;
        int capacity, threshold, size=0;
        std::vector<LinkedList<Entry>> table;

        //methods
        int normalizeindex(int n){return n%capacity;}
        Entry* bucketSeekEntry(int, int);
        void bucketInsertEntry(int, Entry);
        int bucketRemoveEntry(int, int);
        void resizeTable();
    public:
        //constructors
        HashTableChaining(int cap, double load):
            capacity(cap), maxloadfactor(load){
                threshold=cap*maxloadfactor;
                table.resize(cap);
            }
        HashTableChaining(int cap):
            HashTableChaining(cap, default_loadfactor){}
        HashTableChaining():
            HashTableChaining(default_capacity, default_loadfactor){}

        //methods
        int get_size(){return size;}
        void insert(int, int);
        int remove(int);
        int get(int);
        bool haskey(int);
        void printtable();
        
};

Entry* HashTableChaining::bucketSeekEntry(int bucketIndex, int key){
    LinkedList<Entry> bucket=table[bucketIndex];
    if (bucket.head==NULL) return NULL;
    for(auto b=bucket.head; b!=NULL; b=b->next)
        if(b->value.key==key) return &(b->value);
    return NULL;
}

void HashTableChaining::bucketInsertEntry(int bucketIndex, Entry entry){
    LinkedList<Entry> &bucket=table[bucketIndex];
    //if(bucket.head==NULL) table[bucketIndex]=bucket= new LinkedList<Entry>;

    Entry* existant=bucketSeekEntry(bucketIndex, entry.key);
    if(existant==NULL){
        bucket.add(entry);
        if(++size>threshold) resizeTable();
    }
    else{
        int oldvalue=existant->value;
        existant->value=entry.value;
    }
}

int HashTableChaining::bucketRemoveEntry(int bucketIndex, int key){
    Entry* entry=bucketSeekEntry(bucketIndex, key);
    if(entry==NULL) return -1;
    else{
        LinkedList<Entry> bucket=table[bucketIndex];
        bucket.delete_value(*entry);
        --size;
        return entry->value;
    }
}

void HashTableChaining::resizeTable(){
    capacity*=2;
    threshold=(int)(capacity*maxloadfactor);
    std::vector<LinkedList<Entry>> newtable(capacity);
    for(int i=0; i<table.size(); i++){
        if(table[i].head!=NULL){
            for(Node<Entry>* h=table[i].head; h!=NULL; h=h->next){
                int bucketIndex=normalizeindex(h->value.hash);
                newtable[bucketIndex].add(h->value);
            }
        }
        table[i].clear();
    }
    table=newtable;
}

void HashTableChaining::insert(int key, int value){
    Entry newentry (key, value);
    int bucketIndex=normalizeindex(newentry.hash);
    bucketInsertEntry(bucketIndex, newentry);
}

int HashTableChaining::remove(int key){
    int bucketIndex=normalizeindex(hashing(key));
    return bucketRemoveEntry(bucketIndex, key);
}

int HashTableChaining::get(int key){
    int bucketIndex=normalizeindex(hashing(key));
    Entry* ent=bucketSeekEntry(bucketIndex, key);
    if(ent==NULL) return -1;
    else return ent->value;
}

bool HashTableChaining::haskey(int key){
    int bucketIndex=normalizeindex(hashing(key));
    return bucketSeekEntry(bucketIndex, key)!=NULL;
}

void HashTableChaining::printtable(){
    for(int i=0; i<capacity; i++){
        LinkedList<Entry> buck=table[i];
        Node<Entry> *entry=buck.head;
        std::cout<<i;
        while(entry!=NULL){
            std::cout<<" -> "<<"("<<entry->value.key<<", "<<entry->value.value<<")";
            entry=entry->next;
        }
        std::cout<<"\n";
    }
}

int hashing(int data){
    int num=0;
    while(data){
        num+=num*10+(data%10);
        data/=10;
    }
    return num%16;
}

int main(){
    // HashTableChaining tab(4, .75);
    // tab.insert(69, 100);
    // tab.insert(70, 102);
    // tab.insert(94, 1232);
    // tab.insert(132, 28231);
    // int ans=tab.get(69);
    // tab.printtable();
    LinkedList<int> a;
    a.insert_first(5);
    a.insert_last(10);
    a.insert_last(15);
    a.insert_at(1, 20);
    a.insert_at(2, 25);
    //a.delete_at(5);
    a.delete_value(25);
    a.print();
    a.reverse();
    a.print();
    return 0;
}