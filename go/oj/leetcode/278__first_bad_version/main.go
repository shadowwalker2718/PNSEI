package _78__first_bad_version

//You are a product manager and currently leading a team to develop a new produc
//t. Unfortunately, the latest version of your product fails the quality check. Si
//nce each version is developed based on the previous version, all the versions af
//ter a bad version are also bad.
//
// Suppose you have n versions [1, 2, ..., n] and you want to find out the first
// bad one, which causes all the following ones to be bad.
//
// You are given an API bool isBadVersion(version) which will return whether ver
//sion is bad. Implement a function to find the first bad version. You should mini
//mize the number of calls to the API.
//
// Example:
//
//
//Given n = 5, and version = 4 is the first bad version.
//
//call isBadVersion(3) -> false
//call isBadVersion(5) -> true
//call isBadVersion(4) -> true
//
//Then 4 is the first bad version. 
//
// Related Topics Binary Search
// 👍 1512 👎 691



/**
 * Forward declaration of isBadVersion API.
 * @param   version   your guess about first bad version
 * @return 	 	      true if current version is bad
 *			          false if current version is good
 * func isBadVersion(version int) bool;
 */

const BadVersion = 4

func isBadVersion(n int) bool{
	return n>=BadVersion
}

func firstBadVersion(n int) int {
	h, t := 1, n
	for h<=t {
		m := h + (t-h)/2
		if isBadVersion(m) {
			// we know m is bad, but not sure if it is the first bad version
			// the first one must be in the range of [h, m-1]
			t = m - 1
		} else {
			h = m + 1
		}
	}
	return h
}

