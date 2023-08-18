from linked_list import Linkedlist

class Queue:
    def __init__(self):
        self.q=Linkedlist()

    def offer(self, elem):
        self.q.append(elem)

    def poll(self):
        tmp=self.q.head.data
        self.q.delete_first()
        return tmp

    def peek(self):
        tmp=self.q.head.data
        return tmp

    def size(self):
        return self.q.len()
    
    def isEmpty(self):
        return self.q.len()==0
   