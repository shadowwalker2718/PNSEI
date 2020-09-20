package oj.leetcode._499;

import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

/*
There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up (u), down (d), left (l) or right (r), but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction. There is also a hole in this maze. The ball will drop into the hole if it rolls on to the hole.

Given the ball position, the hole position and the maze, find out how the ball could drop into the hole by moving the shortest distance. The distance is defined by the number of empty spaces traveled by the ball from the start position (excluded) to the hole (included). Output the moving directions by using 'u', 'd', 'l' and 'r'. Since there could be several different shortest ways, you should output the lexicographically smallest way. If the ball cannot reach the hole, output "impossible".

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The ball and the hole coordinates are represented by row and column indexes.



Example 1:

Input 1: a maze represented by a 2D array

0 0 0 0 0
1 1 0 0 1
0 0 0 0 0
0 1 0 0 1
0 1 0 0 0

Input 2: ball coordinate (rowBall, colBall) = (4, 3)
Input 3: hole coordinate (rowHole, colHole) = (0, 1)

Output: "lul"

Explanation: There are two shortest ways for the ball to drop into the hole.
The first way is left -> up -> left, represented by "lul".
The second way is up -> left, represented by 'ul'.
Both ways have shortest distance 6, but the first way is lexicographically smaller because 'l' < 'u'. So the output is "lul".

Example 2:

Input 1: a maze represented by a 2D array

0 0 0 0 0
1 1 0 0 1
0 0 0 0 0
0 1 0 0 1
0 1 0 0 0

Input 2: ball coordinate (rowBall, colBall) = (4, 3)
Input 3: hole coordinate (rowHole, colHole) = (3, 0)

Output: "impossible"

Explanation: The ball cannot reach the hole.

Note:

There is only one ball and one hole in the maze.
Both the ball and hole exist on an empty space, and they will not be at the same position initially.
The given maze does not contain border (like the red rectangle in the example pictures), but you could assume the border of the maze are all walls.
The maze contains at least 2 empty spaces, and the width and the height of the maze won't exceed 30.
*/

//https://www.cnblogs.com/grandyang/p/6725380.html
//你可能会有个疑问，到底 Dijkstra 算法和 BFS 算法究竟有啥区别。这是个好问题，二者在求最短路径的时候很相似，
//但却还是有些区别的。首先 Dijkstra 算法是求单源点的最短路径，图需要有权重，而且权重值不能为负，这道题中两点
//之间的距离可以看作权重，而且不会为负，满足要求。而 BFS 算法是从某点出发按广度优先原则依次访问连通的结点，图
//可以无权重。另外一点区别就是，BFS 算法是将未访问的邻居压入队列，然后再将未访问邻居的未访问过的邻居入队列再依
//次访问，而 Dijkstra 算法是在剩余的未访问过的结点中找出权重最小的并访问，这就是为什么要用一个优先队列（最小
//堆）来代替普通的 queue，这样就能尽量先更新离起点近的位置的 dp 值，优先队列里同时也存了该点到起点的距离，这
//个距离不一定是最短距离，可能还能松弛。但是如果其 dp 值已经小于优先队列中保存的距离，那么就不必更新其周围位置
//的距离了，因为优先队列中保存的这个距离值不是最短的，使用它来更新周围的 dp 值没有意义。这相当于利用了松弛操作
//来进行剪枝，大大提高了运算效率，之后就是类似于之前的 BFS 的操作了，遍历其周围的四个位置，尝试去更新其 dp 值。
public class Solution {
    class Path {
        int x, y, dist;
        String path;
        public Path(int x, int y, int dist, String path) {
            this.x = x;
            this.y = y;
            this.dist = dist;
            this.path = path;
        }
        @Override
        public String toString() {
            return x + " " + y + " " + dist + " " + path;
        }
    }
    public String findShortestWay(int[][] maze, int[] ball, int[] hole) {
        int m = maze.length, n = maze[0].length;
        PriorityQueue<Path> q = new PriorityQueue<>((a, b) -> {
            if (a.dist == b.dist) {
                return a.path.compareTo(b.path);
            } else {
                return a.dist - b.dist;
            }
        });
        Set<Integer> visited = new HashSet<>();
        q.offer(new Path(ball[0], ball[1], 0, ""));
        int[][] dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        String[] ways = {"d", "u", "r", "l"};
        while (!q.isEmpty()) {
            Path cur = q.poll();
            //System.out.println(cur);
            if (cur.x == hole[0] && cur.y == hole[1]) return cur.path;
            if (!visited.add(cur.x * n + cur.y)) continue;
            for (int i = 0; i < dirs.length; i++) {
                int[] dir = dirs[i];
                int x = cur.x, y = cur.y, k = 0;
                while (x >= 0 && y >= 0 && x < m && y < n && maze[x][y] == 0) {
                    k++;
                    if (x == hole[0] && y == hole[1]) {
                        q.offer(new Path(x, y, cur.dist + k, cur.path + ways[i]));
                        break;
                    } else {
                        x += dir[0];
                        y += dir[1];
                    }
                }
                x -= dir[0];
                y -= dir[1];
                k--;
                q.offer(new Path(x, y, cur.dist + k, cur.path + ways[i]));
            }
        }
        return "impossible";
    }
}
