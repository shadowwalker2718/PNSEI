package practice.instacart;

/*
https://www.1point3acres.com/bbs/thread-615124-1-1.html
这题其实就是All susbset with k size的做法，用DFS在给的一堆牌里找size为3的的牌，每找到一手牌，就调helper函数validate
这手牌是不是符合对prefix，type of letter 和number of type of letter的要求。符合就立即停止搜索，返回找到的第一副牌。

K-combination
http://sde.quant365.com/combinatorics.html#combination-dfs
* */

import java.util.*;

public class CardGame2 {

    public List<String> run(String s){
        Scanner sc = new Scanner(s);
        sc.useDelimiter(" ");
        List<String> cards = new ArrayList<>();
        Set<List<String>> hands = new HashSet<>();
        while(sc.hasNext()){
            String n = sc.next();
            Iterator<List<String>> it = hands.iterator();
            while(it.hasNext()){
                List<String> x = it.next();
                x.add(n);
                if (x.size()== 3){
                    if (isValid(x))
                        return x;
                    else
                        it.remove();
                }
            }
            cards.add(n);
        }
        return null;
    }


    boolean isValid(List<String> hand) {
        if (hand.size()!=3)
            return false;
        Set<Character> set = new HashSet<>();
        for (int i=0;i<3;i++) {
            set.add(hand.get(i).charAt(0));
        }
        if (set.size() == 2) return false;
        set.clear();
        for (int i=0;i<3;i++) {
            set.add(hand.get(i).charAt(1));
        }
        if (set.size() == 2) return false;
        Set<Integer> set3 = new HashSet<>();
        for (int i=0;i<3;i++) {
            set3.add(hand.get(i).length());
        }
        return set3.size()!=2;
    }

    public static void main(String[] args){
        CardGame2 cg = new CardGame2();
        List<String> res = cg.run("-A -B -BB +C -C -CC =CCC");
        for (String s: res) {
            System.out.println(s);
        }
    }

}
