#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void parseCubes(char* file, int* counts, int* index);
void parseSet(char* file, int* counts, int* index);
int totalSetPower(char* file);

void parseCubes(char* file, int* counts, int* index) {
    int amount = 0;

    while (isDigit(file[*index])) {
        amount *= 10;
        amount += file[*index] - '0';
        *index += 1;
    }

    *index += 1;

    switch (file[*index]) {
        case 'r':
            *index += 3;

            if (amount > counts[0]) {
                counts[0] = amount;
            }
            break;
        case 'g':
            *index += 5;

            if (amount > counts[1]) {
                counts[1] = amount;
            }
            break;
        case 'b':
            *index += 4;

            if (amount > counts[2]) {
                counts[2] = amount;
            }
            break;
    }
}

void parseSet(char* file, int* counts, int* index) {
    while ((file[*index] != ';') && (file[*index] != '\n')) {
        parseCubes(file, counts, index);

        if (file[*index] == ',') {
            *index += 2;
        }
    }

    if (file[*index] == ';') {
        *index += 2;
    }
}

int totalSetPower(char* file) {
    int total = 0;
    int i = 0;
    int* counts = (int*) malloc(3 * sizeof(int));

    while (file[i] != '\0') {
        while (file[i] != ':') {
            i++;
        }
        
        i+=2;
        memset(counts, 0, 3 * sizeof(int));

        while (file[i] != '\n') {
            parseSet(file, counts, &i);
        }

        total += counts[0] * counts[1] * counts[2];
        i++;
    }

    free(counts);

    return total;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Expected filpath as argument.\n");
        exit(1);
    }

    char* file = readFile(argv[1]);
    
    int total = totalSetPower(file);

    printf("%d\n", total);

    free(file);
    return 0;
}