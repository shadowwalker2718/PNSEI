"""
Given a 2d map where 0s indicate the sea and 1s indicate the land. Lists the sizes of the islands.

1)

0 0 0 1
0 1 1 0
1 1 0 0
1 1 0 1

3 islands
Returns [6, 1, 1], the order does not matter
"""


# look over all elements,
# traversal of neighbors of 1, keep track of the number of ones,
# keep track of visited nodes,
# don't visit an element more than one,
# time: O(M) ; space: O(M) or inplace O(1)
def size_island(matrix):
    out = []
    #if len(matrix) == 0:
    #    return []

    def dfs(i, j):
        if matrix[i][j] == 0:
            return 0
        d = [[1, 0], [-1, 0], [0, 1], [0, -1]]
        matrix[i][j] = 0
        out = 1
        for di in d:
            if 0 <= i + di[0] < len(matrix):
                if -1 == j + di[1]:
                    out += dfs(i + di[0], len(matrix[0]) - 1)
                elif j + di[1] == len(matrix[0]):
                    out += dfs(i + di[0], 0)
                else:
                    out += dfs(i + di[0], j + di[1])
        return out

    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            if matrix[i][j] == 1:
                out += [dfs(i, j)]
    return out


"""1 0 0 1
0 1 1 0

[2,1,1]

0 0 0 1
0 1 1 0
1 1 0 0
1 1 0 1

"""


def test():
    matrix1 = []
    output_function = size_island(matrix1)
    print(output_function)

test()

"""


Given an initial map where 0s indicate sea and 1s indicate land. Also given a list of (x, y) pairs indicate the island to be added each time. Return a list of islands after each operation is conducted. 

1)
[[0, 0, 0, 0],
[0, 0, 0, 1],
[0, 1, 0, 0],
[0, 0, 0, 0],
[0, 0, 0, 0]]

(0, 0)
1 0 0 0
0 0 0 1
0 1 0 0
0 0 0 0
0 0 0 0
List has [3]

(0, 2)
1 0 1 0
0 0 0 1
0 1 0 0
0 0 0 0
0 0 0 0
List has [3, 4]

(3, 2)
1 0 1 0
0 0 0 1
0 1 0 0
0 0 1 0
0 0 0 0
List has [3, 4, 5]

(0, 1)
1 1 1 0
0 0 0 1
0 1 0 0
0 0 1 0
0 0 0 0
List has [3, 4, 5, 4]

(2, 2)
1 1 1 0
0 0 0 1
0 1 1 0
0 0 1 0
0 0 0 0
List has [3, 4, 5, 4, 3]

(1, 2)
1 1 1 0
0 0 1 1
0 1 1 0
0 0 1 0
0 0 0 0
List has [3, 4, 5, 4, 3, 1]

Python Function signature

def count_islands(m: int, n: int, positions: List[List[int]]) -> List[int]:
Operations = [(0, 0), (0, 2), (3, 2), (0, 1), (2, 2), (1, 2)]



# matrix_2
# [1, 0, 2,2]

if neighbor==1:
    parent1 = find(neighbor)
if neighbor==1:
    parent2 = find(neighbor)
if parent1 != parent2:
    parent[parent2] = parent[parent1]
    num_island -= 1

"""