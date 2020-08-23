package oj.leetcode;

import foundation.NestedInteger;
import foundation.NestedIntegerImpl;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;

public class NestedIteratorTest {
    @Test
    public void testNestedIterator(){
        List<NestedInteger> nestedList = new ArrayList<>();
        nestedList.add(new NestedIntegerImpl().addInteger(1).addInteger(1));
        nestedList.add(new NestedIntegerImpl().setInteger(2));
        nestedList.add(new NestedIntegerImpl().addInteger(1).addInteger(1));
        NestedIterator i = new NestedIterator(nestedList);
        List<Integer> li = new ArrayList<>();
        while (i.hasNext()){
            li.add(i.next());
        }
        assertEquals(li.size(), 5);
    }
}
