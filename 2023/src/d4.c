#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

int totalPoints(char* file);
int winningNumbersLength(char* file);

int winningNumbersLength(char* file) {
    int i = 0;
    int n = 0;

    while (file[i] != ':') {
        i++;
    }
    i += 2;

    while (file[i] != '|') {
        if (file[i] == ' ') {
            n++;
        }

        i++;
    }

    return n;
}

int totalPoints(char* file) {
    int n = winningNumbersLength(file);
    int* winningNumbers = (int*) malloc(n * sizeof(int));
    int matches, j, number;
    int total = 0;
    int i = 0;

    while (file[i] != '\0') {
        memset(winningNumbers, 0, n * sizeof(int));
        matches = 0;
        j = 0;

        while (file[i] != ':') {
            i++;
        }
        i += 2;

        while (file[i] != '|') {
            while (file[i] == ' ') {
                i++;
            }

            number = file[i] - '0';
            i++;

            while (isDigit(file[i])) {
                number *= 10;
                number += file[i] - '0';
                i++;
            }

            winningNumbers[j] = number;
            j++;
            i++;
        }
        i += 2;

        while (file[i] != '\n') {
            while (file[i] == ' ') {
                i++;
            }

            number = file[i] - '0';
            i++;

            while (isDigit(file[i])) {
                number *= 10;
                number += file[i] - '0';
                i++;
            }

            for (j=0; j<n; j++) {
                if (number == winningNumbers[j]) {
                    matches++;
                    break;
                }
            }
        }

        if (matches > 0) {
            total += pow(2, matches - 1);
        }

        i++;
    }

    free(winningNumbers);
    return total;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Expected filpath as argument.\n");
        exit(1);
    }

    char* file = readFile(argv[1]);
    
    int total = totalPoints(file);

    printf("%d\n", total);

    free(file);
    return 0;
}