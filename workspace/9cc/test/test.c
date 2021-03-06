int g1;
int g2[5];
static int ext1 = 3;
extern int global_var;
char g3 = 3;
int g4 = 5;
int *g5 = &g4;
char *g6 = "abc";
int g7[3] = {0, 1, 2};
char *g8[] = {"foo", "bar"};
struct { char a; int b; } g9[2] = {{1, 2}, {3, 4}};
struct { int a[2]; } g10[2] = {{{1, 2}}};

typedef struct {
    int x;
    int y;
} HogeStruct;

int printf();
int fprintf();
int strcmp(char *p, char *q);
int exit();
int *alloc(int x);
int **alloc2(int x);
int* alloc4(int a, int b, int c, int d);
int*** alloc5(int** pp, int** pq);
void show(char* p);
void show_num(int i);
int assert(int expected, int actual, char *text) {
    if (actual == expected){
        printf("[ok] actual:%d expected: %d %s\n", actual, expected, text);
    } else {
        printf("[ng](expected: %d => but got: %d %s\n", expected, actual, text);
        exit(1);
    }
    return 0;
}

int fuga() {
    return 5;
}

int post_decl(int j) {
    for (int i = 1; i >= 0; i--) {
    }
    return j;
}

int pre_decl(int j) {
    for (int i = 1; i >= 0; --i) {
    }
    return j;
}
#define bool _Bool
bool test_bool(bool a) {
    return a;
}
int hoge() { return 20; }
int add1(int a) { return a; }
int add2(int a, int b) { return a + b; }
int add2_array(int (*a)[2]) { return (*a)[0] + (*a)[1]; }
int add3(int a, int b, int c) { return a + b + c; }
int add4(int a, int b, int c, int d) { return a + b + c + d; }
int add5(int a, int b, int c, int d, int e) { return a + b + c + d + e; }
int add6(int a, int b, int c, int d, int e, int f) { return a + b + c + d + e + f; }
int plus(int x, int y) { return x + y; }
void nop() {}
static int static_fn() { return 3; }

int sub_short(short a, short b, short c) {
    return a - b - c;
}

int sub_long(long a, long b, long c) {
    return a - b- c;
}

bool is_minus_one(int i) {
    return i == -1;
}

