#include <stdio.h>
#include <stdio.h>
#include <math.h>

int func(int n) {
    if (n == 0) {
        return -2;
    }
    else {
        return 3 * n + (2 * (func(n-1))) - 2;
    }
}

int main(int argc, char *argv[]) {
    char *a = argv[1];
    int n = atoi(a);
    int ans;

    ans = func(n);

    printf("%d \n", ans);
    return 0;
}