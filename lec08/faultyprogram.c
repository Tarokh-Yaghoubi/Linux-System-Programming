
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <string.h>

extern int errno;

void f1();
void f2();
void f3();
void f4();
void f5();
void f6();
void f7();

void f1() {
    int num = 43;
    // this is a simple bug
    if (num = 13)
        printf("variable number is 13\n");
    else
        printf("Variable number is not 13\n");
}

void f2() {

    char* ptr =(char *) malloc (sizeof(char) * 10);
    ptr[13] = 'a';  // this is out of bounds
    free(ptr);
    printf("BYE F2()/...\n");
}

void f3() {

    char * ptr = (char *) malloc (sizeof(char) * 10);
    free(ptr);
    ptr[5] = 'k';
    printf("BYE F3()...\n");

}

void f4() {

    char * ptr = (char *) malloc (sizeof(char) * 10);
    free(ptr);
    free(ptr);  // this is wrong, u cannot free a memory twice

}


void f5() {

    char * ptr = (char *) malloc (sizeof(char) * 10);
    ptr[4] = 'p';
    // here we do not free at all
    printf("BYE F5...\n");
}

char * getString1() {
    char msg[100] = "Tarokh is trying to create and get the bugs\n";
    char * ret = msg;
    return ret;
}

void f6 () {

    // this is problematic cause we are accessing the data inside 
    // the stack-frame of the function getString1 inside function f6().
    char * abc = getString1();
    printf("String: %s\n", abc);

}

char * getString2() {
    char * ret = (char *)malloc(sizeof(char) * 100);
    strcpy(ret, "Tarokh is trying to create and get the bugs\n");
    return ret;
}

void f7() {
    char * abc = getString2();
    printf("%s\n", abc);
    free(abc);  // this is correct way ! 
}


int
main() {
    // f1();
    // f2();
    // f4();
    // f5();
    f7();
    return 0;
}
