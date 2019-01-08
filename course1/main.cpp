#include <iostream>
using namespace std;

/* 存储源文件字母次数的数组 */
int Num[26];
/* 存储加密字母次数的数组 */
int EncryNum[26];
/* k1 密钥一 */
int key1 = 2;
/* k2 密钥二 key2 与 m 互质*/
int key2 = 3;
/* key2 密钥二的乘法逆元 */
int k2;

/*
 * 扩展欧几里得算法求乘法逆元
 * @name inv
 * @param a 被求数
 * @param p 模数
 */
void exgcd(int a,int b,int& d,int& x,int& y){
    if(!b) {
        d = a;
        x = 1;
        y = 0;
    }
    else {
        exgcd(b, a%b, d, y, x);
        y -= x*(a/b);
    }
}
int inv(int a, int p){
    int d,x,y;
    exgcd(a,p,d,x,y);
    return d == 1 ? (x+p)%p : -1;
}

/*
 * 初始化
 * @return void
 */
void init(){
    k2 = inv(key2,26);
    for (int i = 0; i < 26; ++i) {
        EncryNum[i] = 0;
    }
}

/*
 * 仿射加密
 * @param m 明文
 * @return c 密文
 */
char encrypt(char m){
    char c;
    //需要加上97转为ascii码
    if (m > 'Z')
        c = (char)((key1 + key2 * ((int)m - 97) ) % 26 + 97) ;
    else
        c = (char)((key1 + key2 * ((int)m - 65) ) % 26 + 65) ;
    return c;
}

/*
 * 解密
 * @param c 密文
 * @return m 明文
 */
char decrypt(char c){
    char m;
    int padding;
    if (c > 'Z')
        padding = 97;
    else
        padding = 65;
    int tmp = (k2 * ((int)c - padding - key1)) % 26;
    if (tmp < 0)
        tmp = 26 + tmp;
    m = (char)(tmp + padding);
    return m;
}

/*
 * 检查输入是否在加密范围之内
 * @param ch 待检测字母
 * @return ans 输出是否合格
 */
bool CheckLetter(char ch){
    if (ch < 'Z' && ch > 'A')
        return true;
    if (ch < 'z' && ch > 'a')
        return true;
    return false;
}

/*
 * 打印字母频率
 * @return void
 */
void PrintCount(){
    cout << "Source file's letter frequency:" << endl;
    for (int i = 0; i < 26; ++i) {
        cout << (char)(i + 97) << ":" << Num[i] << "  ";
    }
    cout << endl << "Outfile's letter frequency:" << endl;
    for (int i = 0; i < 26; ++i) {
        cout << (char)(i + 97) << ":" << EncryNum[i] << "  ";
    }
}

/*
 * 加密文件
 * @param infile 待加密的文件
 * @param outfile 输出已加密的文件
 */
void encryptFile(FILE* infile, FILE* outfile){
    char ch,c;
    int tmp1,tmp2;
    while( (ch = getc(infile)) != EOF) {
        if (CheckLetter(ch)){
            tmp1 = (int)tolower(ch) - 97;
            Num[tmp1]++;
            c = encrypt(ch);
            tmp2 = (int)tolower(c) - 97;
            EncryNum[tmp2]++;
            putc(c,outfile);
        }
        putc(ch,outfile);
    }
    cout << "Finished!" << endl;
    PrintCount();
}

/*
 * 加密文件
 * @param infile 待解密的文件
 * @param outfile 输出已解密的文件
 */
void decryptFile(FILE* infile, FILE* outfile){
    char ch,c;
    int tmp1,tmp2;
    while( (ch = getc(infile)) != EOF) {
        if (CheckLetter(ch)){
            tmp1 = (int)tolower(ch) - 97;
            Num[tmp1]++;
            c = decrypt(ch);
            tmp2 = (int)tolower(c) - 97;
            EncryNum[tmp2]++;
            putc(c,outfile);
        }
        putc(ch,outfile);
    }
    cout << "Finished!" << endl;
    PrintCount();
}

int main() {
    FILE *infile;
    FILE *outfile;
    infile = fopen("input.txt","r");
    outfile = fopen("output.txt","w");
    if (infile == NULL|| outfile == NULL){
        cout << "fail to open file" << endl;
        return 0;
    }
    encryptFile(infile,outfile);
    fclose(infile);
    fclose(outfile);
    return 0;
}