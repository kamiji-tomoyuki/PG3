#include <stdio.h>

template <typename Type>
Type Min(Type a, Type b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

template<>
char Min<char>(char a, char b) {
    printf("数字以外は代入出来ません\n");
    return '\0';
}

int main() {
    printf("%d\n", Min<int>(100, 10));
    printf("%f\n", Min<float>(3.14f, 2.14f));
    printf("%lf\n", Min<double>(2.14, 3.14));

    printf("%c\n", Min<char>('a', 'あ'));

    return 0;
}