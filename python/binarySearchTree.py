from linked_list import Linkedlist
from queue import Queue

class Node:
    def __init__(self, l=None, r=None, d=None):
        self.left=l
        self.right=r
        self.data=d

class BinarySearchTree:
    def __init__(self):
        self.root=Node()
        self.__nodeCount=0
    
    def compared(self, n1, n2):
        if(n1>n2): return 1
        elif(n1<n2): return -1
        else: return 0
    
    def contains(self, elem):
        node=self.root
        while(node!=None):
            cmp=self.compared(elem, node.data)
            if(cmp<0):
                node=node.left
            elif(cmp>0):
                node=node.right
            else:
                return True
    
    def __add(self, node: Node, elem):
        if(node==None):
            node=Node(None, None, elem)
        else:
            cmp=self.compared(elem, node.data)
            if(cmp<0):
                node.left=self.__add(node.left, elem)
            else:
                node.right=self.__add(node.right, elem)
        return node

    def add(self, elem):
        if(self.root.data==None):
            self.root.data=elem
            self.__nodeCount+=1
            return
        if(self.contains(elem)): return
        node=self.__add(self.root, elem)
        self.__nodeCount+=1
    
    def __findMin(self, node: Node):
        while(node.left!=None):
            node=node.left
        return node
    
    def __findMax(self, node: Node):
        while(node.right!=None):
            node=node.right
        return node
    
    def __remove(self, node: Node, elem):
        cmp=self.compared(elem, node.data)
        if(cmp<0):
            node.left=self.__remove(node.left, elem)
        elif(cmp>0):
            node.right=self.__remove(node.right, elem)
        
        else:
            if(node.left==None):
                return node.right
            elif(node.right==None):
                return node.left
            
            else:
                tmp=self.__findMax(node.left)
                node.data=tmp.data
                node.left=self.__remove(node.left, tmp.data)
        return node
    
    def size(self):
        return self.__nodeCount

    def remove(self, elem):
        if(self.contains(elem)):
            node=self.__remove(self.root, elem)
            self.__nodeCount-=1

    def hei(self, node: Node):
        if(node ==None): return 0
        return max(self.hei(node.left), self.hei(node.right))+1
    
    def height(self):
        return self.hei(self.root)
    
    def __preorder(self, node: Node):
        if(node==None): return
        print(node.data, end=" ")
        self.__preorder(node.left)
        self.__preorder(node.right)
    
    def preorder(self):
        self.__preorder(self.root)

    def __inorder(self, node: Node):
        if(node==None): return
        self.__inorder(node.left)
        print(node.data, end=" ")
        self.__inorder(node.right)
    
    def inorder(self):
        self.__inorder(self.root)
    
    def __postorder(self, node: Node):
        if(node==None): return
        self.__postorder(node.left)
        self.__postorder(node.right)
        print(node.data, end=" ")
    
    def postorder(self):
        self.__postorder(self.root)

    def levelorder(self):
        q=Queue()
        q.offer(self.root)
        while(q.isEmpty() is False):
            tmp=q.poll()
            print(tmp.data, end=" ")
            if(tmp.left!=None): q.offer(tmp.left)
            if(tmp.right!=None): q.offer(tmp.right)

bst=BinarySearchTree()
for i in range(0, 5):
    bst.add(5-i)
    bst.add(5+i)
print("height:", bst.height())
print("size:", bst.size())
print("preorder traversal:", end=" ")
bst.preorder()
print("\ninorder traversal:", end=" ")
bst.inorder()
print("\npostorder traversal:", end=" ")
bst.postorder()
print("\nLevel order:", end=" ")
bst.levelorder()

    