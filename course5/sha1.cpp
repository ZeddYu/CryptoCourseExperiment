//
// Created by Zedd on 2019/1/8.
//

#include "sha1.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

vector<int> X;  // 8*64=512，每个下标存放8位
int W[80];  //32位为一组
int A, B, C, D, E;
int A1, B1, C1, D1, E1;//缓冲区寄存器,产生最后结果
int Turn;//加密分组数量N
using namespace std;

/**
 *  循环左移
 *  @param x 待循环数
 *  @param n 移动位数
 *  @return 循环结果
 */
int LeftShift(unsigned int x, int n){
    return x >> (32 - n) | (x << n);
}

void printX() {//输出填充后的文本
    for (int i = 0; i < X.size(); i++) {
        printf("%02x", X[i]);
        if ((i + 1) % 4 == 0)
            printf(" ");
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}

/**
 *  产生M数组
 *  文本的填充处理
 */
void append(string m){
    Turn = m.size() / 64 + 1;
    X.resize(Turn * 64);

    //原文直接赋值
    int i = 0;
    for (; i < m.size(); i++){
        X[i] = m[i];
    }

    //填充1
    X[i++] = 0x80;
    while (i < X.size() - 8){
        X[i] = 0;
        i++;
    }
    //最后 64位表示 m的长度
    long long int a = m.size() * 8;
    for (i = X.size() - 1; i >= X.size() - 8; i--) {
        X[i] = a % 256;
        a /= 256;
    }
}

/**
 * X数组的生成
 *
 */

void setW(vector<int> m, int n){
    //16 * 4
    n *= 64;
    for (int j = 0; j < 16; j++) {
        W[j] = (m[n + 4 * j] << 24) + (m[n + 4 * j + 1] << 16) + (m[n + 4 * j + 2] << 8) + m[n + 4 * j + 3];
    }
    for (int j = 16; j < 80; j++) {
        W[j] = LeftShift(W[j - 16] ^ W[j - 14] ^ W[j - 8] ^ W[j - 3], 1);
    }
}

/**
 * fi函数
 * @param t 次数
 */

int ft(int t) {
    //f1
    if (t < 20)
        return (B & C) | ((~B) & D);
    //f2
    else if (t < 40)
        return B ^ C ^ D;
    //f3
    else if (t < 60)
        return (B & C) | (B & D) | (C & D);
    //f4
    else
        return B ^ C ^ D;
}

/**
 * 返回Ki常数
 * @param t 次数
 * @return Ki常数
 */
int Kt(int t) {
    if (t < 20)
        return 0x5a827999;
    else if (t < 40)
        return 0x6ed9eba1;
    else if (t < 60)
        return 0x8f1bbcdc;
    else
        return 0xca62c1d6;
}

/**
 * sha1算法接口
 * @param t 次数
 * @param ch 字符数组
 */
void sha1(string text, char *ch) {
    A1 = A = 0x67452301;
    B1 = B = 0xefcdab89;
    C1 = C = 0x98badcfe;
    D1 = D = 0x10325476;
    E1 = E = 0xc3d2e1f0;
    append(text);
//    printX();
//    for(int i= 0;i < 64;i++){
//        printf("%x",X[i]);
//    }
    for (int i = 0; i < Turn; i++) {
        setW(X, i);
        for (int t = 0; t < 80; t++) {
            int temp = E + ft(t) + LeftShift(A, 5) + W[t] + Kt(t);
            E = D;
            D = C;
            C = LeftShift(B, 30);
            B = A;
            A = temp;
        }
        A1 = A = A + A1;
        B1 = B = B + B1;
        C1 = C = C + C1;
        D1 = D = D + D1;
        E1 = E = E + E1;
    }
    printf("%x%x%x%x%x\n", A1, B1, C1, D1, E1);
    sprintf(ch,"%x%x%x%x%x", A1, B1, C1, D1, E1);
}