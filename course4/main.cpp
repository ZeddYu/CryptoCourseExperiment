#include <iostream>
#include <cstring>
#include <cmath>
#include "ExEuclid.h"
#include "Miller.h"
#include "QuickPow.h"
#include "RSA.h"
using namespace std;

void PrintHelp(){
    for (int i = 0; i < 64; ++i) {
        cout << "*";
    }
    cout << endl;
}

void Task1(){
    PrintHelp();
    //底数
    int base = 7;
    //模数
    int modules = 5;

    int ans = ExEuclid(base,modules);
    cout << "Base is " << base << ", Modules is " << modules << "" <<endl;
    cout << "The answer is: " << ans << endl;
    PrintHelp();
}

void Task2(){
    int num = 1049;
    if (Miller(num))
        cout << num << " is prime" << endl;
    else
        cout << num << " is not prime" << endl;
    PrintHelp();
}

void Task3(){
    cout << "Cal \"pow(7,563) mod 561 \" : " << QuickPow(7,563,561) << endl;
    PrintHelp();
}

void Task5(){
//    string Table[27] = {"00","01","02","03","04","05","06","07","08","09","10","11",
//                        "12","13","14","15","16","17","18","19","20","21","22","23",
//                        "24","25","26"};
    string m = "I LOVE NANJING UNIVERSITY OF AERONAUTICS AND ASTRONAUTICS";
    string c = "";

    int e = 0, d = 0, p = 0, q = 0;
    GenKey(p,q,e,d);

    p = 19;
    q = 229;
    e = 5;
    d = 821;

    cout << "p is " << p << endl;
    cout << "q is " << q << endl;
    cout << "e is " << e << endl;
    cout << "d is " << d << endl;

    for (int i = 0; i < m.length(); i=i+2) {
        if (i+1 < m.length()){
            string strm = m.substr(i,2);
            int im = 0;
            if (strm[0] == ' ' && strm[1] != ' ' ){
                im = strm[1] - 'A' + 1;
            }
            if (strm[1] == ' ' && strm[0] != ' ' ){
                im = (strm[0] - 'A' + 1) * 100;
            }
            if (strm[0] != ' ' &&  strm[1] != ' ')
                im = (strm[0] - 'A' + 1) * 100 + (strm[1] - 'A' + 1);
            c += RSAEncrypt(im,e,p*q);
        } else{
            string strm = m.substr(i,1);
            int im =0;
            if (strm[0] != ' ')
                im = (strm[0] - 'A' + 1) * -1;
            else
                im = 0;
            c += RSAEncrypt(im,e,p*q);
        }
    }
    cout << c << endl;
}

void Task6(){
    int e = 0, d = 0, p = 0, q = 0;
    GenKey(p,q,e,d);

    p = 19;
    q = 229;
    e = 5;
    d = 821;


    cout << "p is " << p << endl;
    cout << "q is " << q << endl;
    cout << "e is " << e << endl;
    cout << "d is " << d << endl;

    string c = "0011010001010000000010011000011100000100100101010010011001010001000001010101000100010111100000000000010000111000001010000110001100110100011100110000010010010101010000000011100001000010001100000001001000100011001010000111100000000000000000010000100101011001001010010101100101000000100101100011100110000001001101111000001100000000000000010011011110000111000000000000000100100111000110000000011000110000001100100000001000010100000100110010010000110101001110000000";
    string m = "";

    for (int i = 0; i < c.length(); i=i+16) {
        if (i+16 < c.length()){
            string strm = c.substr(i,16);
            int ic = 0;
            for (int j = 0; j < 16; j=j+4) {
                string tmp = strm.substr(j,4);
                ic += BinStr2Int(tmp) * pow(10,((16-j)/4 - 1));
            }
            m += RSADecrypt(ic,d,p*q);
        } else{
            string strm = c.substr(i,c.length() - i);
            int ic = 0;
            for (int j = 0; j < 12; j = j+4) {
                string tmp = strm.substr(j,4);
                ic += BinStr2Int(tmp) * pow(10,((12-j)/4 - 1));
            }
            strm = RSADecrypt(ic,d,p*q);
            m += strm[1];
        }
    }
    cout << m << endl;
}


int main(){
//    Task1();
//    Task2();
//    Task3();
//    Task5();
//    Task6();
}
