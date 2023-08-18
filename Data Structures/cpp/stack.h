#ifndef StackTemplate_H
#define StackTemplate_H

#include "Linkedlist_template.h"

template <typename T>
class Stack{
    LinkedList<T> stack;
    public:
        void push(T elem){
            stack.insert_first(elem);
        }
        T pop(){
            T tmp=stack.head->value;
            stack.delete_first();
            return tmp;
        }
        T peek(){
            return stack.head->value;
        }
        int size(){
            return stack.len();
        }
        bool isEmpty(){
            return stack.len()==0;
        }
};

#endif