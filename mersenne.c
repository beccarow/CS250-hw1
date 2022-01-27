#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    char *a = argv[1];
    int n = atoi(a);
    int x;
    if(argc==2) {
        if(n==1) {
            x=0;
        }

        x = (int) (pow(2, n) - 1);
        printf("%d \n", x);

    }

    return 0;

}