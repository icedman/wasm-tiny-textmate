#include <stdio.h>
#include <stdbool.h>

extern void initialize();

int main() {
    initialize();
    printf("initialized\n");
}

