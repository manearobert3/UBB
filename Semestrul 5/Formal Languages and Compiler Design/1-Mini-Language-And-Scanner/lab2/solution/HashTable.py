class Node:
    def __init__(self, key):
        self.key = key
        self.next = None
    def __str__(self):
        return str(self.key)



class HashTable:

    def __init__(self):
        self.length = 0
        self.size = 1000
        self.table = [None] * self.size

    def hashFunc(self, key):
        return hash(key) % self.size

    def search(self,key):
        index = self.hashFunc(key)
        first_location, second_location = index, 0
        current = self.table[index]

        while current:
            if current.key == key:
                return [first_location + 1, second_location + 1]
            else:
                current = current.next
        return [0,0]

    def insert(self, key):
        index = self.hashFunc(key)
        current = self.table[index]
        while current:
            if current.key == key:
                return
            current = current.next
        new_node = Node(key)
        new_node.next = self.table[index]
        self.table[index] = new_node
        self.length += 1

        if self.length / self.size > 0.75:
            self.resize(2 * self.size)

    def remove(self,key):
        index = self.hashFunc(key)
        previous = None
        current = self.table[index]
        while current:
            if current.key == key:
                if previous:
                    previous.next = current.next
                else:
                    self.table[index] = current.next
                self.length -= 1
                return
            previous = current
            current = current.next
        raise KeyError(key)

    def __len__(self):
        return self.length

    def __contains__(self,key):
        try:
            self.search(key)
            return True
        except KeyError:
            return False

    def print_all(self):
        result = ""
        for node in self.table:
            if node:
                result += str(node) + "\n"
        return result

    def resize(self, new_size):
        old_table = self.table
        self.size = new_size
        self.table = [None] * self.size
        old_length = self.length
        self.length = 0

        for node in old_table:
            current = node
            while current:
                self._insert_without_resize(current.key)
                current = current.next
        self.length = old_length

    def _insert_without_resize(self, key):
        index = self.hashFunc(key)
        new_node = Node(key)
        new_node.next = self.table[index]
        self.table[index] = new_node
