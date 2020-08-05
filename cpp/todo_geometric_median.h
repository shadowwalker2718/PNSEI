#pragma once

// https://en.wikipedia.org/wiki/Geometric_median#Computation
// �1�7�1�2�1�7�1�7�0�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�5�1�7�1�71�0�4�1�7�1�7�1�70�5�1�7�1�7�1�7�1�3�1�7�1�7�0�7�1�7�0�5�1�7�1�7�1�7�0�4�1�7�1�7�0�0�1�7�1�7�1�7�1�7�1�7�1�7�1�4�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�6�1�7�1�7�1�7�1�7�1�7�1�7���1�7�1�7�1�7�1�7�1�7�1�7median�1�7�1�7�1�7�1�7follow up�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�72D space�1�7�1�7�1�7�1�7�1�7�0�5�1�7�1�7�0�4�1�7�1�7�0�5�1�7�1�7�1�7�1�4�1�7�1�7�1�7�1�7�1�7�1�7�0�2�1�7�1�7�1�7���1�7�1�7
// convex function -> gradient descent method
// The centroid or center of mass, defined similarly to the geometric median as minimizing the sum of the 
// squares of the distances to each point, can be found by a simple formula �1�7�1�7 its coordinates are the averages of the coordinates of
// the points �1�7�1�7 but it has been shown that no explicit formula, nor an exact algorithm involving only arithmetic operations and kth
// roots, can exist in general for the geometric median.
// Therefore, only numerical or symbolic approximations to the solution of this problem are possible under this model of computation.[14]
// https://arxiv.org/pdf/1606.05225.pdf
// https://cs.stackexchange.com/questions/30524/find-point-with-smallest-average-distance-to-a-set-of-given-points

