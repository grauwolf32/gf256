#ifndef __GF256_H__
#define __GF256_H__

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

typedef long long int32;

int32 add_poly(int32 a, int32 b);
int32 sub_poly(int32 a, int32 b);
int32 mul_poly(int32 a, int32 b);
int32 find_pos(int32 a);
void div_poly(int32 a, int32 b, int32& res, int32& rem);
void gcd_poly(int32 a, int32 b, int32& gcd, int32& s, int32& t);
int32 ff_poly(int32 a, int32 irr_poly);
int32 ffmul_poly(int32 a, int32 b, int32 irr_poly);
int32 ffinv_poly(int32 a, int32 irr_poly);
int32 ffadd_poly(int32 a, int32 b, int32 irr_poly);

#endif