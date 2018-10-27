//
// Created by henry on 10/27/18.
//

#ifndef PNSEI_BITTORRENT_MERGE_H
#define PNSEI_BITTORRENT_MERGE_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=273407
1. id allocation/deallocation 先實作了queue的做法, 然後是bit array, 問是否有time/space complexity在兩個之間的方法。最後作了binary tree (each node stores whether there's any available ids in its subtrees) 有寫完，面試官很滿意
2. download bit-torrent. 第一題基本上就是merge intervals。後來是interval連續進入，寫了一個binary search找位置然後linear update. 寫完後考慮要問演算法(猜測是用樹來解這題)或是system，選了system.結果問如果真的download這些paritial file後要怎麼merge real files
3. Sharpness value. 一開始以為是新題，說要在一個image中找最像地平線的一條線。DP解。問如果圖太大怎麼處理，問各種讀法的disk access次數。期待的答案好像是把各種讀法的disk access次數寫成一個function然後找到最佳解
4. Behavior
5. Project deep dive
6. 照片每次被view就會call View(photo id), 給top-k view photo. 一開始假設有整個oracle, 用heap解決。延伸如果view是一個個來，寫了一個很複雜的heap + hashmap。期待的最佳解應該是bucket sort
 *
 * */

#endif //PNSEI_BITTORRENT_MERGE_H
