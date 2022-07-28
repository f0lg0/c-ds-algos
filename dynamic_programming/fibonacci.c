#include <stdio.h>
#include <stdint.h>

//largest interesting n
#define MAXN 45
#define UNKNOWN -1

int32_t fib_ultimate(int32_t n) {
    int32_t back1 = 1;
    int32_t back2 = 0;

    int32_t next;
    if (n == 0) return 0;

    for (int32_t i = 2; i < n; i++) {
        next = back1 + back2;
        back2 = back1;
        back1 = next;
    }

    return back1 + back2;
}

int32_t fib_dp(int32_t n) {
    int32_t f[MAXN + 1];
    f[0] = 0;
    f[1] = 1;

    for (int32_t i = 2; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];

    return f[n];
}

int32_t fib_caching(int32_t* cache, int32_t n) {
    if (cache[n] == UNKNOWN)
        cache[n] = fib_caching(cache, n - 1) + fib_caching(cache, n - 2);

    return cache[n];
}

int32_t fib_caching_driver(int32_t n) {
    int32_t f[MAXN + 1];
    f[0] = 0;
    f[1] = 1;

    for (int32_t i = 2; i <= n; i++)
        f[i] = UNKNOWN;

    return fib_caching(f, n);
}

int32_t main() {
    printf("%d\n", fib_caching_driver(45));
    printf("%d\n", fib_dp(45));
    printf("%d\n", fib_ultimate(45));

    return 0;
}
