package leetcode._630.CourseScheduleIII;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SolutionTest {

    @Test
    void scheduleCourse() {
        final int[][] courses = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
        final Solution sln = new Solution();
        final int num = sln.scheduleCourse(courses);
        assertEquals(num, 3);
    }
}
