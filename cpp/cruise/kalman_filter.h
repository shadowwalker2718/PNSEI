//
// Created by root on 11/6/18.
//

#ifndef PNSEI_KALMAN_FILTER_H
#define PNSEI_KALMAN_FILTER_H

/* https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=402851&highlight=cruise
 *
 * 2018(4-6月) 码农类General 博士 全职@Cruise - 网上海投 - Onsite  | Fail | 在职跳槽
以下内容需要积分高于 150 您已经可以浏览

职位:Perception(AV)

 店面第一轮:LRU, follow up templated version.
店面第二轮:Range sum 2D（integral image)

 onsite

Kalman filter vs Particle filter when? why.   Property of covariance matrix??
 Design state for vehicle estimation, motion update equation derivation.
 explain the elements of co-variance matrix.

Connected components maxSum(coding), similar to number of island 2.

Behavior. How did you work with your manager, whats the regret in previous job, what's the failure in previous job,
 what did you learn in previous project.

Design poker game. (every player has 5 cards in hand and can choose to replace a certain number of cards with the
 cards in the deck, then compute the scores of each player and find the largest score player among the players).
这家公司挺抠门的,路费只报销30刀,单程打车都不够,自己感觉面得还行不过面完隔了两天就收到拒信了,模板据.
 *
 * */
#include "henry.h"

namespace kalman{

double frand() {
  return 2 * ((rand() / (double)RAND_MAX) - 0.5);//随机噪声
}


void kalman_filter(){
  float x_last = 0;
  float p_last = 0.02;
  float Q = 0.018;
  float R = 0.542;
  float kg;
  float x_mid;
  float x_now; //kalman value
  float p_mid;
  float p_now;
  float z_real = 0.56;
  float z_measure;
  float summerror_kalman = 0;
  float summerror_measure = 0;
  int i;

  x_last = z_real + frand()*0.03;
  x_mid = x_last;
  for (i = 0; i < 20;i++){
    x_mid = x_last;
    p_mid = p_last + Q;
    kg = p_mid / (p_mid + R);
    z_measure = z_real + frand()*0.03;//测量值
    x_now = x_mid + kg*(z_measure - x_mid);//估计出的最有值
    p_now = (1 - kg)*p_mid;//最优值对应的协方差

    printf("Real position:%6.3f\n", z_real);
    printf("Measure position:%6.3f [diff:%.3f]\n", z_measure, fabs(z_real - z_measure));
    printf("Kalman position: %6.3f [diff:%.3f]\n", x_now, fabs(z_real - x_now));
    printf("\n\n");
    summerror_kalman += fabs(z_real - x_now);
    summerror_measure += fabs(z_real - z_measure);
    p_last = p_now;
    x_last = x_now;
  }
  printf("总体测量误差      :%f\n", summerror_measure);
  printf("总体卡尔曼滤波误差:%f\n", summerror_kalman);
  printf("卡尔曼误差所占比例:%d%%\n", 100 - (int)((summerror_kalman / summerror_measure) * 100));


/*  ---------------------
      作者:凡旭国
  来源:CSDN
  原文:https://blog.csdn.net/sinat_20265495/article/details/51006311
  版权声明:本文为博主原创文章,转载请附上博文链接!*/
}

// http://www.nehalemlabs.net/prototype/blog/2013/07/16/an-introduction-to-smoothing-time-series-in-python-part-iv-particle-filter/
// https://github.com/tmramalho/smallParticleFilter
};

#endif //PNSEI_KALMAN_FILTER_H
