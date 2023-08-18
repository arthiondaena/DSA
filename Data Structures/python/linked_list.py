class Node:
    def __init__(self, data=None):
        self.data=data
        self.next=None

class Linkedlist:
    def __init__(self, head=None):
        self.head=head
        self.__size=0
    
    def append(self, ele):
        new_node=Node(ele)
        current=self.head
        if current:
            while current.next:
                current=current.next
            current.next=new_node
        else:
            self.head=new_node
        self.__size+=1

    def delete_first(self):
        if(self.head==None): return
        self.head=self.head.next
        self.__size-=1

    def delete_last(self):
        tmp=None
        tmp1=self.head
        if(self.head==None): return
        while(tmp1!=None):
            tmp=tmp1
            tmp1=tmp1.next
        tmp.next=tmp1.next
        tmp1.next=None
        self.__size-=1

    def delete_at(self, i):
        assert i<self.__size
        if(i==0):
            self.delete_first()
            return
        tmp=self.head
        tmp1=None
        while(i):
            tmp1=tmp
            tmp=tmp.next
            i-=1
        tmp1.next=tmp.next
        tmp.next=None

    def len(self):
        return self.__size

    def print(self):
        current=self.head
        while current:
            print(current.data)
            current=current.next

    def mergeTwoLists(self, list1, list2):
        third = Node()
        tail = third

        while list1 and list2:
            if list1.data < list2.data:
               tail.next = list1
               list1 = list1.next
            else:
                tail.next = list2
                list2 = list2.next
            tail = tail.next

        if list1:
            tail.next = list1
        elif list2 :
            tail.next = list2

        return third.next
