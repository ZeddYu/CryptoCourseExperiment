//
// Created by Zedd on 2019/1/7.
//
#include <cstdlib>
#include <cmath>
#include "Miller.h"

bool Miller(long long n){
    if(n < 2)
        return false;
    else if(n == 2)
        return true;

    long long s = 0, m = n - 1;
    while(m % 2 == 0) {
        m /= 2;
        ++s;
    }

    long long b = rand() % (n - 2) + 2;
    long long z = (long long)pow(b, m) % n, r = 0;

    if (z == 1 || z == n-1)
        return true;
    for (; r < s - 1; ++r) {
        z = pow(z,2);
        z %= n ;
        if (z == n-1)
            return true;
    }
    if (r == s-1)
        return false;
}