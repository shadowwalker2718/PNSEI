#pragma once

// https://en.wikipedia.org/wiki/Geometric_median#Computation
// �ڶ��֣�������һ��1ά���飬ϣ���ܹ��ҳ�һ���㣬��ʹ������㵽������������ľ������С������median����follow up���������2D space�����һ��㣬��һ���㵽������ĺ���С��
// convex function -> gradient descent method
// The centroid or center of mass, defined similarly to the geometric median as minimizing the sum of the 
// squares of the distances to each point, can be found by a simple formula �� its coordinates are the averages of the coordinates of
// the points �� but it has been shown that no explicit formula, nor an exact algorithm involving only arithmetic operations and kth
// roots, can exist in general for the geometric median.
// Therefore, only numerical or symbolic approximations to the solution of this problem are possible under this model of computation.[14]
// https://arxiv.org/pdf/1606.05225.pdf
// https://cs.stackexchange.com/questions/30524/find-point-with-smallest-average-distance-to-a-set-of-given-points

