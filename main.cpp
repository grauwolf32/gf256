#include <iostream>
#include <ctime>

#include "gf256.h"
#include "gf256_tables.c"

using namespace std;

class GF256
{
	public:
		GF256(int num) {n = num;}
		GF256 operator+(const GF256& rhs) { return GF256(add_table[n][rhs.n]); }
		GF256 operator-(const GF256& rhs) { return GF256(add_table[n][rhs.n]); }
		GF256 operator*(const GF256& rhs) { return GF256(mul_table[n][rhs.n]); }
		GF256 operator/(const GF256& rhs) { 
											int res = add_table[n][rhs.n]; 
											assert(res != -1);
											return GF256(res);
										  }

		friend ostream& operator<<(ostream& os, const GF256& n);
		int n;

	private:
		static const int irr_poly = 285; // 1 + x^2 + x^3 + x^4 + x^8
};

ostream& operator<<(ostream& os, const GF256& n)
{
    os << n.n;
    return os;
}

void benchmark()
{
	clock_t t1, t2;
	int32 irr_poly = 285;  // 1 + x^2 + x^3 + x^4 + x^8 

	t1 = clock();
	for(int e = 0; e < 100; e++){
		for(int i = 0; i < 256; i++){
        	for(int j = 0; j < 256; j++){
            	ffadd_poly(i, j, irr_poly);
            	ffmul_poly(i, j, irr_poly);
        	}
    	}

    	for(int i = 0; i < 256; i++){
        	for(int j = 1; j < 256; j++){
            	ffmul_poly(i, ffinv_poly(j, irr_poly), irr_poly);
        	}
    	}
	}
	t2 = clock();
	cout << "Calculation time: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl;

	t1 = clock();
	for(int e = 0; e < 100; e++){
		for(int i = 0; i < 256; i++){
        	for(int j = 0; j < 256; j++){
            	GF256(i) + GF256(j);
            	GF256(i) * GF256(j);
        	}
    	}

    	for(int i = 0; i < 256; i++){
        	for(int j = 1; j < 256; j++){
            	GF256(i) / GF256(j);
        	}
    	}
	}
	t2 = clock();
	cout << "Lookup time: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl;
}

void tests(){
    cout << "mul_poly(5, 5): " << mul_poly(5, 5) << endl;
    cout << "mul_poly(37, 32): " << mul_poly(37, 32) << endl;
    cout << "mul_poly(31, 48): " << mul_poly(31, 48) << endl;
    cout << "mul_poly(0, 5): " << mul_poly(0, 5) << endl;
    cout << "mul_poly(1, 1): " << mul_poly(1, 1) << endl;

    cout << "find_pos(5): "  << find_pos(5) << endl;
    cout << "find_pos(32): " << find_pos(32) << endl;
    cout << "find_pos(0): " << find_pos(0) << endl;

    int32 rem, res;
    div_poly(25, 5, res, rem);
    cout << "div_poly(25, 5, res, rem) " << "res: " << res << " rem: " << rem << endl;
    
    div_poly(37, 19, res, rem);
    cout << "div_poly(37, 19, res, rem) " << "res: " << res << " rem: " << rem << endl;

    div_poly(37, 1, res, rem);
    cout << "div_poly(37, 1, res, rem) " << "res: " << res << " rem: " << rem << endl;

    int32 gcd, s, t;
    gcd_poly(11, 5, gcd, s, t);
    cout << "gcd_poly(11, 5, gcd, s, t) " << "gcd: " << gcd << " s: " << s << " t: " << t << endl;

    gcd_poly(17, 8, gcd, s, t);
    cout << "gcd_poly(17, 8, gcd, s, t) " << "gcd: " << gcd << " s: " << s << " t: " << t << endl;

    gcd_poly(18, 6, gcd, s, t);
    cout << "gcd_poly(18, 6, gcd, s, t) " << "gcd: " << gcd << " s: " << s << " t: " << t << endl;

    int32 irr_poly = 285; // 1 + x^2 + x^3 + x^4 + x^8 
    cout << "ffinv_poly(121, irr_poly): " << ffinv_poly(121, irr_poly) << endl;
    cout << "ffadd_poly(121, 12, irr_poly): " << ffadd_poly(121, 12, irr_poly) << endl;
}

int main(void)
{
	//tests();
	benchmark();
	return 0;
}