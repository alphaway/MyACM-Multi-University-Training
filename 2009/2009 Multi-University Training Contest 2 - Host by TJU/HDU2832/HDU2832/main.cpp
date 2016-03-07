//
//  main.cpp
//  HDU2832
//
//  Created by beMaster on 16/3/7.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
/*
 有一段100cm的橡皮筋
 蜗牛每分钟爬kcm， 爬完后橡皮筋的长度增加100cm，但是蜗牛所在的位置距离两端的比例不变
那只要按照比例来走就好了
 第一次走了k/100,第二次k/200
 问几分钟爬完
 */
int main(int argc, const char * argv[]) {
    int k;
    while(scanf("%d",&k)!=EOF){
        int t = 0;
        double tmp = 0;
        double s = 100;
        while(tmp<1){
            tmp += k/s;
            t++;
            s += 100;
        }
        printf("%d\n",t);
    }
    return 0;
}
