//
// Created by Zedd on 2019/1/7.
//

#include "QuickPow.h"


/*
 * 快速幂运算
 * @param x 底数
 * @param n 指数
 * @param m 模数
 * @return res 结果
 */
ll QuickPow(ll x,ll n,ll m){
    ll res = 1;
    while(n > 0){
        if(n & 1)	res = res * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return res;
}