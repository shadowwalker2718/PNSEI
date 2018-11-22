//
// Created by root on 11/21/18.
//

#ifndef PNSEI_253_MEETING_ROOMS_II_H
#define PNSEI_253_MEETING_ROOMS_II_H


#include "henry.h"

namespace _253 {
/* https://leetcode.com/problems/meeting-rooms-ii/
 *
 * Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei),
 * find the minimum number of conference rooms required.

Example 1:
Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:
Input: [[7,10],[2,4]]
Output: 1

 *
 * */

struct Solution {
  int minMeetingRooms(vector<Interval> &ivs) {
    vector<pair<int, bool>> vpr;
    for (Interval &e: ivs)
      vpr.emplace_back(e.start, true), vpr.emplace_back(e.end, false);
    sort(vpr.begin(), vpr.end()); // when pr.first equals, for pr.second, false first!
    int c = 0, overlaps = 0;
    for (auto &e: vpr) {
      if (e.second) ++c; else --c;
      overlaps = max(overlaps, c);
    }
    return overlaps;
  }
};
}

#endif //PNSEI_253_MEETING_ROOMS_II_H
