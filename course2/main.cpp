#include <iostream>
#include <bitset>
#include <cstring>
#include <cstdlib>
using namespace std;

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
 * 将char直接转换成int，0-10之内
 * @param a 要转换的char
 * @return b 转换的字符
 */
char ToInt(char a){
    int b = a - '0';
    return b;
}

/*
 * 随机产生一个01序列串
 * @param length 序列串的长度
 * @return str 产生的01序列串
 */
string GenString(int length){
    string str;
    int n;
    for (int i = 0; i < length; ++i) {
        n = rand() % 2;
        str.push_back(ToChar(n));
    }
    return str;
}

/*
 * 加密函数
 * @param m 明文
 * @param key 密钥
 * @return c 密文
 */
string Encrypt(string m,string key){
    string c;
    char ch;
    for (int i = 0; i < m.length(); ++i) {
        ch = ToChar( ToInt(m[i]) ^ ToInt(key[i]) );
        c.push_back(ch);
    }
    return c;
}

int main() {
    bitset<5> key(25);
    bitset<5> key_bak(25);
    string result;
    cout << "Init statement:" << key.to_string() << endl;
    do{
        int j = key[3] ^ key[0];
        result.push_back(ToChar(j));
        key.operator>>=(1);
        key[4] = j;
    } while (key_bak.to_string() != key.to_string());
    cout << "Output sequence:" << result << endl;
    cout << "Output sequence cycle : " << result.length() << endl;
    string str = GenString(result.length());
    string c = Encrypt(str, result);
    cout << "The result of encrypt \"" << str << "\" is  " << c << endl;
    c = Encrypt(c, result);
    cout << "The result of decrypt is  " << c;
    return 0;
}