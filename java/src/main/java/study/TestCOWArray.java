package study;

import java.util.ArrayList;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;
import static java.lang.System.out;

//https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/util/concurrent/CopyOnWriteArrayList.html

public class TestCOWArray {

    static void test(){
        try {
            List<String> list = new ArrayList<>();
            list.add("1");
            list.add("2");
            list.add("3");
            list.add("4");
            list.add("5");

            // get the iterator
            Iterator<String> it = list.iterator();

            //manipulate list while iterating
            while(it.hasNext()){
                System.out.println("list is:"+list);
                String str = it.next();
                System.out.println(str);
                if(str.equals("2"))
                    list.remove("5");
                if(str.equals("3"))
                    list.add("3 found");
                //below code don't throw ConcurrentModificationException
                //because it doesn't change modCount variable of list
                if(str.equals("4"))
                    list.set(1, "4");
            }
        }catch (ConcurrentModificationException e){
            out.print(e.toString());
        }

    }

    public static void main(String args[]) throws InterruptedException {
        test();

        // all mutative operations (add, set, and so on) are implemented by making a fresh copy of the underlying array
        CopyOnWriteArrayList<String> threadSafeList = new CopyOnWriteArrayList<String>();
        threadSafeList.add("Java");
        threadSafeList.add("J2EE");
        threadSafeList.add("Collection");

        Thread n = new Thread(){
            public void run(){
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                threadSafeList.clear();
            }
        };
        n.start();

        //add, remove operator is not supported by CopyOnWriteArrayList iterator
        Iterator<String> failSafeIterator = threadSafeList.iterator();
        threadSafeList.add("hello");
        Iterator<String> failSafeIterator2 = threadSafeList.iterator();
        Thread.sleep(5000);

        while(failSafeIterator.hasNext()){
            System.out.printf("Read from CopyOnWriteArrayList : %s %n", failSafeIterator.next());
            //failSafeIterator.remove(); //not supported in CopyOnWriteArrayList in Java
        }


        while(failSafeIterator2.hasNext()){
            System.out.printf("Read from CopyOnWriteArrayList : %s %n", failSafeIterator2.next());
            //failSafeIterator.remove(); //not supported in CopyOnWriteArrayList in Java
        }
        n.join();
    }
}
