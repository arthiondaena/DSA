class Node:
    def __init__(self, data=0) -> None:
        self.prev=None
        self.next=None
        self.val=data
    def laterNode(self, i):
        if(i==0): return self
        assert self
        self=self.next.laterNode(i-1)
class DoubleLinked:
    def __init__(self) -> None:
        self.head=None
        self.tail=None
    
    def __iter__(self):
        node=self.head
        while node:
            yield node.val
            node=node.next
    
    def insert_first(self, n):
        temp=Node(n)
        if(self.head==None):
            self.head=temp
            self.tail=temp
        else:
            self.head.prev=temp
            temp.next=self.head
            self.head=temp
    
    def insert_last(self, n):
        temp=Node(n)
        if(self.tail==None):
            self.head=temp
            self.tail=temp
        else:
            self.tail.next=temp
            temp.prev=self.tail
            self.tail=temp
    
    def delete_first(self):
        assert self.head
        n=self.head.val
        self.head=self.head.next
        if self.head:
            self.tail=None
        else:
            self.head.prev=None
        return n
    
    def delete_last(self):
        assert self.tail
        n=self.tail.value
        self.tail=self.tail.prev
        if self.tail:
            self.head=None
        else:
            self.tail.next=None
        return n
    
    def remove(self, x1, x2):
        L2=DoubleLinked()
        L2.head=x1
        L2.tail=x2
        if(x1==self.head): self.head=x2.next
        else:              x1.prev.next=x2.next
        if(x2==self.tail): self.tail=x1.prev
        else:              x2.next.prev=x1.prev
        x1.prev=None
        x2.next=None
        return L2
    
    def reverse(self):
        n=self.head
        while(n):
            a=n.next
            n.prev, n.next=n.next, n.prev
            n=a
        self.head, self.tail=self.tail, self.head
    
LL=DoubleLinked()
LL.insert_last(3)
LL.insert_last(5)
LL.insert_last(7)
for node in LL:
    print(node, end=" ")
print()
LL.reverse()
for node in LL:
    print(node, end=" ")

    



    
