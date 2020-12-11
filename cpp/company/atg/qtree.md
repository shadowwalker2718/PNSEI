# Quad-Tree

## Description of Question

Quadtree is a tree data structure in which each internal node either is a leaf node or has exactly 4 childern. Quadtrees are most often used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions. One of the common use cases of quadtree is image compression, for example:

Input Image:
```
+---------+--------+
|  2 |  2 |  3 | 3 |
+----|----|----|---|
|  2 |  2 |  3 | 3 |
+----+----|--------|
|  4 |  2 |  5 | 5 |
+----|----|----|---|
|  2 |  3 |  5 | 5 |
+----+----+--------+
```

Quadtree representation:
```
+---------+--------+
|         |        |
|    2    |    3   |
+----+----|--------|
| 4  | 2  |        |
+----|----|    5   |
| 2  | 3  |        |
+----+----+--------+
```

Design the quadtree data structure and write a function that builds a quadtree for an input image, where image will be given as a two-d array of integers.

## Solution to Question

Recursive solution: build 4 subtrees first and see if they need to be merged as one leaf node.

```go
package main

import "fmt"

// QuadTree Node
type QuadTreeNode struct {
    Value int
    IsLeaf bool

    NorthwestNode *QuadTreeNode
    NortheastNode *QuadTreeNode
    SouthwestNode *QuadTreeNode
    SoutheastNode *QuadTreeNode
}

func MakeQuadTree(img [][]int) *QuadTreeNode{
    if len(img) == 0 {
        return nil
    }
    return MakeSubTree(img, 0, len(img[0])-1, 0, len(img)-1)
}

func MakeSubTree(img [][]int, x1 int, x2 int, y1 int, y2 int) *QuadTreeNode{
    if x1 == x2 && y1 == y2 {
        return &QuadTreeNode{img[x1][y1], true, nil, nil, nil, nil}
    }

    newNode := new(QuadTreeNode)

    nw := MakeSubTree(img, x1, (x1+x2)/2, y1, (y1+y2)/2)
    ne := MakeSubTree(img, x1, (x1+x2)/2, (y1+y2)/2+1, y2)
    sw := MakeSubTree(img, (x1+x2)/2+1, x2, y1, (y1+y2)/2)
    se := MakeSubTree(img, (x1+x2)/2+1, x2, (y1+y2)/2+1, y2)

    // merge nodes
    if nw.IsLeaf && ne.IsLeaf && sw.IsLeaf && se.IsLeaf &&
        nw.Value == ne.Value && nw.Value == sw.Value && nw.Value == se.Value {
            return &QuadTreeNode{nw.Value, true, nil, nil, nil, nil}
        }

    return &QuadTreeNode{0, false, nw, ne, sw, se}
}

func main() {
    img := [][]int{
        {2, 2, 3, 3},
        {2, 2, 3, 3},
        {4, 2, 5, 5},
        {2, 3, 5, 5}}

    root := MakeQuadTree(img)
    PrintQuadTree(root)

    img = [][]int{
        {1,1},
        {1,1}}
    root = MakeQuadTree(img)
    PrintQuadTree(root)

    img = [][]int{{1}}
    root = MakeQuadTree(img)
    PrintQuadTree(root)

    img = [][]int{}
    root = MakeQuadTree(img)
    PrintQuadTree(root)
}


/************************* Pretty Print ***************************/
func PrintQuadTree(root *QuadTreeNode) {
    fmt.Println("ROOT")
    PrintQuadTreeHelper(root, 0)
}

func PrintQuadTreeHelper(root *QuadTreeNode, level int) {
    indention := ""
    for i := 0; i < level; i++ {
        indention += "   "
    }
    indention += "L"
    if root == nil {
        fmt.Println(indention, "nil")
        return
    }
    if root.IsLeaf {
        fmt.Println(indention, root.Value)
        return
    }
    fmt.Println(indention, "nw:")
    PrintQuadTreeHelper(root.NorthwestNode, level+1)
    fmt.Println(indention, "ne:")
    PrintQuadTreeHelper(root.NortheastNode, level+1)
    fmt.Println(indention, "sw:")
    PrintQuadTreeHelper(root.SouthwestNode, level+1)
    fmt.Println(indention, "se:")
    PrintQuadTreeHelper(root.SoutheastNode, level+1)
}
```


Why is this question good?

Quadtree is a relatively new concept to most candidates. This can test candidate's ability to handle a new concept. Also this's decent recursion problem. If candidate can understand this very well and sort out the recursion steps and termination condition, this problem can be solved with very simple and elegant code. Otherwise, the code could be very messy. So, ability to handle new concept and clean coding would be two main things to test from this question.

Possible follow up

Speed up the construction algorithm: build sub-trees concurrently

Additional notes

https://en.wikipedia.org/wiki/Quadtree