#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int isDigit(char c);
int isSymbol(char c);
int isValid(char* file, int width, int height, int y, int first_x, int last_x);
int totalPartNumbers(char* file);

int isDigit(char c) {
    if ((c >= '0') && (c <= '9')) {
        return 1;
    } else {
        return 0;
    }
}

int isSymbol(char c) {
    if (!isDigit(c) && (c != '.')) {
        return 1;
    } else {
        return 0;
    }
}

int isValid(char* file, int width, int height, int y, int first_x, int last_x) {
    int x1 = first_x;
    int x2 = last_x;

    if ((first_x - 1) >= 0) {
        x1 = first_x - 1;

        if (isSymbol(file[y * (width + 1) + x1])) {
            return 1;
        }
    }

    if ((last_x + 1) < width) {
        x2 = last_x + 1;

        if (isSymbol(file[y * (width + 1) + x2])) {
            return 1;
        }
    }

    if ((y + 1) < height) {
        for (int x=x1; x <= x2; x++) {
            if (isSymbol(file[(y + 1) * (width + 1) + x])) {
                return 1;
            }
        }
    }

    if ((y - 1) >= 0) {
        for (int x=x1; x <= x2; x++) {
            if (isSymbol(file[(y - 1) * (width + 1) + x])) {
                return 1;
            }
        }
    }

    return 0;
}

int totalPartNumbers(char* file) {
    int width;
    int height = 0;
    int total = 0;
    int i = 0;

    while (file[i] != '\n') {
        i++;
    }

    width = i;

    while (file[i] != '\0') {
        if (file[i] == '\n') {
            height++;
        }
        i++;
    }

    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (isDigit(file[y * (width + 1) + x])) {
                int first_x = x;
                int number = file[y * (width + 1) + x] - '0';

                x++;
                while ((x < width) && isDigit(file[y * (width + 1) + x])) {
                    number *= 10;
                    number += file[y * (width + 1) + x] - '0';
                    x++;
                }
                x--;

                if (isValid(file, width, height, y, first_x, x)) {
                    total += number;
                }
            }
        }
    }

    return total;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Expected filpath as argument.\n");
        exit(1);
    }

    char* file = readFile(argv[1]);
    
    int total = totalPartNumbers(file);

    printf("%d\n", total);

    free(file);
    return 0;
}