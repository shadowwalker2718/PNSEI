package practice.instacart;

/*
https://www.1point3acres.com/bbs/thread-615124-1-1.html
这题其实就是All susbset with k size的做法，用DFS在给的一堆牌里找size为3的的牌，每找到一手牌，就调helper函数validate
这手牌是不是符合对prefix，type of letter 和number of type of letter的要求。符合就立即停止搜索，返回找到的第一副牌。

K-combination
http://sde.quant365.com/combinatorics.html#combination-dfs
* */

import java.util.*;

public class CardGame {

    public List<String> getOneWinning(String s){
        Scanner sc = new Scanner(s);
        sc.useDelimiter(" ");
        List<String> cards = new ArrayList<>();
        while(sc.hasNext()){
            String n = sc.next();
            cards.add(n);
        }
        List<String> hand = new ArrayList<>();
        if (findOneWinningHand(cards, 0, hand)){
            System.out.println("found one winning hand");
        }
        return hand;
    }

    public Set<List<String>> getAllWinning(String s){
        Scanner sc = new Scanner(s);
        sc.useDelimiter(" ");
        List<String> cards = new ArrayList<>();
        while(sc.hasNext()){
            String n = sc.next();
            cards.add(n);
        }
        List<String> hand = new ArrayList<>();
        Set<List<String>> res = new HashSet<>();
        findWinningHands(res, cards, 0, hand);
        return res;
    }

    boolean findOneWinningHand(List<String> cards, int k, List<String> hand){
        if (hand.size()==3){
            return isValid(hand);
        }
        while(k<cards.size()) {
            hand.add(cards.get(k));
            if (findOneWinningHand(cards, k+1, hand)){
                return true;
            } else{
                hand.remove(hand.size()-1);
            }
            k++;
        }
        return false;
    }

    void findWinningHands(Set<List<String>> res, List<String> cards, int k, List<String> hand){
        if (hand.size()==3){
            if(isValid(hand))
                res.add(new ArrayList<>(hand));
            return;
        }
        while(k<cards.size()) {
            hand.add(cards.get(k));
            findWinningHands(res, cards, k+1, hand);
            hand.remove(hand.size()-1);
            k++;
        }
    }

    boolean isValid(List<String> hand){
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
        CardGame cg = new CardGame();
        List<String> res = cg.getOneWinning("-A -B -BB +C -C -CC =CCC");
        for (String s: res) {
            System.out.println(s);
        }

        Set<List<String>> all = cg.getAllWinning("-A -B -BB +C -C -CC =CCC");
        assert all.size() == 2 : "error";
    }

}
