package oj.leetcode;

import foundation.NestedInteger;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import java.util.NoSuchElementException;

// https://leetcode.com/problems/flatten-nested-list-iterator/
public class NestedIterator implements Iterator<Integer> {
    private List<Integer> array = new ArrayList<>();
    private int index = 0;

    private void addList(List<NestedInteger> nestedList){
        for (NestedInteger ni: nestedList) {
            if (ni.isInteger()){
                array.add(ni.getInteger());
            } else {
                addList(ni.getList());
            }
        }
    }

    public NestedIterator(List<NestedInteger> nestedList) {
        addList(nestedList);
        index = 0;
    }

    @Override
    public Integer next() {
        if (!hasNext())
            throw new NoSuchElementException();
        return array.get(index++);
    }

    @Override
    public boolean hasNext() {
        return index<array.size();
    }
}
