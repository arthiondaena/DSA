class Unionfind:
    def __init__(self, s) -> None:
        self.__size=s
        self.__id=[x for x in range (0, s)]
        self.__sz=[1]*s
        self.__numComponents=s
    
    def find(self, p):
        root=p
        while(self.__id[root]!=root):  root=self.__id[root]

        if(root==p): return root
        
        while(p!=root):
            next=self.__id[p]
            self.__id[p]=root
            p=next
        
        return root
    
    def connected(self, p, q):
        return self.find(p)==self.find(q)
    
    def componentSize(self, p):
        return self.__sz[self.find(p)]
    
    def size(self):
        return self.__size
    
    def components(self):
        return self.__numComponents
    
    def unify(self, p, q):
        if(self.connected(p, q)): return
        root1=self.find(p)
        root2=self.find(q)
        if(self.__sz[root1]<self.__sz[root2]):
            self.__sz[root2]+=self.__sz[root1]
            self.__id[root1]=root2
            self.__sz[root1]=0
        else:
            self.__sz[root1]+=self.__sz[root2]
            self.__id[root2]=root1
            self.__sz[root2]=0
    
s=Unionfind(10)
for i in range (3, 10, 2):
    s.unify(i-2, i)
for i in range (0, 10):
    print( i, "th component size: ", s.componentSize(i))