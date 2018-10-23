//
// Created by henry on 10/21/18.
//

#ifndef C_OA_H
#define C_OA_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=447222&ctid=228575
 *
 * Cruise的OA是我做过的最难的，题都是那三道。之前的OA帖子很少，而且光看题目名称其实有误导性啊…求加米求加米啊…-google 1point3acres

[high=200]
抱歉这里积分要稍稍设的高一点。这个OA应该是针对AV岗位的，针对fullstack的是另外五道，地理有。
1. 打印Pascal's triangle。 这个没什么好说的，做一下蠡口原题就知道怎么回事儿了。
2. Encircular 这个是给一串string指令，看看重复本指令会不会绕圈（回到原点）。指令执行过程和蠡口 拔其似 比较像。我的做法是执行这条指令执行四次，如果回到原点，说明这个指令会绕圈。testcast都过了。
3. Strongly connected group。这个并非是geekforgeek上的问题，甚至都不是wiki上strongly connected components的原意。
 这个链接才是本意，[url=https://www.hackerrank.com/challenges/clique/problem [/hide]]https://www.hackerrank.com/challenges/clique/problem[/url]， 个人感觉相当难了…
[/hide]*/


// https://www.careercup.com/question?id=5653668599693312
// https://stackoverflow.com/questions/28967020/check-if-there-exists-a-circle
// https://www.geeksforgeeks.org/check-if-a-given-sequence-of-moves-for-a-robot-is-circular-or-not/
// https://leetcode.com/problems/walking-robot-simulation/description/


/*
1. Each run(one run is executing all commands of the given string once) changes two things:
the direction which the robot looks to and its position(that is, each run shifts it by
some vector(the direction of this vector depends on the its initial direction before
the run) and rotates it).

2. The number of possible directions is 4. Thus, after running the simulation 4 times it
looks in the same direction as it did initially(each run rotates it by the same angle)!!!!
(This point is very important!)

3. That's why 4 consecutive runs just shift it by some vector without any rotation.

4. Thus, we can just run the simulation 4 times in a row and see if it stopped in the
original point. If it did, we can find the minimum circle that contains its path.
Otherwise, no such circle exists.
 * */


/*
second (North)
^
|
|
|----------------------------> first (East)
 */
/* Java *
static class Pair{
  int first;
  int second;
  public Pair(int f, int s){
    first = f;
    second = s;
  }
}
static String doesCircleExist(String commands) {
  if(commands.length() == 0 || commands == null) return "";
  int dir=1; //1 is east; 2 north; 3 west, 4 south
  Pair pos;
  pos = new Pair(0,0);  //start at origin
  for(int i=0;i<4;i++) {
    for(int j=0;j<commands.length(); j++){
      if(commands.charAt(j)=='G'){
        if(dir==1) pos.first++;  if(dir==2) pos.second++;
        if(dir==3) pos.first--; if(dir==0) pos.second--;
      }
      if(commands.charAt(j)=='L') {dir = (dir+1)%4;}
      else if(commands.charAt(j)=='R') {dir=(dir+4-1)%4;}
    }
  }
  if(pos.first==0 && pos.second==0 && dir==1) return "YES"; else return "NO";
}*/


#endif //C_OA_H
