package practice.instacart;

import javax.xml.bind.annotation.adapters.CollapsedStringAdapter;
import java.sql.Time;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.TimeUnit;

/*
https://www.1point3acres.com/bbs/thread-654366-1-1.html
Instacart店面
这题也是地里之前看过的

1:写一个KV store， 可以直接用hashmap
2: set()的参数除了key， 还增加一个timestamp
    get()有两种：
    get(key) 返回最近的val
    get(key, timestamp) 返回对应的（key， timestamp）的value
3: 如果（key, timestamp）不存在，则返回这个timestamp之前最近的val
*/
public class KVStore {
    // Map<K, Map<T, V>>
    private Map<String, Map<Long, String>> m = new HashMap<>();

    public void set(String k, String v){
        Long t = System.currentTimeMillis();
        m.computeIfAbsent(k, key->new TreeMap<>()).put(t, v);
    }
    public String get(String k){
        TreeMap<Long, String> tree = (TreeMap<Long, String>) m.get(k);
        if (tree == null) {
            return null;
        } else {
            return tree.lastEntry().getValue();
        }
    }
    public String get(String k, Long timestamp){
        TreeMap<Long, String> tree = (TreeMap<Long, String>) m.get(k);
        if (tree == null) {
            return null;
        } else {
            return tree.get(timestamp);
        }
    }

    public String get_fuzzy(String k, Long timestamp){
        TreeMap<Long, String> tree = (TreeMap<Long, String>) m.get(k);
        if (tree == null) {
            return null;
        } else {
            Map.Entry<Long, String> me = tree.lowerEntry(timestamp);
            if (me == null){
                return null;
            }
            return me.getValue();
        }
    }
    public static void main(String[] args) throws InterruptedException {
        KVStore kv = new KVStore();
        Long t1 = System.currentTimeMillis();
        kv.set("henry", "woo1");
        Thread.sleep(1);
        kv.set("henry", "woo2");
        Thread.sleep(10);
        Long t2 = System.currentTimeMillis();
        Thread.sleep(1);
        kv.set("henry", "woo3");
        System.out.println(kv.get("henry"));
        System.out.println(kv.get("henry", t2));
        System.out.println(kv.get_fuzzy("henry", t2));
    }
}
