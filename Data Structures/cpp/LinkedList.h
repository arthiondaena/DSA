#ifndef LL_H
#define LL_H

#include<iostream>
using namespace std;

class Node{
    public:
        int value;
        Node* next;
    
    Node(){
        value=0;
        next=NULL;
    }
    Node(int data){
        value=data;
        next=NULL;
    }
};

class LinkedList{
    public:
    Node* head;
    unsigned int size=0;

    LinkedList(){
        head=NULL;
    }

    //function
    void insert_first(int data);
    void insert_last(int data);
    void insert_at(int offset, int data);
    void delete_first();
    void delete_last();
    void delete_at(int offset);
    void delete_value(int data);
    void print();
    int len();
};

void LinkedList::insert_first(int data){
    Node* temp= new Node(data);
    size++;
    if(this->head==NULL){
        head=temp;
        return;
    }
    temp->next=head;
    this->head=temp;
    return;
}

void LinkedList::insert_last(int data){
    Node* temp=new Node(data); 
    size++;
    if(this->head==NULL){
        head=temp;
        return;
    }
    Node* thead=this->head;
    while(thead->next){
        thead=thead->next;
    }
    thead->next=temp;
}

void LinkedList::insert_at(int offset, int data){
    if(offset>size){
        cout<<"Offset is out of bounds"<<endl;
        return;
    }
    if(offset==1||offset==0){
        insert_first(data);
        return;
    }
    Node *temp=new Node(data), *thead=this->head;
    while(--offset>1){
        thead=thead->next;
    }
    Node *t2=thead->next;
    thead->next=temp;
    temp->next=t2;
    size++;
}

void LinkedList::delete_first(){
    if(size==0){
        cout<<"List is empty"<<endl;
        return;
    }
    this->head=this->head->next;
    size--;
}

void LinkedList::delete_last(){
    if(size==0){
        cout<<"List is empty"<<endl;
        return;
    }
    Node *temp=head, *t2=NULL;
    while(temp->next!=NULL){
        t2=temp;
        temp=temp->next;
    }
    t2->next=NULL;
    size--;
}

void LinkedList::delete_at(int offset){
    if(offset>size){
        cerr<<"Offset is out of bounds: delete_at"<<endl;
        return;
    }
    if(offset==1){
        delete_first();
        return;
    }
    Node *temp=head, *t2=NULL;
    while(--offset>0){
        t2=temp;
        temp=temp->next;
    }
    t2->next=temp->next;
    temp->next=NULL;
    size--;
}

void LinkedList::delete_value(int data){
    if(head->value==data){
        delete_first();
        return;
    }
    Node *temp=head, *t2=NULL;
    while(temp->value!=data && temp!=NULL){
        t2=temp;
        temp=temp->next;
    }
    if(temp->value==data){
        t2->next=temp->next;
        temp->next=NULL;
        size--;
    }
    else{
        cout<<"delete_value(): value not found"<<endl;
    }
}

void LinkedList::print(){
    Node *temp=this->head;
    while(temp!=NULL){
        cout<<temp->value<<' ';
        temp=temp->next;
    }
    cout<<endl;
}

int LinkedList::len(){
    return size;
}

#endif