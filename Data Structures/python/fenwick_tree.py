class FenwickTree:
    def __init__(self, l: list):
        l.insert(0, 0);
        self.tree=l
        self.N=len(l)
        for i in range(0, self.N):
            parent=i+self.lsb(i)
            if(parent<self.N): self.tree[parent]+=self.tree[i]
    
    def lsb(self, i):
        return (i & -i)
    
    def __prefixSum(self, i):
        sum=0
        while(i!=0):
            sum+=self.tree[i]
            i&=~self.lsb(i)
        return sum
    
    def sum(self, i, j):
        assert i<=j
        return self.__prefixSum(j)-self.__prefixSum(i-1)
    
    def get(self, i):
        return self.sum(i, i)
    
    def add(self, i, val):
        while(i<self.N):
            self.tree[i]+=val
            i+=self.lsb(i)
    
    def set(self, i, val):
        self.add(i, val-self.get(i))

ft=FenwickTree([1, 2, 3, 4, 5, 6, 7])
for i in range(1, 8):
    print(ft.sum(1, i), end=" ")