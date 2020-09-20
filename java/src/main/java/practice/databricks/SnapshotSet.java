package practice.databricks;

import java.util.*;

// https://stackoverflow.com/questions/18902484/what-is-a-view-of-a-collection
// https://stackoverflow.com/questions/37782319/java-how-to-take-static-snapshot-of-concurrenthashmap
// https://www.geeksforgeeks.org/java-implementing-iterator-and-iterable-interface/
class SnapshotSetIterator implements Iterator {
    SnapshotSet ss;
    public int cursor = 0;
    public int right = 0; // exclusive

    // constructor 
    SnapshotSetIterator(SnapshotSet obj) {
        ss = obj;
        right = obj.val.size();
    }

    // Checks if the next element exists 
    public boolean hasNext() {
        while(cursor <ss.val.size() && ss.val.get(cursor)==null){
            cursor++;
        }
        return cursor < right;
    }

    // moves the cursor/iterator to next element 
    public String next() {
        if (!hasNext()){
            throw new NoSuchElementException();
        }
        String res = ss.val.get(cursor);
        cursor++;
        return res;
    }
}

// vector and index map ===> set
public class SnapshotSet implements Iterable{
    public Map<String, Integer> valueToIndex = new HashMap<>();
    public List<String> val = new ArrayList<>();

    public void add(String s){
        if(valueToIndex.containsKey(s))
            return;
        val.add(s);
        valueToIndex.put(s, val.size()-1);
    }

    public void remove(String s){
        if(!valueToIndex.containsKey(s))
            return;
        val.set(valueToIndex.get(s), null);
        valueToIndex.remove(s);
    }

    @Override
    public Iterator iterator() {
        return new SnapshotSetIterator(this);
    }

    public static void main(String[] args){
        SnapshotSet ss = new SnapshotSet();
        ss.add("Welcome");
        ss.add("To");
        ss.add("Geeks");
        ss.add("4");
        ss.add("Geeks");
        Iterator it = ss.iterator();

        ss.remove("4");
        while(it.hasNext()){
            System.out.println(it.next());
        }

        // Creating an empty Set
        Set<String> set = new HashSet<String>();
        // Use add() method to add elements into the Set
        set.add("Welcome");
        set.add("To");
        set.add("Geeks");
        set.add("4");
        set.add("Geeks");

        // Displaying the Set
        System.out.println("Set: " + set);

        // Creating an iterator
        Iterator value = set.iterator();

        // Displaying the values after iterating through the iterator
        System.out.println("The iterator values are: ");
        while (value.hasNext()) {
            System.out.println(value.next());
        }
    }

}
