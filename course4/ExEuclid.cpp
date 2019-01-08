//
// Created by Zedd on 2019/1/7.
//

#include "ExEuclid.h"

/*
 * 扩展欧几里得算法求乘法逆元
 * @name ExEuclid
 * @param a 被求数
 * @param n 模数
 */
void exgcd(int a,int b,int& d,int& x,int& y){
    if(!b) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        exgcd(b, a%b, d, y, x);
        y = y - x*(a/b);
    }
}
int ExEuclid(int a, int n){
    int d,x,y;
    exgcd(a,n,d,x,y);
    if(d == 1)
        return (x + n) % n;
    else
        return -1;
}