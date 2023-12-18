#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

int parseCubes(char* file, int* index);
int parseSet(char* file, int* index);
int totalGameIds(char* file);

int parseCubes(char* file, int* index) {
    int amount = 0;

    while (isdigit(file[*index])) {
        amount *= 10;
        amount += file[*index] - '0';
        *index += 1;
    }

    *index += 1;

    switch (file[*index]) {
        case 'r':
            *index += 3;

            if (amount > 12) {
                return 1;
            }
            break;
        case 'g':
            *index += 5;

            if (amount > 13) {
                return 1;
            }
            break;
        case 'b':
            *index += 4;

            if (amount > 14) {
                return 1;
            }
            break;
    }

    return 0;
}

int parseSet(char* file, int* index) {
    int result;

    while ((file[*index] != ';') && (file[*index] != '\n')) {
        result = parseCubes(file, index);

        if (file[*index] == ',') {
            *index += 2;
        }

        if (result == 1) {
            while ((file[*index] != ';') && (file[*index] != '\n')) {
                *index += 1;
            }

            return 1;
        }
    }

    if (file[*index] == ';') {
        *index += 2;
    }

    return 0;
}

int totalGameIds(char* file) {
    int total = 0;
    int i = 0;
    int id = 1;
    int result;

    while (file[i] != '\0') {
        while (file[i] != ':') {
            i++;
        }
        
        i+=2;

        while (file[i] != '\n') {
            result = parseSet(file, &i);

            if (result == 1) {
                while (file[i] != '\n') {
                    i++;
                }
            }
        }

        if (result == 0) {
            total += id;
        }

        id++;
        i++;
    }

    return total;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Expected filpath as argument.\n");
        exit(1);
    }

    char* file = readFile(argv[1]);
    
    int total = totalGameIds(file);

    printf("%d\n", total);

    free(file);
    return 0;
}