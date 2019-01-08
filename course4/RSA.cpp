//
// Created by Zedd on 2019/1/7.
//

#include <bitset>
#include "RSA.h"
#include "ExEuclid.h"
#include "QuickPow.h"
#include <sstream>
#include <iostream>

using namespace std;

/*
 * 300以内素数表
 */
int primeTable []= {
        2,3,5,7,11,13,17,19,23,29,
        31,37,41,43,47,53,59,61,67,71,
        73,79,83,89,97,101,103,107,109,113,
        127,131,137,139,149,151,157,163,167,173,
        179,181,191,193,197,199,211,223,227,229,
        233,239,241,251,257,263,269,271,277,281
};

/*
 * 随机产生素数
 */
int GenPrime(){
    return primeTable[ rand() % 50 ];
}

/*
 * 辗转相除求最大公因子
 * @param a
 * @param b
 */
int gcd(int a,int b) {
    int r;
    while(b > 0){
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/*
 * 欧拉函数
 * @param p
 * @param q
 */
int Euler(int p, int q){
    return (p-1)*(q-1);
}

/*
 * 生成私钥公钥
 * @param p
 * @param q
 * @param e 公钥{e,n}
 * @param d 私钥{d,n}
 */
void GenKey(int &p, int &q, int &e, int &d){
    p = GenPrime();
    q = GenPrime();
    int eul = Euler(p,q);
    for (int i = 2; i < eul; ++i) {
        if(gcd(eul, i) == 1) {
            e = i;
            break;
        }
    }
    d = ExEuclid(e,eul);
}

/*
 * 将字符串转换成二进制字符串
 * @param str 需要转换的字符串
 * @return ans 二进制字符串
 */
string String2Bin(string str){
    string ans;
    for (int i = 0; i < str.size(); ++i) {
        ans += bitset<4>(str[i]).to_string();
    }
    return ans;
}

/*
 * 将二进制字符串转换成ascii字符串
 * @param str 二进制字符串
 * @return ans ascii字符串
 */
string Bin2String(string str){
    stringstream sstream(str);
    string output;
    while(sstream.good())
    {
        std::bitset<4> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }
    return output;
}

/*
 * 将二进制字符串转换成int
 * @param str 二进制字符串
 * @return ans int整形
 */
int BinStr2Int(string str){
    bitset<4> bit(str);
    return static_cast<int>(bit.to_ulong());
}

/*
 * 将int直接转换成char，0-10之内
 * @param a 要转换的int
 * @return b 转换的字符
 */
char ToChar(int a){
    char b;
    b = '0' + a;
    return b;
}

/*
 * 将十进制转换为二进制字符串
 * @param a 十进制数
 * @return ans 字符串
 */
string Int2Bin(int a){
    string str("0000");
    for (int i = 0; i < 4; ++i) {
        str[i] = ToChar(a%2);
        a /= 2;
    }
    string ans(str.rbegin(),str.rend());
    return ans;
}

/*
 * RSA加密
 * @param m 明文
 * @param e
 * @param n
 * @return c 密文
 */
string RSAEncrypt(int im, int e, int n){
    if (im < 0){
        im = im * -1;
        int ic = static_cast<int>(QuickPow(im, e, n));
        return String2Bin(to_string(ic));
    }
    int ic = static_cast<int>(QuickPow(im, e, n));
    string strc = "";
    if (ic < 10)
        strc = "000" + to_string(ic);
    else if (ic < 100)
        strc = "00" + to_string(ic);
    else if (ic < 1000)
        strc = "0" + to_string(ic);
    else
        strc = to_string(ic);
    string res = String2Bin(strc);
    return res;
}

/*
 * RSA解密
 * @param c 密文
 * @param d
 * @param n
 * @return m 明文
 */
string RSADecrypt(int ic, int d, int n){
    int im = static_cast<int>(QuickPow(ic, d, n));
    char im1 = (char) (im / 100 + 'A' - 1);
    char im2 = (char) (im % 100 + 'A' - 1);
    string res = "";
    if (im1 == '@')
        im1 = ' ';
    if (im2 == '@')
        im2 = ' ';
    res.push_back(im1);
    res.push_back(im2);
    return res;
}