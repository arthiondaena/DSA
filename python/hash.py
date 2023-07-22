#from prettytable import PrettyTable


class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None


class HashTable:
    def __init__(self, capacity):
        self.capacity = capacity
        self.size = 0
        self.table = [None] * capacity

    def _hash(self, key):
        return hash(key) % self.capacity

    def insert(self, key, value):
        index = self._hash(key)
        if self.table[index] is None:
            self.table[index] = Node(key, value)
        else:
            cur = self.table[index]
            while cur:
                if cur.key == key:
                    cur.value = value
                    self.size += 1
                    return
                cur = cur.next
            new_node = Node(key, value)
            new_node.next = self.table[index]
            self.table[index] = new_node
            self.size += 1

    def search(self, key):
        index = self._hash(key)

        cur = self.table[index]
        while cur:
            if cur.key == key:
                return cur.value + 1
            cur = cur.next
        raise KeyError(key)

    def remove(self, key):
        index = self._hash(key)

        prev = None
        current = self.table[index]

        while current:
            if current.key == key:
                if prev:
                    prev.next = current.next
                else:
                    self.table[index] = current.next
                    self.size -= 1
                    return
                prev = current
                current = current.next

        raise KeyError(key)

    def _len_(self):
        return self.size

    def _contains_(self, key):
        try:
            self.search(key)
            return True
        except KeyError:
            return False

    def pos_in_tab(self, key):
        index = self._hash(key)
        print(f"the position is {index}")
            
    def print_table(self):
        for i in range(self.capacity):
            print(f"Index {i}: ", end="")
            cur = self.table[i]
            while cur:
                print(cur.key, end=" ")
                cur = cur.next
            print()


my_table = HashTable(11)
my_table.insert("apple", 0)
my_table.insert("orange", 0)
my_table.insert("bananna", 2)
my_table.insert("cake", 3)
my_table.print_table()