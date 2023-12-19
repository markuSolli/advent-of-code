#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int isSymbol(char c);
void getDimensions(char * file, int* width, int* height);
void connectGears(char* file, int* ratios, int* connections, int number, int width, int height, int y, int first_x, int last_x);
int totalGearRatios(char* file);

int isSymbol(char c) {
    if (!isDigit(c) && (c != '.')) {
        return 1;
    } else {
        return 0;
    }
}

void getDimensions(char * file, int* width, int* height) {
    int i = 0;
    *height = 0;

    while (file[i] != '\n') {
        i++;
    }

    *width = i;

    while (file[i] != '\0') {
        if (file[i] == '\n') {
            *height = *height + 1;
        }
        i++;
    }
}

void connectGears(char* file, int* ratios, int* connections, int number, int width, int height, int y, int first_x, int last_x) {
    int x1 = first_x;
    int x2 = last_x;
    int index;

    if ((first_x - 1) >= 0) {
        x1 = first_x - 1;
        index = y * width + x1;

        if (file[y * (width + 1) + x1] == '*') {
            connections[index]++;

            if (connections[index] <= 2) {
                ratios[index] *= number;
            }
        }
    }

    if ((last_x + 1) < width) {
        x2 = last_x + 1;
        index = y * width + x2;

        if (file[y * (width + 1) + x2] == '*') {
            connections[index]++;

            if (connections[index] <= 2) {
                ratios[index] *= number;
            }
        }
    }

    if ((y + 1) < height) {
        for (int x=x1; x <= x2; x++) {
            index = (y + 1) * width + x;

            if (file[(y + 1) * (width + 1) + x] == '*') {
                connections[index]++;

                if (connections[index] <= 2) {
                    ratios[index] *= number;
                }
            }
        }
    }

    if ((y - 1) >= 0) {
        for (int x=x1; x <= x2; x++) {
            index = (y - 1) * width + x;

            if (file[(y - 1) * (width + 1) + x] == '*') {
                connections[index]++;

                if (connections[index] <= 2) {
                    ratios[index] *= number;
                }
            }
        }
    }
}

int totalGearRatios(char* file) {
    int width, height;
    getDimensions(file, &width, &height);

    int* ratios = (int*) malloc(width * height * sizeof(int));
    int* connections = (int*) malloc(width * height * sizeof(int));

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            ratios[y * width + x] = 1;
            connections[y * width + x] = 0;
        }
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

                connectGears(file, ratios, connections, number, width, height, y, first_x, x);
            }
        }
    }

    int total = 0;

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (connections[y * width + x] == 2) {
                total += ratios[y * width + x];
            }
        }
    }

    free(ratios);
    free(connections);
    return total;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Expected filpath as argument.\n");
        exit(1);
    }

    char* file = readFile(argv[1]);
    
    int total = totalGearRatios(file);

    printf("%d\n", total);

    free(file);
    return 0;
}