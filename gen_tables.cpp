#include <sstream>
#include <fstream>
#include "gf256.h"

using namespace std;

string table_tostr(int32 table[256][256], const char* name){
    stringstream table_stream;
    table_stream << name << " = " << "{" << endl;

    for(int i = 0; i < 256; i++){
        table_stream << "{ " << table[i][0];
        
        for(int j = 1; j < 256; j++){
          table_stream  << ", " << table[i][j];
        }

        table_stream << " }," << endl;
    }

    table_stream << "};" << endl;

    return table_stream.str();
}

void create_tables(){
    int32 add_table[256][256] = {0};
    int32 mul_table[256][256] = {0};
    int32 div_table[256][256] = {0};

    int32 irr_poly = 285;  // 1 + x^2 + x^3 + x^4 + x^8 

    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++){
            add_table[i][j] = ffadd_poly(i, j, irr_poly);
            mul_table[i][j] = ffmul_poly(i, j, irr_poly);
        }
    }

    for(int i = 0; i < 256; i++){
        div_table[i][0] = -1;
    }

    for(int i = 0; i < 256; i++){
        for(int j = 1; j < 256; j++){
            div_table[i][j] = ffmul_poly(i, ffinv_poly(j, irr_poly), irr_poly);
        }
    }

    string cpp_add = table_tostr(add_table, "long long add_table[256][256]");
    string cpp_mul = table_tostr(mul_table, "long long mul_table[256][256]");
    string cpp_div = table_tostr(div_table, "long long div_table[256][256]");

    ofstream tables("gf256_tables.c");
    tables << cpp_add << endl << cpp_mul << endl << cpp_div << endl;
    tables.close();

    return;
}

int main(void){
    create_tables();
}