
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int _and(int a, int b);
int _or(int a, int b);
int _nand(int a, int b);
int _xor(int a, int b);

int main(int argc, const char * argv[]) {
    int  a=0;
    int  b=1;
    
    printf(" a=%x b=%x\n", a, b);
    printf("AND results %x\n", _and(a,b));
    printf("OR results %x\n", _or(a,b));
    printf("NAND results %x\n", _nand(a,b));
    printf("XOR results %x\n", _xor(a,b));

}

int _and(int a, int b) {
    return a==b && a == 1;
}

int _or(int a, int b) {
    return a==1 || b == 1;
}

int _xor(int a, int b) {
    return (_or(a,b)) ? 0 : 1;
}

int _nand(int a, int b) {
    return (_and(a,b)) ? 0 : 1;
}