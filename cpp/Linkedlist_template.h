#ifndef LLTemplate_H
#define LLTemplate_H

#include<iostream>
//using namespace std;

template<typename T>
class Node{
    public:
        T value;
        Node* next;
    
    Node(){
        value=0;
        next=NULL;
    }
    Node(T data){
        value=data;
        next=NULL;
    }
};

template<typename T>
class LinkedList{
    public:
    Node<T>* head=NULL;
    unsigned int size=0;

    LinkedList(){
        head=NULL;
    }

    LinkedList<T> operator=(const LinkedList<T> &rhs){
        this->head=rhs.head;
        this->size=rhs.size;
        return *this;
    }

    //function
    void insert_first(T data);
    void insert_last(T data);
    void insert_at(int offset, T data);
    void add(T data);
    void delete_first();
    void delete_last();
    void delete_at(int offset);
    void delete_value(T data);
    void reverse();
    void clear();
    void print();
    int len();
};

template<typename T>
void LinkedList<T>::insert_first(T data){
    Node<T>* temp= new Node<T>(data);
    size++;
    if(this->head==NULL){
        head=temp;
        return;
    }
    temp->next=head;
    this->head=temp;
    return;
}

template<typename T>
void LinkedList<T>::insert_last(T data){
    Node<T>* temp=new Node<T>(data); 
    size++;
    if(this->head==NULL){
        head=temp;
        return;
    }
    Node<T>* thead=this->head;
    while(thead->next){
        thead=thead->next;
    }
    thead->next=temp;
}

template<typename T>
void LinkedList<T>::insert_at(int offset, T data){
    if(offset>size){
        std::cout<<"Offset is out of bounds"<<std::endl;
        return;
    }
    if(offset==1||offset==0){
        insert_first(data);
        return;
    }
    Node<T> *temp=new Node<T>(data), *thead=this->head;
    while(--offset>1){
        thead=thead->next;
    }
    Node<T> *t2=thead->next;
    thead->next=temp;
    temp->next=t2;
    size++;
}

template<typename T>
void LinkedList<T>::add(T data){
    insert_last(data);
}

template<typename T>
void LinkedList<T>::delete_first(){
    if(size==0){
        std::cout<<"List is empty"<<std::endl;
        return;
    }
    Node<T> *h1=head;
    this->head=this->head->next;
    free(h1);
    size--;
}

template<typename T>
void LinkedList<T>::delete_last(){
    if(size==0){
        std::cout<<"List is empty"<<std::endl;
        return;
    }
    if(size==1){
        Node<T> *temp=head;
        head=NULL;
        free(temp);
        size--;
        return;
    }
    Node<T> *temp=head, *t2=NULL;
    while(temp->next!=NULL){
        t2=temp;
        temp=temp->next;
    }
    t2->next=NULL;
    free(temp);
    size--;
}

template<typename T>
void LinkedList<T>::delete_at(int offset){
    if(offset>size){
        std::cerr<<"Offset is out of bounds: delete_at"<<std::endl;
        return;
    }
    if(offset==1){
        delete_first();
        return;
    }
    Node<T> *temp=head, *t2=NULL;
    while(--offset>0){
        t2=temp;
        temp=temp->next;
    }
    t2->next=temp->next;
    free(temp);
    size--;
}

template<typename T>
void LinkedList<T>::clear(){
    while(size){
        delete_last();
    }
}

template<typename T>
void LinkedList<T>::delete_value(T data){
    if(head->value==data){
        delete_first();
        return;
    }
    Node<T> *temp=head, *t2=NULL;
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
        std::cout<<"delete_value(): value not found"<<std::endl;
    }
}

template<typename T>
void LinkedList<T>::reverse(){
    Node<T>* temp=this->head, *prev=NULL, *next;
    while(temp!=NULL){
        next=temp->next;
        temp->next=prev;
        prev=temp;
        temp=next;
    }
    this->head=prev;
}

template<typename T>
void LinkedList<T>::print(){
    Node<T> *temp=this->head;
    while(temp!=NULL){
        std::cout<<temp->value<<' ';
        temp=temp->next;
    }
    std::cout<<std::endl;
}

template<typename T>
int LinkedList<T>::len(){
    return size;
}

#endif