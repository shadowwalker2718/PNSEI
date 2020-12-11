"""
Given N point on a 2D plane as pair of (x, y) co-ordinates, we need to find maximum number of point which lie on the same line.

Examples:

Input : points[] = {-1, 1}, {0, 0}, {1, 1},
                    {2, 2}, {3, 3}, {3, 4}
Output : 4
Then maximum number of point which lie on same
line are 4, those point are {0, 0}, {1, 1}, {2, 2}, {3, 3}
"""

from collections import defaultdict


# T: O(N^3), S:O(N)
def FindMaxPoints(inp):  # inp [[0,1], [1,1], [2,2]], all values
    n = len(inp)
    if n < 3:
        return n
    cnt = defaultdict(int)
    mod_inp = []
    for val in inp:
        cnt[str(val)] += 1
        if cnt[str(val)] == 1:
            mod_inp.append(val)
    slope_dt = defaultdict(set)
    n = len(mod_inp)
    out = 0
    if n == 1:
        return cnt[str(mod_inp[0])]

    for i in range(n):
        # prev_slope = set()
        for j in range(i + 1, n):
            a, b = mod_inp[i]
            c, d = mod_inp[j]

            curr_out = cnt[str(mod_inp[i])] + cnt[str(mod_inp[j])]
            if a == c:
                curr_slope = float('inf')
                const = a
            else:
                curr_slope = (d - b) / (c - a)
                const = b - curr_slope * a
            # if curr_slope in prev_slope:
            #     continue
            # else:
            #     prev_slope.add(curr_slope)
            if curr_slope in slope_dt[str(mod_inp[j])] or curr_slope in slope_dt[str(mod_inp[i])]:
                continue
            else:
                slope_dt[str(mod_inp[j])].add(curr_slope)
                slope_dt[str(mod_inp[i])].add(curr_slope)
            for k in range(j + 1, n):
                e, f = mod_inp[k]
                if curr_slope < float('inf'):
                    if f - curr_slope * e - const == 0:
                        slope_dt[str(mod_inp[k])].add(curr_slope)
                        curr_out += cnt[str(mod_inp[k])]
                else:
                    if e == a:
                        slope_dt[str(mod_inp[k])].add(curr_slope)
                        curr_out += cnt[str(mod_inp[k])]
            out = max(out, curr_out)
    return out

import math
class Solution(object):
    def maxPoints(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """

        def max_points_on_a_line_containing_point_i(i):
            """
            Compute the max number of points
            for a line containing point i.
            """

            def slope_coprime(x1, y1, x2, y2):
                """ to avoid the precision issue with the float/double number,
                    using a pair of co-prime numbers to represent the slope.
                """
                delta_x, delta_y = x1 - x2, y1 - y2
                if delta_x == 0:  # vertical line
                    return (0, 0)
                elif delta_y == 0:  # horizontal line
                    return (sys.maxsize, sys.maxsize)
                elif delta_x < 0:
                    # to have a consistent representation,
                    #   keep the delta_x always positive.
                    delta_x, delta_y = - delta_x, - delta_y
                gcd = math.gcd(delta_x, delta_y)
                slope = (delta_x / gcd, delta_y / gcd)
                return slope

            def add_line(i, j, count, duplicates):
                """
                Add a line passing through i and j points.
                Update max number of points on a line containing point i.
                Update a number of duplicates of i point.
                """
                # rewrite points as coordinates
                x1 = points[i][0]
                y1 = points[i][1]
                x2 = points[j][0]
                y2 = points[j][1]
                # add a duplicate point
                if x1 == x2 and y1 == y2:
                    duplicates += 1
                # add a horisontal line : y = const
                elif y1 == y2:
                    nonlocal horizontal_lines
                    horizontal_lines += 1
                    count = max(horizontal_lines, count)
                # add a line : x = slope * y + c
                # only slope is needed for a hash-map
                # since we always start from the same point
                else:
                    slope = slope_coprime(x1, y1, x2, y2)
                    lines[slope] = lines.get(slope, 1) + 1
                    count = max(lines[slope], count)
                return count, duplicates

            # init lines passing through point i
            lines, horizontal_lines = {}, 1
            # One starts with just one point on a line : point i.
            count = 1
            # There is no duplicates of a point i so far.
            duplicates = 0
            # Compute lines passing through point i (fixed)
            # and point j (interation).
            # Update in a loop the number of points on a line
            # and the number of duplicates of point i.
            for j in range(i + 1, n):
                count, duplicates = add_line(i, j, count, duplicates)
            return count + duplicates

        # If the number of points is less than 3
        # they are all on the same line.
        n = len(points)
        if n < 3:
            return n

        max_count = 1
        # Compute in a loop a max number of points
        # on a line containing point i.
        for i in range(n - 1):
            max_count = max(max_points_on_a_line_containing_point_i(i), max_count)
        return max_count

# {-1, 1}, {0, 0}, {1, 1},
#                     {2, 2}, {3, 3}, {3, 4}

inp = [[-1, 1], [0, 0], [1, 1], [2, 2], [3, 3], [3, 4]]
inp = [[-1, 1], [0, 0], [1, 1], [2, 2], [3, 3], [3, 4], [3, 3]]
inp = [[-1, 1], [0, 0], [0, 0], [1, 1], [2, 2], [3, 3], [3, 4]]
inp = [[-1, -1], [-1, -1], [-1, -1], [-1, 1], [-1, 1]]
inp = [[0, 0], [94911151, 94911150], [94911152, 94911151]]
out = FindMaxPoints(inp)
print(out)

sln = Solution()
print(sln.maxPoints(inp))
