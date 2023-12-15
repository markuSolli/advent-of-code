#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

struct keyword {
    int length;
    const char* pattern;
};

int scanKeyword(char* file, int* index, struct keyword word, int j);
int scanKeywords(char* buffer, int* index);
int totalCalibrationValues(char* file);

struct keyword keywords[9] = {
    {3, "one"},
    {3, "two"},
    {5, "three"},
    {4, "four"},
    {4, "five"},
    {3, "six"},
    {5, "seven"},
    {5, "eight"},
    {4, "nine"}
};

int scanKeyword(char* file, int* index, struct keyword word, int j) {
    if ((file[*index + j] == '\n') || (j >= word.length)) {
        return 0;
    }

    if (file[*index + j] == word.pattern[j]) {
        if (j + 1 == word.length) {
            return 1;
        }

        return scanKeyword(file, index, word, j + 1);
    }

    return 0;
}

int scanKeywords(char* file, int* index) {
    int match;
    for (int i=0; i<9; i++) {
        match = scanKeyword(file, index, keywords[i], 0);

        if (match == 1) {
            *index += keywords[i].length - 1;
            return i + 1;
        }
    }

    return -1;
}

int totalCalibrationValues(char* file) {
    int first, last, digit;
    int total = 0;
    int i = 0;

    while (file[i] != '\0') {
        first = -1;
        last = -1;

        while (file[i] != '\n') {
            digit = -1;

            if (isdigit(file[i])) {
                digit = file[i] - '0';
            } else {
                digit = scanKeywords(file, &i);
            }

            if (digit > 0) {
                if (first < 0) {
                    first = digit;
                } else {
                    last = digit;
                }
            }

            i++;
        }

        if (first < 0) {
            return -1;
        } else if (last < 0) {
            last = first;
        }

        total += 10 * first + last;
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
    
    int total = totalCalibrationValues(file);

    printf("%d\n", total);

    free(file);
    return 0;
}