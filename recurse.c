#include <stdio.h>

int func(int n) {
    if (n == 0) {
        return -2;
    }
    else {
        return 3 * n + (2 * func(n-1)) - 2;
    }
}

int main() {
    int n;
    int ans;

    printf("Enter a value for n:");
    scanf("%d", &n);

    ans = func(n);

    printf("%d \n", ans);
    return 0;
}