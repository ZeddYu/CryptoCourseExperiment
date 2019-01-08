//
// Created by Zedd on 2019/1/7.
//
#include <cstdlib>
#include <cmath>
#include "Miller.h"

/*
 * calculates (a * b) % c taking into account that a * b might overflow
 */

ll mulmod(ll a, ll b, ll mod){
    ll x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

/*
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod){
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(ll n,int iteration){
    if(n < 2)
        return false;
    else if(n == 2)
        return true;

    long long q = 0, m = n - 1;
    while(m % 2 == 0) {
        m /= 2;
        ++q;
    }

    long long a = rand()%(n-2)+2;
    long long x1 = (long long)pow(a, m) % n, x2;

    for(int i = 1; i <= q; ++i) {
        x2 = (x1*x1) % n;
        if(x2 == 1 && x1 != 1 && x1 != n-1)
            return false;
        x1 = x2;
    }

    if( x2 != 1)
        return false;
    else
        return true;
}