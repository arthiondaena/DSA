#ifndef QueueTemplate_H
#define QueueTemplate_H

#include "Linkedlist_template.h"

template<typename T>
class Queue{
    private:
        LinkedList<T> queue;
    public:
        void offer(T elem){
            queue.add(elem);
        }
        T poll(){
            T data=queue.head->value;
            queue.delete_first();
            return data;
        }
        T peek(){
            return queue.head->value;
        }
        int size(){
            return queue.len();
        }
        bool isEmpty(){
            return queue.len()==0;
        }
};

#endif