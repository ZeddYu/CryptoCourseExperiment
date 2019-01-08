#include<iostream>
#include<vector>
#include<string>
#include "sha1.h"
#include <NTL/ZZ.h>
#include <cmath>

using namespace std;
using namespace NTL;

//Got N = 160
//Got L = 512
//P: 41188750937431246233317001358302257486434525058419432359151975265864031707498855296132396084150410716436625109861613952645308860315137142764964918816263796700681163
//Q: 894028168452526229103549871319779399232066507237

ZZ p,q,g,h,x,y;

ZZ GetH(string msg){
    char ch[57];
    sha1(msg,ch);
    string str = "";
    for (int i = 0; i < 40; ++i) {
        str.push_back(ch[i]);
    }
    ZZ H(0);
    for (int i = 0; i < 40; ++i) {
        if (str[i] < 'z' && str[i] > 'a')
            H += (str[i] - 'a' + 10) * power(ZZ(16),i);
        else
            H += (str[i] - '0') * power(ZZ(16),i);
    }
    return H;
}

ZZ GetS(ZZ k, string msg, ZZ r){
    ZZ k_1 = InvMod(k,q);
    ZZ H = GetH(msg);
    ZZ S = (k_1 * (H + x * r)) % q;
    return S;
}

void GenKey(){
    ZZ index = (p-1)/q;
    h= 35;
    g = PowerMod(h,index,p);
    x = 232066507237;
    y = PowerMod(g,x,p);
}

void Signature(ZZ k, string msg, ZZ &r, ZZ &s){
    GenKey();
    r = PowerMod(g,k,p) % q;
    s = GetS(k,msg,r);
    cout << "Signature is {" << r << ", " << s <<"}" << endl;
}

void Verify(ZZ r, ZZ s, string msg){
    ZZ w = InvMod(s,q) % q;
    ZZ u1 = (GetH(msg) * w) % q;
    ZZ u2 = (r * w) %q;
    ZZ temp = (PowerMod(g,u1,p) * PowerMod(y,u2,p)) % p;
    ZZ r1 = temp % q;
    cout << "Verify r is :" << r1 << endl;
    if (r == r1)
        cout << "Congratulations! Confirm!" << endl;
    else
        cout << "Oh! No!" << endl;
}


int main(){
    cout << "p: ";
    cin >> p;

    cout << "q: ";
    cin >> q;

    string msg = "";
    cout << "msg: ";
    cin >> msg;
    ZZ k(21);
    ZZ r(0);
    ZZ s(0);
    Signature(k,msg,r,s);
    Verify(r,s,msg);

}