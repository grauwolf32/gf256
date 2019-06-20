#include <iostream>
#include <string>
#include "gf256.h"

using namespace std;
typedef long long int32;

int32 add_poly(int32 a, int32 b){
    return a ^ b;
}
int32 sub_poly(int32 a, int32 b){
    return a ^ b;
}

int32 mul_poly(int32 a, int32 b){
    int32 res = 0;
    int32 ptr = 1;
    int32 pos = 0;

    while(ptr <= b){
        if(b & ptr){
            res ^= (a << pos);
        }
        ptr <<= 1;
        pos +=  1;
    }
    return res;
}

int32 find_pos(int32 a){
    int32 tmp = 31;
    while(!(a & 1 << tmp) && tmp > 0) tmp--;
    return tmp;
}

void div_poly(int32 a, int32 b, int32& res, int32& rem){
    assert(b != 0);
    
    if(a == 0){ res = 0; rem = 0; return; }

    int32 a_pos = find_pos(a);
    int32 b_pos = find_pos(b);

    int32 c = a;
    int32   tmp;

    if(a_pos < b_pos){ res = 0; rem = a; return; }
    
    res = 0;
    while(a_pos >= b_pos){
        c ^= b << (a_pos - b_pos);
        res ^= 1 << (a_pos - b_pos);
        a_pos = find_pos(c);

        if(!(c & 1 << a_pos)) break;
    }

    rem = c;
    return;
}

void gcd_poly(int32 a, int32 b, int32& gcd, int32& s, int32& t){
    int32 s_curr = 0, s_last = 1, s_next;
    int32 t_curr = 1, t_last = 0, t_next;
    int32 r_curr = a > b ? b:a, r_last = a > b ? a:b, r_next;

    int32 q;
    div_poly(r_last, r_curr, q, r_next);

    while(r_next){
        s_next = mul_poly(q, s_curr) ^ s_last;
        t_next = mul_poly(q, t_curr) ^ t_last;

        r_last = r_curr;
        r_curr = r_next;

        s_last = s_curr;
        s_curr = s_next;

        t_last = t_curr;
        t_curr = t_next;

        div_poly(r_last, r_curr, q, r_next);
    }
    gcd = r_curr;
    s = s_curr; 
    t = t_curr;
    
    return;
}

int32 ff_poly(int32 a, int32 irr_poly){
    int32 res, rem;
    div_poly(a, irr_poly, res, rem);

    return rem;
}

int32 ffmul_poly(int32 a, int32 b, int32 irr_poly){
    int32 res = mul_poly(a, b);
    return ff_poly(res, irr_poly);
}

int32 ffinv_poly(int32 a, int32 irr_poly){
    int32 gcd, s, t;
    gcd_poly(a, irr_poly, gcd, s, t);
    assert(gcd == 1);

    return t;
}

int32 ffadd_poly(int32 a, int32 b, int32 irr_poly){
    int32 res = a ^ b;
    return ff_poly(res, irr_poly);
}

/*
int main(void){
    tests();
    create_tables();

    return 0;
}
*/