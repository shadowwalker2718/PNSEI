import random


def gen_array():
    a = []
    for _ in range(3):
        s = ""
        for i in range(3):
            s += chr(int(random.randint(0, 1000) % 26) + 97)
        a.append(s)
    a[random.randint(0, 3)] = "melissa"
    return a


def is_melissa_here(a):
    for s in a:
        if s == 'melissa':
            print("found it")
    return True  # False


def hash_function(s):
    sum_result = 0
    for ch in s:
        sum_result += ord(ch)
    return sum_result % (122 * 7)


class HashTable:
    def __init__(self):
        self.iamarray = [None] * 122 * 70

    def put(self, key, value):
        i = hash_function(key)
        # chaining to resolve the collision
        if self.iamarray[i] is not None:
            tmp = self.iamarray[i]
            self.iamarray[i] = [tmp, (key, value)]
            return
        self.iamarray[i] = (key, value)

    def exist(self, key):
        index = hash_function(key)
        if self.iamarray[index] is None:
            return False
        if self.iamarray[index][0] == key:
            return True
        for k, v in self.iamarray[index]:
            if k == key:
                return True

    def get(self, key):
        index = hash_function(key)
        if self.iamarray[index] is None:
            return None
        if self.iamarray[index][0] == key:
            return self.iamarray[index][1]
        for k, v in self.iamarray[index]:
            if k == key:
                return v


if __name__ == "__main__":
    """
    print(hash_function("abc"))
    print(hash_function("melissa"))
    print(hash_function("jack"))
    """
    big_array = gen_array()
    big_array.append("lissame")
    ht = HashTable()
    for s in big_array:
        ht.put(s, len(s))
    print(ht.exist("melissa"))
    print(ht.exist("lissame"))
    print(ht.exist("jackwu"))
    print(ht.get("melissa"))
    # print(a)
