#include <stdio.h>
#include <unistd.h>
#include <asm-generic/unistd.h>
#pragma GCC diagnostic ignored "-Wunused-result"

void print_key_status(long key_data);

int main() {
    long i;
    unsigned long handled_keys = 0x00;
    long key_state;

    printf("input value: ");
    scanf("%ld", &i);
    print_key_status(i);

    do {
        key_state = syscall(__NR_mysyscall, i);

        unsigned long newly_pressed = key_state & ~handled_keys;

        if (newly_pressed) {
            i = newly_pressed; 
            print_key_status(newly_pressed);
            handled_keys |= newly_pressed;
        }

        handled_keys &= key_state;

        if (key_state == 0x80) {
            break;
        }


    } while (1);

    return 0;
}

void print_key_status(long key_data) {
    printf("0:1:2:3:4:5:6:7\n");

    for (int i = 0; i < 8; i++) {
        if (key_data & (1 << i)) {
            printf("O:");
        } else {
            printf("X:");
        }
    }
    printf("\n\n");
}
