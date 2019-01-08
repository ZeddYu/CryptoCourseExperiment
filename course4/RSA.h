//
// Created by Zedd on 2019/1/7.
//

#ifndef COURSE4_RSA_H
#define COURSE4_RSA_H

#include <bitset>
#include "RSA.h"
#include "ExEuclid.h"
#include "QuickPow.h"
#include <sstream>
using namespace std;

int BinStr2Int(string str);

/*
 * 辗转相除求最大公因子
 * @param a
 * @param b
 */
int gcd(int a,int b);

/*
 * 欧拉函数
 * @param p
 * @param q
 */
int Euler(int p, int q);

/*
 * 生成私钥公钥
 * @param p
 * @param q
 * @param e 公钥{e,n}
 * @param d 私钥{d,n}
 */
void GenKey(int &p, int &q, int &e, int &d);

/*
 * 将字符串转换成二进制字符串
 * @param str 需要转换的字符串
 * @return ans 二进制字符串
 */
string String2Bin(string str);

/*
 * 将二进制字符串转换成ascii字符串
 * @param str 二进制字符串
 * @return ans ascii字符串
 */
string Bin2String(string str);

/*
 * 将二进制字符串转换成int
 * @param str 二进制字符串
 * @return ans int整形
 */
int BinStr2Int(string str);

/*
 * 将int直接转换成char，0-10之内
 * @param a 要转换的int
 * @return b 转换的字符
 */
char ToChar(int a);

/*
 * 将十进制转换为二进制字符串
 * @param a 十进制数
 * @return ans 字符串
 */
string Int2Bin(int a);

/*
 * RSA加密
 * @param m 明文
 * @param c 密文
 * @param e
 * @param n
 * @return void
 */
string RSAEncrypt(int im, int e, int n);

/*
 * RSA解密
 * @param c 密文
 * @param m 明文
 * @param d
 * @param n
 * @return void
 */
string RSADecrypt(int ic, int d, int n);

#endif //COURSE4_RSA_H
