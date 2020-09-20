package oj.leetcode._359;

/*
359. Logger Rate Limiter
Design a logger system that receive stream of messages along with its timestamps, each message should be printed if
 and only if **it is not printed in the last 10 seconds**.

Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given
 timestamp, otherwise returns false.

It is possible that several messages arrive roughly at the same time.

Example:

Logger logger = new Logger();
// logging string "foo" at timestamp 1
logger.shouldPrintMessage(1, "foo"); returns true;
// logging string "bar" at timestamp 2
logger.shouldPrintMessage(2,"bar"); returns true;
// logging string "foo" at timestamp 3
logger.shouldPrintMessage(3,"foo"); returns false;
// logging string "bar" at timestamp 8
logger.shouldPrintMessage(8,"bar"); returns false;
// logging string "foo" at timestamp 10
logger.shouldPrintMessage(10,"foo"); returns false;
// logging string "foo" at timestamp 11
logger.shouldPrintMessage(11,"foo"); returns true;

https://leetcode.com/problems/logger-rate-limiter/
*/

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Logger {
    // time bucket - can the same message exist in different time bucket?? NO
    private int[] buckets = new int[10]; //store timestamp
    private Set[] sets = new Set[10]; // id to Strings printed in last 10s
    private Map<String, Integer> map= new HashMap<>();
    public Logger() {
        for (int i = 0; i < sets.length; ++i)
            sets[i] = new HashSet<String>();
    }
    public boolean shouldPrintMessage(int timestamp, String message) {
        int idx = timestamp % 10;
        if (timestamp != buckets[idx]) { // old data or no data ever
            sets[idx].clear();
            buckets[idx] = timestamp;
        }
        for (int i = 0; i < buckets.length; ++i) {
            if (timestamp - buckets[i] < 10){
                if(sets[i].contains(message))
                    return false;
            }

        }
        sets[idx].add(message);
        return true;
    }

    public static void main(String[] args) {

        Logger2 logger = new Logger2();
        // logging string "foo" at timestamp 1
        logger.shouldPrintMessage(1, "foo");// returns true;
        logger.shouldPrintMessage(1, "foo");// returns true;
        // logging string "bar" at timestamp 2
        logger.shouldPrintMessage(2, "bar");// returns true;
        // logging string "foo" at timestamp 3
        logger.shouldPrintMessage(3, "foo");// returns false;
        // logging string "bar" at timestamp 8
        logger.shouldPrintMessage(8, "bar");// returns false;
        // logging string "foo" at timestamp 10
        logger.shouldPrintMessage(10, "foo");// returns false;
        // logging string "foo" at timestamp 11
        logger.shouldPrintMessage(11, "foo");// returns true;
    }
}


class Logger2 {
    private int[] buckets = new int[10];
    private Set<String>[] sets = new Set[10];
    private Map<String, Integer> map= new HashMap<>();

    public Logger2() {
        for (int i = 0; i < sets.length; i++) {
            sets[i] = new HashSet<String>();
        }
    }

    public boolean shouldPrintMessage(int timestamp, String message) {
        int idx = timestamp % 10;
        if (buckets[idx] != timestamp) {
            /*for (String m : sets[idx]){
                map.remove(m);
            }*/
            sets[idx].clear();
            buckets[idx] = timestamp;
        }
        if (map.containsKey(message)){
            int x =map.get(message);
            if (sets[x].contains(message) && timestamp < buckets[x] + 10){
                return false;
            }
        }
        sets[idx].add(message);
        map.put(message, idx);
        return true;
    }
}
