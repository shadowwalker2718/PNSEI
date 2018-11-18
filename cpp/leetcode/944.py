def minDeletionSize(A):
    m=zip(*A)
    return sum(list(col) != sorted(col) for col in m)

a=["cba","daf","ghi"]
assert(minDeletionSize(a) == 1)