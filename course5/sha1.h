//
// Created by Zedd on 2019/1/8.
//

#ifndef COURSE5_SHA1_H
#define COURSE5_SHA1_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int LeftShift(unsigned int x, int n);

void append(string m);

void setW(vector<int> m, int n);

int ft(int t);

int Kt(int t);

void sha1(string text,char *ch);


#endif //COURSE5_SHA1_H
