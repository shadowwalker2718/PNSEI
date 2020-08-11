from hashlib import md5
from struct import unpack_from
from bisect import bisect_left

NODES = 100
NODES2 = 101
VNODES = 1000

ITEMS = 1000000  # 10m key


def _hash(value):
    k = md5(str(value).encode('utf-8')).digest()
    ha = unpack_from(">I", k)[0]
    return ha


ring = []
hash2node = {}
ring2 = []
hash2node2 = {}
for n in range(NODES):
    for v in range(VNODES):
        h = _hash(str(n) + str(v))
        ring.append(h)
        hash2node[h] = n
ring.sort()
for i in range(1, 10):
    print("ring1 value", ring[-i], ", realnode:", hash2node[ring[-i]])
print("*" * 50)
for n in range(NODES2):  # 101
    for v in range(VNODES):
        h = _hash(str(n) + str(v))
        ring2.append(h)
        hash2node2[h] = n
ring2.sort()
for i in range(1, 10):
    print("ring2 value", ring2[-i], ", realnode:", hash2node2[ring2[-i]])
print(len(ring))
print(len(ring2))
print("*" * 50)
change = 0
for item in range(ITEMS):
    h = _hash(str(item))
    n = bisect_left(ring, h)
    n2 = bisect_left(ring2, h)
    if hash2node[ring[n]] != hash2node2[ring2[n2]]:
        change += 1
print("Change: %d\t(%0.2f%%)" % (change, change * 100.0 / ITEMS))
