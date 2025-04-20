#include <stdint.h>
#include <stdio.h>

int main()
{
    int e = 4294967295;
    printf("%ld", e);
    unsigned char a = 200, b = 100;
    unsigned char c = a + b; // Lỗi do tràn số
    printf("%d\n", c);
    int si = -1;
    unsigned int ui = 1;
    printf("%d\n", si < (int)ui);
    return 0;
}