int main() {
#include "test/test3.h"
    assert(0, 0, "0");
    assert(42, 42, "42");
    assert(48879, 0xBEEF, "0xBEEF");
    assert(255, 0xff, "0xff");
    assert(493, 0755, "0755");
    assert(0-42, -42, "-42");
    assert(42, (13 + 34 - 5), "(13 + 34 - 5)");
    assert(0, 1 - (4 - 1 - 2), "(4 - 1 - 2)");
    assert(21, 5+20-4, "5+20-4");
    assert(0, ({ 0; }), "({ 0; })");
    assert(42, ({ 42; }), "({ 42; })");
    assert(21,  ({ 5+20-4; }), " ({ 5+20-4; })");
    assert(41,  ({  12 + 34 - 5; }), " ({  12 + 34 - 5; })");
    assert(37,  ({ 5 * 6 + 7; }), " ({ 5 * 6 + 7; })");
    assert(48,  ({ 5 + 6 * 7 + 1; }), " ({ 5 + 6 * 7 + 1; })");
    assert(7,  ({ 5 + 14 / 7; }), " ({ 5 + 14 / 7; })");
    assert(3, 3 % 7, "3 % 7");
    assert(0, 7 % 7, "7 % 7");
    assert(4, 11 % 7, "11 % 7");
    assert(0, 14 % 7, "14 % 7");
    assert(50,  ({ 5 + 6 * 7 + 1 * 3; }), " ({ 5 + 6 * 7 + 1 * 3; })");
    assert(47,  ({ 5 + 6 * 7; }), " ({ 5 + 6 * 7; })");
    assert(47,  ({ 2 + 3 + 6 * 7; }), " ({ 2 + 3 + 6 * 7; })");
    assert(44,  ({ 6 / 3 + 6 * 7; }), " ({ 6 / 3 + 6 * 7; })");
    assert(9,  ({ (1 + 2) * 3; }), " ({ (1 + 2) * 3; })");
    assert(9,  ({ (1 + 2) * 3; }), " ({ (1 + 2) * 3; })");
    assert(1,  ({ 2 == 2; }), " ({ 2 == 2; })");
    assert(0,  ({ 2 == 3; }), " ({ 2 == 3; })");
    assert(0,  ({ 2 != 2; }), " ({ 2 != 2; })");
    assert(1,  ({ 2 != 3; }), " ({ 2 != 3; })");
    assert(1,  ({ 3 >= 2; }), " ({ 3 >= 2; })");
    assert(1,  ({ 2 >= 2; }), " ({ 2 >= 2; })");
    assert(0,  ({ 1 >= 2; }), " ({ 1 >= 2; })");
    assert(0,  ({ 3 <= 2; }), " ({ 3 <= 2; })");
    assert(1,  ({ 2 <= 2; }), " ({ 2 <= 2; })");
    assert(1,  ({ 1 <= 2; }), " ({ 1 <= 2; })");
    assert(1,  ({ 3 > 2; }), " ({ 3 > 2; })");
    assert(0,  ({ 2 > 2; }), " ({ 2 > 2; })");
    assert(0,  ({ 1 > 2; }), " ({ 1 > 2; })");
    assert(0,  ({ 3 < 2; }), " ({ 3 < 2; })");
    assert(0,  ({ 2 < 2; }), " ({ 2 < 2; })");
    assert(1,  ({ 1 < 2; }), " ({ 1 < 2; })");
    assert(5,  ({int a; int b; a = 3;b = 2; a + b; }), " ({int a; int b; a = 3;b = 2; a + b; })");
    assert(25,  ({ int d; int b; d = 3 * 2 - 1;b = 5; d * b; }), " ({ int d; int b; d = 3 * 2 - 1;b = 5; d * b; })");
    assert(25,  ({ int abc; int b; abc = 3 * 2 - 1;b = 5; abc * b; }), " ({ int abc; int b; abc = 3 * 2 - 1;b = 5; abc * b; })");
    assert(50,  ({ int abc; int b; abc = 3 * 2 - 1;b = abc + 5; abc * b; }), " ({ int abc; int b; abc = 3 * 2 - 1;b = abc + 5; abc * b; })");

    assert(3, ({ int x=0; if (0) x=2; else x=3; x; }), "({ int x=0; if (0) x=2; else x=3; x; })");
    assert(3, ({ int x=0; if (1-1) x=2; else x=3; x; }), "({ int x=0; if (1-1) x=2; else x=3; x; })");
    assert(2, ({ int x=0; if (1) x=2; else x=3; x; }), "({ int x=0; if (1) x=2; else x=3; x; })");
    assert(2, ({ int x=0; if (2-1) x=2; else x=3; x; }), "({ int x=0; if (2-1) x=2; else x=3; x; })");
    assert(2, ({ if (1 == 2) { 1; } else if (1 == 1) { 2; } else { 3; } }), "({ if (1 == 2) { 1; } else if (1 == 1) { 2; } else { 3; } })");

    printf("while...\n");
    assert(3, ({ 1; {2;} 3; }), "({ 1; {2;} 3; })");
    assert(10, ({ int i=0; i=0; while(i<10) i=i+1; i; }), "({ int i=0; i=0; while(i<10) i=i+1; i; })");
    assert(55, ({ int i=0; int j=0; while(i<=10) {j=i+j; i=i+1;} j; }), "({ int i=0; int j=0; while(i<=10) {j=i+j; i=i+1;} j; })");
    assert(1, ({ int x=0; while(1) { x++; break; } x; }), "({ int x=0; while(1) { x++; break; } x; })");
    assert(3, ({ int x=0; while(x < 3) { if (x <= 3) { x++; continue; } break; } x; }), "({ int x=0; while(x > 3) { if (x <= 3) { x++; continue; } break; } x; })");

    printf("do ~ while...\n");
    assert(5, ({ int x=0; do { x++; } while(x < 5); x; }),"{ int x=0; do { x++; } while(x < 5); x; }" );
    assert(4, ({ int x=0; do { if (x > 3) { break; } x++; } while(x < 5); x; }),"{ int x=0; do { if (x > 3) { break; } x++; } while(x < 5); x; }" );
    assert(5, ({ int x=0; int y = 0; do { if (y < 5) { y++; continue; }  x++; } while(x != 1); y; }),"int x=0; int y = 0; do { if (y < 5) { y++; continue; }  x++; } while(x != 1); y; }" );


    printf("for...\n");

// switch
    assert(6, ({ int x=0; switch(3) { case 2: x = 5; break; case 3: x=6; break; case 4: x=7; break;} x;}), "({ int x=0; switch(3) { case 2: x = 5; break; case 3: x=6; break; case 4: x=7; break;} x;})");
    assert(7, ({ int x=0; switch(3) { case 2: x = 5; case 3: x=6; case 4: x=7; } x;}), "({ int x=0; switch(3) { case 2: x = 5; case 3: x=6; case 4: x=7;} x;})");
    assert(0, ({ int x=0; switch(3) { case 1: x = 5; } x;}), "({ int x=0; switch(3) { case 1: x = 5; } x;})");
    assert(4, ({ int x=0; switch(3) { case 1: x = 1; case 2: x=2; default: x=4;} x; }), "({ int x=0; switch(3) { case 1: x = 1; case 2: x=2; default: x=4;} x; })");
    assert(4, ({ int x=0; switch(3) { case 1: x = 1; break; default: x=4; break;case 2: x=2; break;} x; }), "({ int x=0; switch(3) { case 1: x = 1; break; default: x=4; break;case 2: x=2; break;} x; })");

    assert(55, ({ int i=0; int j=0; for (i=0; i<=10; i=i+1) j=i+j; j; }), "({ int i=0; int j=0; for (i=0; i<=10; i=i+1) j=i+j; j; })");
    assert(6, ({ int i = 0; for (;;){ if (i > 5) { break; } i++; } i; }), "({ int i = 0; for (;;){ if (i > 5) { break; } i++} i; })");
    assert(4, ({int j = 0; for (int i = 0; i < 5; i++) { j = i; } j; }), "({int j = 0; for (int i = 0; i < 5; i++) { j = i; } j; })");
    assert(5, ({ int i=0; for (; i < 10; i++) { if (i==5) break; } i; }), "({ int i=0; for (; i < 10; i++) { if (i==5) break; } i; })");

    assert(7, ({ int i=0; for (int j=0; j < 10; j++) { if (j < 3) continue; i++; } i;}), "({ int i=0; for (int j=0; j < 10; j++) { if (j < 3) continue; i++; } i;})");
    assert(3, ({int x=0; if (1 == 0) { x=1; } else { x=3; } x; }), "({int x=0; if (1 == 0) { x=1; } else { x=3; } x; })");
    printf("function call...\n");
    assert(20,  ({ hoge(); }), " ({ hoge(); })");
    assert(30,  ({ int a; a = 30; }), " ({ int a; a = 30; })");
    assert(30,  ({ int a; int b; a = hoge(); b = 10; a + b; }), " ({ int a; int b; a = hoge(); b = 10; a + b; })");
    assert(25,  ({ int fuga; int hoge; fuga = fuga(); hoge = hoge(); fuga + hoge; }), " ({ int fuga; int hoge; fuga = fuga(); hoge = hoge(); fuga + hoge; })");
    assert(3,  ({ add1(3); }), " ({ add1(3); })");
    assert(7,  ({ add2(3, 4); }), " ({ add2(3, 4); })");
    assert(8, ({ int ary[2][2]; ary[0][0]=3; ary[0][1]=5; add2_array(ary); }), "({ int ary[2][2]; ary[0][0]=3; ary[0][1]=5; add2_array(ary); })");
    assert(8, ({ int ary[2][2]; ary[1][0]=3; ary[1][1]=5; add2_array(ary+1); }), "({ int ary[2][2]; ary[0][0]=3; ary[0][1]=5; add2_array(ary+t1); })");
    assert(12,  ({ add3(3, 4, 5); }), " ({ add3(3, 4, 5); })");
    assert(18,  ({ add4(3, 4, 5, 6); }), " ({ add4(3, 4, 5, 6); })");
    assert(25,  ({ add5(3, 4, 5, 6, 7); }), " ({ add5(3, 4, 5, 6, 7); })");
    assert(33,  ({ add6(3, 4, 5, 6, 7, 8); }), " ({ add6(3, 4, 5, 6, 7, 8); })");
    assert(36,  ({ add2(1, 2) + add6(3, 4, 5, 6, 7, 8); }), " ({ add2(1, 2) + add6(3, 4, 5, 6, 7, 8); })");
    assert(1, ({int a; int *p = &a; *p = 1;  *p;}), "({int a; int *p = &a; *p = 1;  *p;})");
    assert(39, ({ int **q; q = alloc2(39);  **q; }), "({ int **q; q = alloc2(39);  **q; })");
    assert(42, ({ int *p; p = alloc(42);  *p; }), "({ int *p; p = alloc(42);  *p; })");
    assert(22, ({ int *p; int **q; p = alloc(42); q = alloc2(22); p = *q;  *p; }), "({ int *p; int **q; p = alloc(42); q = alloc2(22); p = *q;  *p; })");
    assert(5,  ({ int x; int *p; p = &x; x = 5;  *p;}), " ({ int x; int *p; p = &x; x = 5;  *p;})");
    assert(3,  ({ int x; int y; int* p; int** q; y = 3; x = 5; p = &x; q = &p; *q = &y;  **q; }), " ({ int x; int y; int* p; int** q; y = 3; x = 5; p = &x; q = &p; *q = &y;  **q; })");
    assert(3,  ({ int x = 3;  x;}), " ({ int x = 3;  x;})");
    assert(3,  ({ int x = 3; int *y = &x;  *y;}), " ({ int x = 3; int *y = &x;  *y;})");
    assert(0,  ({  0&&0; }), " ({  0&&0; })");
    assert(0,  ({  1&&0; }), " ({  1&&0; })");
    assert(0,  ({  0&&1; }), " ({  0&&1; })");
    assert(1,  ({  1&&1; }), " ({  1&&1; })");
    assert(0,  ({  0||0; }), " ({  0||0; })");
    assert(1,  ({  1||0; }), " ({  1||0; })");
    assert(1,  ({  0||1; }), " ({  0||1; })");
    assert(1,  ({  1||1; }), " ({  1||1; })");
    assert(1,  ({  1||1; }), " ({  1||1; })");
    assert(1,  ({  1|1; }), " ({  1|1; })");
    assert(7,  ({  5|2; }), " ({  5|2; })");
    assert(15,  ({  8|5|2; }), " ({  8|5|2; })");
    assert(2,  ({  6 & 3; }), " ({ 6 & 3; })");
    assert(0,  ({  6 & 0; }), " ({ 6 & 0; })");
    assert(2,  ({  18 & 6 & 3; }), " ({  18 & 6 & 3; })");
    assert(12, (5 ^ 9), "5 ^ 9");
    assert(10, (5 ^ 6 ^ 9), "5 ^ 6 ^ 9");
    assert(12, (3<<2), "3<<2");
    assert(8, (1<<3), "1<<3");
    assert(4, (16>>2), "16>>2");
    assert(4,  ({ int *p; p = alloc4(1, 2, 4, 8); p = p + 2;   *p; }), " ({ int *p; p = alloc4(1, 2, 4, 8); p = p + 2;   *p; })");
    assert(8,  ({ int *p; p = alloc4(1, 2, 4, 8); p = p + 3;   *p; }), " ({ int *p; p = alloc4(1, 2, 4, 8); p = p + 3;   *p; })");
    assert(2,  ({ int *p; p = alloc4(1, 2, 4, 8); p = p + 3; p = p -2;   *p; }), " ({ int *p; p = alloc4(1, 2, 4, 8); p = p + 3; p = p -2;   *p; })");
// alloc
    assert(3, ({ int* pp = alloc4(1, 2, 4, 8); int* pq = alloc4(3, 5, 7, 9); int*** tpp = alloc5(&pp, &pq); tpp = tpp + 1;  ***tpp; }), "({ int* pp = alloc4(1, 2, 4, 8); int* pq = alloc4(3, 5, 7, 9); int*** tpp = alloc5(&pp, &pq); tpp = tpp + 1;  ***tpp; })");
    assert(8, ({ int* pp = alloc4(1, 2, 4, 8); int* pq = alloc4(3, 5, 7, 9); int*** tpp = alloc5(&pp, &pq); pp = pp + 3;  ***tpp; }), "({ int* pp = alloc4(1, 2, 4, 8); int* pq = alloc4(3, 5, 7, 9); int*** tpp = alloc5(&pp, &pq); pp = pp + 3;  ***tpp; })");
    assert(2, ({ int* pp = alloc4(1, 2, 4, 8); int* pq = alloc4(3, 5, 7, 9); int*** tpp = alloc5(&pp, &pq); **tpp = **tpp + 1;  ***tpp; }), "({ int* pp = alloc4(1, 2, 4, 8); int* pq = alloc4(3, 5, 7, 9); int*** tpp = alloc5(&pp, &pq); **tpp = **tpp + 1;  ***tpp; })");
// sizeof
    printf("sizeof\n");
    assert(4,  ({ sizeof(1); }), " ({ sizeof(1); })");
    assert(4,  ({ int x; sizeof(x); }), " ({ int x; sizeof(x); })");
    assert(8,  ({ int *x; sizeof(x); }), " ({ int *x; sizeof(x); })");
    assert(4,  ({ int *x; sizeof(*x); }), " ({ int *x; sizeof(*x); })");
    assert(4,  ({ sizeof 1; }), " ({ sizeof 1; })");
    assert(4,  ({ sizeof("abc"); }), " ({ sizeof(\"abc\"); })");
    assert(7, sizeof("abc" "def"), "sizeof(\"abc\" \"def\")");
    assert(9, sizeof("ab\0c" "\0def"), "sizeof(\"abc\" \"def\")");
    assert(1, sizeof(char), "sizeof(char)");
    assert(4, sizeof(int), "sizeof(int)");
    assert(8, sizeof(char*), "sizeof(char*)");
    assert(8, sizeof(int *), "sizeof(int*)");
    assert(8, sizeof(int **), "sizeof(int**)");
    assert(8, sizeof(int(*)[4]), "sizeof(int(*)[4])");
    assert(32, sizeof(int* [4]), "sizeof(int*[4])");
    assert(16, sizeof(int [4]), "sizeof(int*[4])");
    assert(48, sizeof(int [3][4]), "sizeof(int*[4])");
    assert(8, sizeof(struct {int a; int b;}), " sizeof(struct {int a; int b;})");


// array
    assert(5,  ({ int a[2]; *a = 2; *(a + 1) = 3; int *p; p = a;  *p + *(p + 1); }), " ({ int a[2]; *a = 2; *(a + 1) = 3; int *p; p = a;  *p + *(p + 1); })");
    assert(3,  ({ int a[2]; a[1] = 3;  a[1]; }), " ({ int a[2]; a[1] = 3;  a[1]; })");
    assert(12, ({ int a[2]; a[0] = 12;  a[0]; }), "({ int a[2]; a[0] = 12;  a[0]; })");
    assert(12, ({ int i = 0; int a[2]; a[0] = 12;  a[i]; }), "({ int i = 0; int a[2]; a[0] = 12;  a[i]; })");
    assert(12, ({ int a[2][2]; a[0][0] = 12;  a[0][0]; }), "({ int a[2][2]; a[0][0] = 12;  a[0][0]; })");

// Global variables
    assert(10, ({ g1 = 10;  g1; }), "({ g1 = 10;  g1; })");
    assert(15, ({  g2[0] = 5; g2[4] = 10;  g2[0] + g2[4]; }), "({  g2[0] = 5; g2[4] = 10;  g2[0] + g2[4]; })");
    assert(20,  ({  sizeof(g2); }), " ({  sizeof(g2); })");
    assert(20, ({  sizeof(g2); }), "({  sizeof(g2); })");

// char type
    assert(6, ({ char x[3];  { x[0] = 2; int y = 4;  x[0] + y; }}), "({ char x[3];  { x[0] = 2; int y = 4;  x[0] + y; }})");
    assert(6,  ({ char x[3]; x[0] = 2; int y = 4;  x[0] + y; }), " ({ char x[3]; x[0] = 2; int y = 4;  x[0] + y; })");

// char literal
    assert(97, 'a', "\'a\'");
    assert(59, ';', "\';\'");
    assert(10, '\n', "\'n\'");
    assert(92, '\\', "\'\\'");
    assert(0, '\0', "\'0\'");

// string literal
    assert(97,  ({ char *p = "abc";  p[0]; }), "({ char *p = \"abc\";  p[0]; })");
    assert(98,  ({ char *p = "abc";  p[1]; }), " ({ char *p = \"abc\";  p[1]; })");
    assert(99,  ({ char *p = "abc";  p[2]; }), " ({ char *p = \"abc\";  p[2]; })");
    assert(0,  ({ char *p = "abc";  p[3]; }), " ({ char *p = \"abc\";  p[3]; })");
    assert(0,  ({ char *p = "hello world"; show(p);  0; }), " ({ char *p = \"hello world\"; show(p);  0; })");

// struct
    assert(4,  ({ struct { int a; } x;  sizeof(x); }), " ({ struct { int a; } x;  sizeof(x); })");
    assert(8,  ({ struct { int a; int b; } x;  sizeof(x); }), " ({ struct { int a; int b; } x;  sizeof(x); })");
    assert(12,  ({ struct { char a; char b; int c; char d;} x;  sizeof(x); }), " ({ struct { char a; char b; int c; char d;} x;  sizeof(x); })");
    assert(2,  ({ struct { char a; char b; } x;  sizeof(x); }), " ({ struct { char a; char b; } x;  sizeof(x); })");
    assert(8,  ({ struct { char a; char b; int c; } x;  sizeof(x); }), " ({ struct { char a; char b; int c; } x;  sizeof(x); })");
    assert(4,  ({ struct { char a; char b; struct { char a; char b; } c; } x;  sizeof(x); }), " ({ struct { char a; char b; struct { char a; char b; } c; } x;  sizeof(x); })");
    assert(12,  ({ struct { char a; char b; struct { char a; int b; } c; } x;  sizeof(x); }), " ({ struct { char a; char b; struct { char a; int b; } c; } x;  sizeof(x); })");
    assert(3,  ({ struct { int a; } x; x.a = 3;  x.a; }), " ({ struct { int a; } x; x.a = 3;  x.a; })");
    assert(8,  ({ struct { int a; int b; } x; x.a = 3; x.b = 5;  (x.a + x.b); }), " ({ struct { int a; int b; } x; x.a = 3; x.b = 5;  (x.a + x.b); })");
    assert(8,  ({ struct { char a; int b; } x; x.a = 3; x.b = 5;  (x.a + x.b); }), " ({ struct { char a; int b; } x; x.a = 3; x.b = 5;  (x.a + x.b); })");
    assert(8,  ({ struct { char a; char b; } x; x.a = 3; x.b = 5;  (x.a + x.b); }), " ({ struct { char a; char b; } x; x.a = 3; x.b = 5;  (x.a + x.b); })");
    assert(18,  ({ struct { char a; char b; int c; } x; x.a = 3; x.b = 5; x.c = 10;  (x.a + x.b + x.c); }), " ({ struct { char a; char b; int c; } x; x.a = 3; x.b = 5; x.c = 10;  (x.a + x.b + x.c); })");
    assert(18,  ({ struct { char a; char b; int c; struct { char d; char e; } f;}  x; x.a = 3; x.b = 5; x.c = 10;  (x.a + x.b + x.c); }), " ({ struct { char a; char b; int c; struct { char d; char e; } f;}  x; x.a = 3; x.b = 5; x.c = 10;  (x.a + x.b + x.c); })");
    assert(8,  ({ struct tag { char a; int b; } x; struct tag *p = &x; x.a = 3; x.b = 5;  p->a + p->b; }), " ({ struct tag { char a; int b; } x; struct tag *p = &x; x.a = 3; x.b = 5;  p->a + p->b; })");
    assert(8,  ({ struct { char a; int b; } x; struct { char a; int b; } *p = &x; x.a=3; x.b=5;  p->a+p->b; }), " ({ struct { char a; int b; } x; struct { char a; int b; } *p = &x; x.a=3; x.b=5;  p->a+p->b; })");
    assert(48,  ({ struct { struct { int b; int c[5]; } a[2]; } x;  sizeof(x); }), " ({ struct { struct { int b; int c[5]; } a[2]; } x;  sizeof(x); })");
    assert(8,  ({ struct { struct { int b; int c[5]; } a[2]; } x; x.a[0].b = 3; x.a[0].c[1] = 5;  x.a[0].b + x.a[0].c[1]; }), " ({ struct { struct { int b; int c[5]; } a[2]; } x; x.a[0].b = 3; x.a[0].c[1] = 5;  x.a[0].b + x.a[0].c[1]; })");
    assert(4, ({ Point p; p.x = 4; p.y = 5; p.x; }), "({ Point p; p.x = 4; p.y = 5; p.x})");
    assert(4, ({ HogeStruct p; p.x = 4; p.y = 5; p.x; }), "({ HogeStruct p; p.x = 4; p.y = 5; p.x})");

// typedef
    assert(3,  ({ typedef int foo; foo x; x = 3;  x; }), " ({ typedef int foo; foo x; x = 3;  x; })");
    assert(3,  ({ typedef struct { int a; int b; } foo; foo x; x.a = 3;  x.a; }), " ({ typedef struct { int a; int b; } foo; foo x; x.a = 3;  x.a; })");

// !
    assert(0,  ({ !1; }), " ({ !1; })");
    assert(0,  ({ !"hoge"; }), " ({ !\"hoge\"; })");
    assert(1,  ({ !0; }), " ({ !0; })");
    assert(1,  ({ !(3 > 4); }), " ({ !(3 > 4); })");
// ~
    assert(-1, ~0, "~0");
    assert(-4, ~3, "~3");

// function alignment
    assert(0,  ({ int e1; e1 = 0;  0;}), " ({ int e1; e1 = 0;  0;})");
    assert(0,  ({ printf("OK");  0;}), " ({ printf(\"OK\");  0;})");
    assert(0,  ({ int e1; e1 = 1; printf("OK");  0;}), " ({ int e1; e1 = 1; printf(\"OK\");  0;})");
    assert(0,  ({ int e1; e1 = 0; printf("OK");  0;}), " ({ int e1; e1 = 0; printf(\"OK\");  0;})");
// extern
    assert(5, ({ global_var; }), "global_var");
// ?:
    assert(42, ({ 5 == 1 ? 3 : 42; }), "({ 5 == 1 ? 3 : 42; })");
    assert(1, ({ 1 == 1 ? 1 : 42; }), "({ 1 == 1 ? 1 : 42; })");
    assert(1, ({ 1 == 1 ? 4 == 2 ? 32 : 1 : 42; }),"({ 1 == 1 ? 4 == 2 ? 32 : 1 : 42; })");
// ,operator
    assert(3, (1, 2, 3), "(1, 2, 3)");
// pre inc ++i
    assert(4, ({int i = 3; ++i;}), "({int i = 3; ++i;})");
    assert(4, ({int i = 3; int *j; j = &i; ++*j;}), "({int i = 3; int *j; j = &i; ++*j;})");
// pre dec --i
    assert(2, ({int i = 3; --i;}), "({int i = 3; --i;})");
    assert(2, ({int i = 3; int *j; j = &i; --*j;}), "({int i = 3; int *j; j = &i; --*j;})");
    assert(-1, ({ post_decl(-1); }), "post_decl(-1);");
    assert(-1, ({ pre_decl(-1); }), "post_decl(-1);");
// post inc i++
    assert(3, ({int i = 3; i++;}), "({int i = 3; i++;})");
    assert(3, ({int i = 3; int *j; j = &i; *j++;}), "({int i = 3; int *j; j = &i; *j++;})");
    assert(1, ({ int ary[2]; ary[0]=1; ary[1]=2; int *p=ary; *p++;}), "({ int ary[2]; ary[0]=1; ary[1]=2; int *p=ary; return *p++;})");
    assert(2, ({ int ary[2]; ary[0]=1; ary[1]=2; int *p=ary; *++p;}), "({ int ary[2]; ary[0]=1; ary[1]=2; int *p=ary; return *++p;})");
    assert(2, ({ int ary[2]; int i = 0; ary[i++]=1; ary[i++]=2; int *p=ary; *++p;}), "({ int ary[2]; int i = 0; ary[i++]=1; ary[i++]=2; int *p=ary; *++p;})");
// post inc i--
    assert(3, ({int i = 3; i--;}), "({int i = 3; i--;})");
    assert(3, ({int i = 3; int *j; j = &i; *j++;}), "({int i = 3; int *j; j = &i; *j++;})");
// break
    assert(5, ({int i = 0; while(i < 10) { if (i >= 5) { break; } i++; } i;}), "({int i = 0; while(i < 10) { if (i >= 5) { break; } i++; } i;})");
    assert(5, ({int i; for (i = 0; i < 10; i++) { if (i >= 5) { break; }} i;}), "({ for(int i = 0; i < 10; i++) { if (i >= 5) { break; }} i;})");
// assignment operator
    assert(20, ({int a = 4; a *= 5; a; }), "({int a = 4; a *= 5; a; })");
    assert(4, ({int a = 20; a /= 5; a; }), "({int a = 20; a /= 5; a; })");
    assert(2, ({int a = 5; a %= 3; a; }), "({int a = 5; a %= 3; a; })");
    assert(8, ({int a = 5; a += 3; a; }), "({int a = 5; a += 3; a; })");
    assert(2, ({int a = 5; a -= 3; a; }), "({int a = 5; a -= 3; a; })");
    assert(40, ({int a = 5; a <<= 3; a; }), "({int a = 5; a <<= 3; a; })");
    assert(5, ({int a = 40; a >>= 3; a; }), "({int a = 40; a >>= 3; a; })");
    assert(1, ({int a = 5; a &= 3; a; }), "({int a = 5; a &= 3; a; })");
    assert(6, ({int a = 5; a ^= 3; a; }), "({int a = 5; a ^= 3; a; })");
    assert(7, ({int a = 5; a |= 3; a; }), "({int a = 5; a |= 3; a; })");

    assert(3, ({ int x; int y; x=y=3; x; }), "({ int x; int y; x=y=3; x; })");
    assert(3, ({ int x; int y; x=y=3; y; }), "({ int x; int y; x=y=3; y; })");
// static
    assert(3, static_fn(), "static_fn()");
    assert(3, ext1, "ext1");

    int M1 = 5;
#define M1 3
    assert(3, M1, "M1");
#define M1 4
    assert(4, M1, "M1");
#undef M1
    assert(5, M1, "M1");

// _Bool
    assert(0, ({ _Bool x = 0; x; }), "({ _Bool x = 0; x; })");
    assert(1, ({ _Bool x = 1; x; }), "({ _Bool x = 1; x; })");
    assert(0, ({ _Bool x; x = 0; x; }), "({ _Bool x; x = 0; x; })");
    assert(1, ({ _Bool x; x = 2; x; }), "({ _Bool x; x = 2; x; })");
    assert(0, ({ _Bool x; int y = 0; x = y; x; }), "({ _Bool x; int y = 0; x = y; x; })");
    assert(1, ({ _Bool x; int y = -1; x = y; x; }), "({ _Bool x; int y = -1; x = y; x; })");
    assert(0, ({ _Bool x; int y = 0; x = y; x; }), "({ _Bool x; int y = 0; x = y; x; })");
    assert(1, ({ _Bool x; int y = 1; x = y; x; }), "({ _Bool x; int y = 1; x = y; x; })");
    assert(100, ({ int i = 100; _Bool x; x = 0; i; }),"({ int i = 100; _Bool x; x = 0; i; })");
    assert(1, test_bool(123), "test_bool(123)");
    assert(1, test_bool(122), "test_bool(122)");
    assert(0, test_bool(0), "test_bool(0)");
// local variable initialize
    assert(0, ({ int x[3] = {}; x[0]; }), "int x[3] = {}; x[0];");
    assert(0, ({ int x[3] = {}; x[1]; }), "int x[3] = {}; x[1];");
    assert(0, ({ int x[3] = {}; x[2]; }), "int x[3] = {}; x[2];");
    assert(1, ({ int x[3] = {1, 2, 3}; x[0]; }), "({ int x[3] = {1, 2, 3}; x[0]; })");
    assert(2, ({ int x[3] = {1, 2, 3}; x[1]; }), "({ int x[3] = {1, 2, 3}; x[0]; })");
    assert(3, ({ int x[3] = {1, 2, 3}; x[2]; }), "({ int x[3] = {1, 2, 3}; x[0]; })");
    assert(2, ({ int x[2][3]={{1,2,3},{4,5,6}}; x[0][1]; }), "({ int x[2][3]={{1,2,3},{4,5,6}}; x[0][1]; })");
    assert(4, ({ int x[2][3]={{1,2,3},{4,5,6}}; x[1][0]; }), "({ int x[2][3]={{1,2,3},{4,5,6}}; x[1][0]; })");
    assert(6, ({ int x[2][3]={{1,2,3},{4,5,6}}; x[1][2]; }), "({ int x[2][3]={{1,2,3},{4,5,6}}; x[1][2]; })");
    assert(2, ({ int x[2][3]={{1,2}}; x[0][1]; }), "int x[2][3]={{1,2}}; x[0][1];");
    assert(0, ({ int x[2][3]={{1,2}}; x[1][0]; }), "int x[2][3]={{1,2}}; x[1][0];");
    assert(0, ({ int x[2][3]={{1,2}}; x[1][2]; }), "int x[2][3]={{1,2}}; x[1][2];");
    assert('a', ({ char x[4] = "abc"; x[0]; }), "char x[4] = \"abc\"; x[0];");
    assert('c', ({ char x[4] = "abc"; x[2]; }), "char x[4] = \"abc\"; x[2];");
    assert(0, ({ char x[4] = "abc"; x[3]; }), "char x[4] = \"abc\"; x[3];");
    assert('a', ({ char x[2][4] = {"abc", "def"}; x[0][0]; }), "char x[2][4] = {\"abc\", \"def\"}; x[0][0];" );
    assert(0, ({ char x[2][4] = {"abc", "def"}; x[0][3]; }), "char x[2][4] = {\"abc\", \"def\"}; x[0][3];" );
    assert('d', ({ char x[2][4] = {"abc", "def"}; x[1][0]; }), "char x[2][4] = {\"abc\", \"def\"}; x[1][0];" );
    assert('f', ({ char x[2][4] = {"abc", "def"}; x[1][2]; }), "char x[2][4] = {\"abc\", \"def\"}; x[1][2];" );
    assert(4, ({ int x[] = {1, 2, 3, 4}; x[3]; }), "int x[] = {1, 2, 3, 4}; x[3];");
    assert(16, ({ int x[] = {1, 2, 3, 4}; sizeof(x); }), "int x[] = {1, 2, 3, 4}; sizeof(x);");
    assert(4, ({ char x[] = "foo"; sizeof(x); }), "char x[] = \"foo\"; sizeof(x);");

    assert(1, ({ struct { int a; int b; int c; } x = {1, 2, 3}; x.a; }), "struct { int a; int b; int c; } x = {1, 2, 3}; x.a;");
    assert(2, ({ struct { int a; int b; int c; } x = {1, 2, 3}; x.b; }), "struct { int a; int b; int c; } x = {1, 2, 3}; x.b;");
    assert(3, ({ struct { int a; int b; int c; } x = {1, 2, 3}; x.c; }), "struct { int a; int b; int c; } x = {1, 2, 3}; x.c;");
    assert(1, ({ struct { int a; int b; int c; } x = {1}; x.a; }), "struct { int a; int b; int c; } x = {1}; x.a;");
    assert(0, ({ struct { int a; int b; int c; } x = {1}; x.b; }), "struct { int a; int b; int c; } x = {1}; x.b;");
    assert(0, ({ struct { int a; int b; int c; } x = {1}; x.c; }), "struct { int a; int b; int c; } x = {1}; x.c;");
    assert(1, ({ struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[0].a; }), "struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[0].a;");
    assert(2, ({ struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[0].b; }), "struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[0].b;");
    assert(3, ({ struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[1].a; }), "struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[1].a;");
    assert(4, ({ struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[1].b; }), "struct {int a; int b;} x[2] = {{1, 2}, {3, 4}}; x[1].b;");

    assert(0, ({ struct {int a; int b;} x[2]={{1, 2}}; x[1].b; }), "struct {int a; int b;} x[2]={{1, 2}}; x[1].b;" );

    assert(0, ({ struct {int a; int b;} x={}; x.a; }), "struct {int a; int b;}; x={}; x.a;");
    assert(0, ({ struct {int a; int b;} x={}; x.b; }), "struct {int a; int b;}; x={}; x.b;");

    assert(3, g3, "g3");
    assert(5, g4, "g4");
    assert(5, *g5, "*g5");
    assert(0, strcmp(g6, "abc"), "strcmp(g6, \"abc\")");

    assert(0, g7[0], "g7[0]");
    assert(1, g7[1], "g7[1]");
    assert(2, g7[2], "g7[2]");

    assert(0, strcmp(g8[0], "foo"), "strcmp(g8[0], \"foo\")");
    assert(0, strcmp(g8[1], "bar"), "strcmp(g8[1], \"bar\")");
    assert(1, g9[0].a, "g9[0].a");
    assert(2, g9[0].b, "g9[0].b");
    assert(3, g9[1].a, "g9[1].a");
    assert(4, g9[1].b, "g9[1].b");

    assert(1, g10[0].a[0], "g10[0].a[0]");
    assert(2, g10[0].a[1], "g10[0].a[1]");
    assert(0, g10[1].a[0], "g10[1].a[0]");
    assert(0, g10[1].a[1], "g10[1].a[1]");

// enum
    assert(0, ({ enum { zero, one, two }; zero; }), "{ enum { zero, one, two }; zero; }");
    assert(1, ({ enum { zero, one, two }; one; }), "{ enum { zero, one, two }; one; }");
    assert(2, ({ enum { zero, one, two }; two; }), "{ enum { zero, one, two }; two; }");
    assert(5, ({ enum { five=5, six, seven }; five; }), "{ enum { five=5, six, seven }; five; }");
    assert(6, ({ enum { five=5, six, seven }; six; }), "enum { five=5, six, seven }; six;");
    assert(7, ({ enum { five=5, six, seven }; seven; }), "enum { five=5, six, seven }; seven;");
    assert(0, ({ enum { zero, five=5, three=3, four }; zero; }), "enum { zero, five=5, three=4, four }; zero;");
    assert(5, ({ enum { zero, five=5, three=3, four }; five; }), "enum { zero, five=5, three=4, four }; five;");
    assert(3, ({ enum { zero, five=5, three=3, four }; three; }), "enum { zero, five=5, three=4, four }; three;");
    assert(4, ({ enum { zero, five=5, three=3, four }; four; }), "enum { zero, five=5, three=4, four }; four;");
    assert(4, ({ enum { zero, one, two} x; sizeof(x); }), "{ enum { zero, one, two} x; sizeof(x); }");
    assert(4, ({ enum t { zero, one, two }; enum t y; sizeof(y); }), "{ enum { zero, one, two} x; sizeof(x); }");

#if 0
#include "/no/such/file"
    assert(0, 1, "1");
#if nested
#endif
#endif
    assert(3, 1
#if 1
            +2
#endif
            , "1 + 2");
#if 1 + 2
    assert(3, 1 + 2, "eval test..1 + 2");
#endif
  assert(3, 1
#if 1
# if 0
#  if 1
    foo bar
#  endif
# endif
    + 2
#endif
    , "1+2");

  assert(3,
#if 1-1
# if 1
# endif
# if 1
# else
# endif
# if 0
# else
# endif
         2,
#else
# if 1
         3,
# endif
#endif
         "3");

  assert(2,
#if 1
         2,
#else
         3,
#endif
         "2");
    assert(3,
#if 0
            1,
#elif 0
            2,
#elif 3+5
            3,
#elif 1*5
            4,
#endif
            "3");
    assert(1,
#if 1+5
            1,
#elif 1
            2,
#elif 3
            2,
#endif
            "1");

#define M 5
    assert(5,
#if M
            5,
#else
            6,
#endif
            "5");
#define M 5
    assert(5,
#if M-5
            6,
#elif M
            5,
#endif
            "5");

    assert(3,
#ifdef UNDEFINED_M
           5,
#else
           3,
#endif
           "3");

#define M2
    assert(2,
#ifdef M2
            2,
#else
            3,
#endif
            "2");

    assert(3,
#ifndef UNDEFINED_M
            3,
#else
            5,
#endif
            "3");
    assert(3,
#ifndef M2
            5,
#else
            3,
#endif
            "3");
#if 0
#ifdef NO_SUCH_MACRO
#endif
#ifndef NO_SUCH_MACRO
#endif
#else
#endif
#define M3
    assert(3,
#if defined(M3)
            3,
#else
            4,
#endif
            "3");

#define M3
    assert(3,
#if defined M3
            3,
#else
            4,
#endif
            "3");
    assert(4,
#if defined(M2) - 1
            3,
#else
            4,
#endif
            "4");
assert(4,
#if defined(NO_SUCH_MACRO)
        3,
#else
        4,
#endif
        "4");
assert(4,
#if defined(NO_SUCH_MACRO) && defined(UNDEFINED_M)
        3,
#else
        4,
#endif
        "4");
// long, short
    assert(2, ({ short x; sizeof(x); }), "({ short x; sizeof(x); })");
    assert(4, ({ struct {char a; short b;} x; sizeof(x);}), "{ struct {char a; short b;} x; sizeof(x);}");
    assert(8, ({ long x; sizeof(x); }), "({ long x; sizeof(x); })");
    assert(16, ({ struct {char a; long b;} x; sizeof(x);}), "{ struct {char a; long b;} x; sizeof(x);}");
    assert(1, sub_short(7, 3, 3), "sub_short(7, 3, 3)");
    assert(1, sub_long(7, 3, 3), "sub_long(7, 3, 3)");

    assert(1, ({ char x; sizeof(x); }), "({ char x; sizeof(x); })");
    assert(2, ({ short int x; sizeof(x); }), "({ short int x; sizeof(x); })");
    assert(2, ({ int short x; sizeof(x); }), "({ int short x; sizeof(x); })");
    assert(4, ({ int x; sizeof(x); }), "({ int x; sizeof(x); })");
    assert(8, ({ long int x; sizeof(x); }), "({ long int x; sizeof(x); })");
    assert(8, ({ int long x; sizeof(x); }), "({ int long x; sizeof(x); })");
    assert(8, ({ long long x; sizeof(x); }), "({ long long x; sizeof(x); })");

    assert(1, sizeof(char), "sizeof(char)");
    assert(1, sizeof(signed char), "sizeof(signed char)");
    assert(1, sizeof(signed char signed), "sizeof(signed char signed)");
    assert(1, sizeof(unsigned char), "sizeof(unsigned char)");
    assert(1, sizeof(unsigned char unsigned), "sizeof(unsigned char unsigned)");

    assert(2, sizeof(short), "sizeof(short)");
    assert(2, sizeof(int short), "sizeof(int short)");
    assert(2, sizeof(short int), "sizeof(short int)");
    assert(2, sizeof(signed short), "sizeof(signed short)");
    assert(2, sizeof(int short signed), "sizeof(int short signed)");
    assert(2, sizeof(unsigned short), "sizeof(unsigned short)");
    assert(2, sizeof(int short unsigned), "sizeof(int short unsigned)");

    assert(4, sizeof(int), "sizeof(int)");
    assert(4, sizeof(signed int), "sizeof(signed int)");
    assert(4, sizeof(signed), "sizeof(signed)");
    assert(4, sizeof(signed signed), "sizeof(signed signed)");
    assert(4, sizeof(unsigned int), "sizeof(unsigned int)");
    assert(4, sizeof(unsigned), "sizeof(unsigned)");
    assert(4, sizeof(unsigned unsigned), "sizeof(unsigned unsigned)");

    assert(8, sizeof(long), "sizeof(long)");
    assert(8, sizeof(signed long), "sizeof(signed long)");
    assert(8, sizeof(signed long int), "sizeof(signed long int)");
    assert(8, sizeof(unsigned long), "sizeof(unsigned long)");
    assert(8, sizeof(unsigned long int), "sizeof(unsigned long int)");

    assert(8, sizeof(long long), "sizeof(long long)");
    assert(8, sizeof(signed long long), "sizeof(signed long long)");
    assert(8, sizeof(signed long long int), "sizeof(signed long long int)");
    assert(8, sizeof(unsigned long long), "sizeof(unsigned long long)");
    assert(8, sizeof(unsigned long long int), "sizeof(unsigned long long int)");

    assert(1, sizeof(char), "sizeof(char)");
    assert(255, ({unsigned char x = 255; x; }), "({unsigned char x = 255; x; })");
    assert(-1, ({signed char x = 255; x; }), "({signed char x = 255; x; })");
    assert(-128, ({signed char x = 128; x; }), "({signed char x = 128; x; })");

    assert(-1, ({ short x = 65535; x; }), "({ short x = 65535; x; })");
    assert(65535, ({ unsigned short x = 65535; x; }), "({ unsigned short x = 65535; x; })");
    assert(-1, ({ int x = 0xffffffff; x; }), "({ int x = 0xffffffff; x; })");
    // assert(4294967295, ({ unsigned int x = 0xffffffff; x; }), "({ unsigned int x = 0xffffffff; x; })");
    assert(1, -1 < 1, "-1<1");
    //assert(0, ({ unsigned int x = 1; -1 < x; }), "({ unsigned int x = 1; -1 < x; })");
    assert(254, ({ char a = 127; char b = 127; a + b; }), "({ char a = 127; char b = 127; a + b; })");
    assert(20, ({ char a = 40; char b = 2; a / b; }), "({ char a = 40, char b = 2; a / b; })");
    assert(20, ({ long a = 40; long b = 2; a / b; }), "({ long a = 40, long b = 2; a / b; })");
    assert(20, ({ short a = 40; short b = 2; a / b; }), "({ short a = 40, short b = 2; a / b; })");
    assert(20, ({ int a = 40; int b = 2; a / b; }), "({ int a = 40, int b = 2; a / b; })");

    assert(20, ({ unsigned char a = 40; unsigned char b = 2; a / b; }), "({ unsigned char a = 40; unsigned char b = 2; a / b; })");
    assert(20, ({ unsigned long a = 40; unsigned long b = 2; a / b; }), "({ unsigned long a = 40; unsigned long b = 2; a / b; })");
    assert(20, ({ unsigned short a = 40; unsigned  short b = 2; a / b; }), "({ unsigned short a = 40; unsigned short b = 2; a / b; })");
    assert(20, ({ unsigned int a = 40; unsigned  int b = 2; a / b; }), "({ unsigned int a = 40; unsigned int b = 2; a / b; })");

    assert(19, ({ char a = 40; char b = 21; a % b; }), "({ char a = 40, char b = 21; a % b; })");
    assert(19, ({ long a = 40; long b = 21; a % b; }), "({ long a = 40, long b = 21; a % b; })");
    assert(19, ({ short a = 40; short b = 21; a % b; }), "({ short a = 40, short b = 21; a % b; })");
    assert(19, ({ int a = 40; int b = 21; a % b; }), "({ int a = 40, int b = 21; a % b; })");

    assert(19, ({ unsigned char a = 40; unsigned char b = 21; a % b; }), "({ unsigned char a = 40; unsigned char b = 21; a % b; })");
    assert(19, ({ unsigned long a = 40; unsigned long b = 21; a % b; }), "({ unsigned long a = 40; unsigned long b = 21; a % b; })");
    assert(19, ({ unsigned short a = 40; unsigned  short b = 21; a % b; }), "({ unsigned short a = 40; unsigned short b = 21; a % b; })");
    assert(19, ({ unsigned int a = 40; unsigned  int b = 21; a % b; }), "({ unsigned int a = 40; unsigned int b = 21; a % b; })");

    assert(-2, (-100)%7, "(-100)%7");

    assert(8, ({long x; sizeof(x);}), "({long x; sizeof(x);})");
    assert(8, sizeof(0L), "sizeof(0L)");
    assert(8, sizeof(0LU), "sizeof(0LU)");
    assert(8, sizeof(0UL), "sizeof(0UL)");
    assert(8, sizeof(0LL), "sizeof(0LL)");
    assert(8, sizeof(0LLU), "sizeof(0LLU)");
    assert(8, sizeof(0Ull), "sizeof(0Ull)");
    assert(8, sizeof(0l), "sizeof(0l)");
    assert(8, sizeof(0ll), "sizeof(0ll)");
    assert(8, sizeof(0x0L), "sizeof(0x0L)");
    assert(4, sizeof(2147483647), "sizeof(2147483647)");
    assert(8, sizeof(2147483648), "sizeof(2147483648)");

    assert(-1, 0xffffffffffffffff, "0xffffffffffffffff");
    assert(8, sizeof(0xffffffffffffffff), "sizeof(0xffffffffffffffff)");
    assert(4, sizeof(4294967295U), "sizeof(4294967295U)");
    assert(8, sizeof(4294967296U), "sizeof(4294967296U)");

    //assert(3, -1U>>30, "-1U>>30");
    //assert(3, -1Ul>>62, "-1Ul>>62");
    //assert(3, -1ull>>62, "-1ull>>62");

    assert(1, 0xffffffffffffffffl>>63, "0xffffffffffffffffl>>63");
    assert(1, 0xffffffffffffffffll>>63, "0xffffffffffffffffll>>63");

    assert(-1, 18446744073709551615, "18446744073709551615");
    assert(8, sizeof(18446744073709551615), "sizeof(18446744073709551615)");
    //assert(-1, 18446744073709551615>>63, "18446744073709551615>>63");

    assert(-1, 0xffffffffffffffff, "0xffffffffffffffff");
    assert(8, sizeof(0xffffffffffffffff), "sizeof(0xffffffffffffffff)");
    assert(1, 0xffffffffffffffff>>63, "0xffffffffffffffff>>63");

    assert(-1, 01777777777777777777777, "01777777777777777777777");
    assert(8, sizeof(01777777777777777777777), "sizeof(01777777777777777777777)");
    assert(1, 01777777777777777777777>>63, "01777777777777777777777>>63");

    //assert(-1, 0b1111111111111111111111111111111111111111111111111111111111111111, "0b1111111111111111111111111111111111111111111111111111111111111111");
    //assert(8, sizeof(0b1111111111111111111111111111111111111111111111111111111111111111), "sizeof(0b1111111111111111111111111111111111111111111111111111111111111111)");
    //assert(1, 0b1111111111111111111111111111111111111111111111111111111111111111>>63, "0b1111111111111111111111111111111111111111111111111111111111111111>>63");

    assert(8, sizeof(2147483648), "sizeof(2147483648)");
    assert(4, sizeof(2147483647), "sizeof(2147483647)");

    assert(8, sizeof(0x1ffffffff), "sizeof(0x1ffffffff)");
    assert(4, sizeof(0xffffffff), "sizeof(0xffffffff)");
    assert(1, 0xffffffff>>31, "0xffffffff>>31");

    assert(8, sizeof(040000000000), "sizeof(040000000000)");
    assert(4, sizeof(037777777777), "sizeof(037777777777)");
    assert(1, 037777777777>>31, "037777777777>>31");

    //assert(8, sizeof(0b111111111111111111111111111111111), "sizeof(0b111111111111111111111111111111111)");
    //assert(4, sizeof(0b11111111111111111111111111111111), "sizeof(0b11111111111111111111111111111111)");
    //assert(1, 0b11111111111111111111111111111111>>31, "0b11111111111111111111111111111111>>31");

    //assert(-1, 1 << 31 >> 31, "1 << 31 >> 31");
    //assert(-1, 01 << 31 >> 31, "01 << 31 >> 31");
    //assert(-1, 0x1 << 31 >> 31, "0x1 << 31 >> 31");
    //assert(-1, 0b1 << 31 >> 31, "0b1 << 31 >> 31");

#define SPACE (-1)
    assert(-1, SPACE, "SPACE");
#define abs(a) (a > 0) ? (a) : (-(a))
    assert(3, abs(-3), "abs(-3)");
#define STRING(X) #X
    printf("%s", STRING(hello));

// alignof
    assert(1, alignof(char), "alignof(char)");
    assert(2, alignof(short), "alignof(short)");
    assert(4, alignof(int), "alignof(int)");
    assert(8, alignof(long), "alignof(long)");
    assert(8, alignof(long long), "alignof(long long)");
    assert(1, alignof(char[3]), "alignof(char[3])");
    assert(4, alignof(int[3]), "alignof(int[3])");
    assert(1, alignof(struct {char a; char b;}[2]), "alignof(struct {char a; char b;}[2])");
    assert(8, alignof(struct {char a; long b;}[2]), "alignof(struct {char a; long b;}[2])");


// variadic
    assert(6, add_all1(1,2,3,0), "add_all1(1,2,3,0)");
// cast
    assert(1, (long)1, "(long)1");
    assert(1, (char)8590066177, "(char)8590066177");
    assert(131585, (int)8590066177, "(int)8590066177");
    assert(513, (short)8590066177, "(short)8590066177");
    assert(5, ({ int x=5; long y=(long)&x; *(int*)y; }), "({ int x=5; long y=(long)&x; *(int*)y; })");

    assert(513, ({ int x=512; *(char *)&x=1; x; }), "({ int x=512; *(char *)&x=1; x; })");
    (0, (long)&*(int *)0, "(long)&*(int *)0");

// unary
    assert(1, ({ is_minus_one(-1); }), "is_minus_one(-1);");

    printf("OK\n");
    return 0;
}
